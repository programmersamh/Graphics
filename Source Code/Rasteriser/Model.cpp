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