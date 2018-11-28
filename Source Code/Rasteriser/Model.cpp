#include "Model.h"
#include <algorithm>

Model::Model()
{

}
Model::~Model()
{

}

vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}
vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}
vector<Vertex>& Model::GetTransformedVertices()
{
	return _transformedVertices;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}
size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}
void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z));
}

void Model::ApplyTransformToLocalVertices(const Matrix &transform)
{
	_transformedVertices.clear();

	for (size_t i = 0; i < _vertices.size(); i++)
	{
		_transformedVertices.push_back(transform * _vertices[i]);
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix &transform)
{
	for (size_t i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = transform * _transformedVertices[i];
	}
}
void Model::DehomogenizeTransformedVertices()
{
	for (size_t i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i].Dehomogenize();
	}
}

void Model::CalculateBackfaces(Camera camera)
{
	for (auto & polygon : _polygons)
	{
			Vector3D vector1 = _transformedVertices[polygon.GetIndex(0)] - _transformedVertices[polygon.GetIndex(1)];
			Vector3D vector2 = _transformedVertices[polygon.GetIndex(0)] - _transformedVertices[polygon.GetIndex(2)];
			//Calculate the normal vector
			Vector3D normalVector = Vector3D::CalculateCrossProduct(vector2,vector1);
			Vector3D eyeVector = _transformedVertices[polygon.GetIndex(0)] - camera.GetCameraPosition();

			float result = Vector3D::CalculateDotProduct(normalVector, eyeVector);
			if (result < 0)
			{
				polygon.SetBackfaceCullingTrue();
			}
			else
			{
				polygon.SetBackfaceCullingFalse();
			}
	}
}

bool Compare(Polygon3D poly1, Polygon3D poly2)
{
	return poly1.GetZDepth() > poly2.GetZDepth();
}

void Model::Sort(void)
{
	for (auto & polygon : _polygons)
	{
		float averageDepth = (_transformedVertices[polygon.GetIndex(0)].GetZ() + _transformedVertices[polygon.GetIndex(1)].GetZ() + _transformedVertices[polygon.GetIndex(2)].GetZ()) / 3;
		polygon.SetZDepth(averageDepth);
	}
	sort(_polygons.begin(), _polygons.end(), Compare );
}

void Model::CalculateLightingDirectional(vector<Lighting> directionalLighting)
{
	//This needs to be moved to polygon once working
	int red, green, blue; //Total values
	int tempRed, tempGreen, tempBlue; //Temp values

	for (auto & polygon : _polygons)
	{
		//Resetting the total values to black
		red = 0;
		green = 0;
		blue = 0;
		
		for (auto & lighting : directionalLighting)
		{
			//Setting the temp RGB values to the light intensity;
			tempRed = lighting.GetRedLightIntensity();
			tempGreen = lighting.GetGreenLightIntensity();
			tempBlue = lighting.GetBlueLightIntensity();

			//Modulating the temp RGB values by their corresponding reflectance coefficients
			tempRed = tempRed * kd_red;
			tempGreen = tempGreen * kd_green;
			tempBlue = tempBlue * kd_blue;

			//Calculate the dot product of the normal vector to light source
			float dotproduct = Vector3D::CalculateDotProduct(lighting.GetLightSource(), polygon.GetNormalVector()); //This is supposed to take the normal vector? or the normalized vector?

			tempRed = tempRed * dotproduct;
			tempGreen = tempGreen * dotproduct;
			tempBlue = tempBlue * dotproduct;

			red += tempRed;
			green += tempGreen;
			blue += tempBlue;
		}

		polygon.ColourClamp(red);
		polygon.ColourClamp(green);
		polygon.ColourClamp(blue);

		polygon.SetColour(red, green, blue);
	}
}