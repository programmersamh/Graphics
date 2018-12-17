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
			polygon.SetNormalVector(Vector3D::CalculateCrossProduct(vector2,vector1));
			Vector3D eyeVector = _transformedVertices[polygon.GetIndex(0)] - camera.GetCameraPosition();

			float result = Vector3D::CalculateDotProduct(polygon.GetNormalVector(), eyeVector);
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
	float tempRed, tempGreen, tempBlue; //Temp values

	for (auto & polygon : _polygons)
	{

		//Resetting the total values to black
		red = GetRValue(polygon.GetColour());
		green = GetGValue(polygon.GetColour());
		blue = GetBValue(polygon.GetColour());

		for (auto & lighting : directionalLighting)
		{
			//Setting the temp RGB values to the light intensity;
			tempRed = (float)lighting.GetRedLightIntensity();
			tempGreen = (float)lighting.GetGreenLightIntensity();
			tempBlue = (float)lighting.GetBlueLightIntensity();

			//Modulating the temp RGB values by their corresponding reflectance coefficients
			tempRed = tempRed * kd_red;
			tempGreen = tempGreen * kd_green;
			tempBlue = tempBlue * kd_blue;

			Vector3D lightSourceNormal = lighting.GetLightSource();
			lightSourceNormal.normaliseVector();

			Vector3D polyNormalVector = polygon.GetNormalVector();
			polyNormalVector.normaliseVector();

			//Calculate the dot product of the normal vector to light source
			float dotproduct = Vector3D::CalculateDotProduct(lightSourceNormal, polyNormalVector); 

			//Making sure that if there are multiple lights that it doesn't take away from the other applied lights
			if (dotproduct > 0)
			{
				tempRed *= dotproduct;
				tempGreen *= dotproduct;
				tempBlue *= dotproduct;
			}
			else
			{
				tempRed = 0;
				tempGreen = 0;
				tempBlue = 0;
			}

			red += (int)tempRed;
			green += (int)tempGreen;
			blue += (int)tempBlue;
		}

		red = polygon.ColourClamp(red);
		green = polygon.ColourClamp(green);
		blue = polygon.ColourClamp(blue);

		polygon.SetColour(red, green, blue);
	}
}

void Model::CalculateLightingAmbient(vector<AmbientLight> ambientLighting)
{
	int red, green, blue; //Total values
	float tempRed, tempGreen, tempBlue; //Temp values

	for (auto & polygon : _polygons)
	{
		//Resetting the total values to black
		red = 0;
		green = 0;
		blue = 0;
		
		for (auto & ambientLight : ambientLighting)
		{
			//Setting the temp RGB values to the light intensity;
			tempRed = (float)ambientLight.GetRedLightIntensity();
			tempGreen = (float)ambientLight.GetGreenLightIntensity();
			tempBlue = (float)ambientLight.GetBlueLightIntensity();

			//Modulating the temp RGB values by their corresponding reflectance coefficients
			tempRed = tempRed * ka_red;
			tempGreen = tempGreen * ka_green;
			tempBlue = tempBlue * ka_blue;

			red += (int)tempRed;
			green += (int)tempGreen;
			blue += (int)tempBlue;
		}
		red = polygon.ColourClamp(red);
		green = polygon.ColourClamp(green);
		blue = polygon.ColourClamp(blue);

		polygon.SetColour(red, green, blue);
	}
}

void Model::CalculateLightingPoint(vector<PointLight> pointLights)
{
	//This needs to be moved to polygon once working
	int red, green, blue; //Total values
	float tempRed, tempGreen, tempBlue; //Temp values

	for (auto & polygon : _polygons)
	{

		//Resetting the total values to black
		red = GetRValue(polygon.GetColour());
		green = GetGValue(polygon.GetColour());
		blue = GetBValue(polygon.GetColour());
		
		for (auto & pointlights : pointLights)
		{
			tempRed = (float)pointlights.GetRedLightIntensity();
			tempGreen = (float)pointlights.GetGreenLightIntensity();
			tempBlue = (float)pointlights.GetBlueLightIntensity();

			tempRed = tempRed * kp_red;
			tempGreen = tempGreen * kp_green;
			tempBlue = tempBlue * kp_blue;
			/*
			To calculate the vector to the light source, you can subtract the position of the light source
			from the position of the first vertex in the polygon.Then normalise it.
			*/
			Vector3D lightSourceVector = _transformedVertices[polygon.GetIndex(0)] - pointlights.GetPosition();
			lightSourceVector.normaliseVector();

			Vector3D polyNormalVector = polygon.GetNormalVector();
			polyNormalVector.normaliseVector();

			//Calculate the dot product of the normal vector to light source
			float dotproduct = Vector3D::CalculateDotProduct(lightSourceVector, polyNormalVector);

			pointlights.CalculateAttenuation(lightSourceVector.GetVectorMagnitude());
			
			if (pointlights.GetAttenuation() > 0)
			{
				tempRed *= pointlights.GetAttenuation();
				tempGreen *= pointlights.GetAttenuation();
				tempBlue *= pointlights.GetAttenuation();
			}
			else
			{
				tempRed = 0;
				tempGreen = 0;
				tempBlue = 0;
			}
			if (dotproduct > 0)
			{
				tempRed *= dotproduct;
				tempGreen *= dotproduct;
				tempBlue *= dotproduct;
			}
			else
			{
				tempRed = 0;
				tempGreen = 0;
				tempBlue = 0;
			}
			/*
			• You also need to multiply by the attenuation which is based on the distance from the light
			source.To calculate the distance, calculate the length of the vector to the light source(before
			it was normalised).
			The attenuation coefficients should be supplied to the constructor when
			you create a new point light.
			*/
			red += (int)tempRed;
			green += (int)tempGreen;
			blue += (int)tempBlue;
		}
		red = polygon.ColourClamp(red);
		green = polygon.ColourClamp(green);
		blue = polygon.ColourClamp(blue);

		polygon.SetColour(red, green, blue);
	}
}
