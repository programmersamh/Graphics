#include "Polygon3D.h"

Polygon3D::Polygon3D()
{

}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_requiresCulling = false;
}

Polygon3D::~Polygon3D()
{

}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	for (int i = 0; i < 3; i++)
	{
		_indices[i] = p.GetIndex(i);
	}
	_requiresCulling = p.GetBackfaceCulling();
	_zDepth = p.GetZDepth();
}

//Accessor to return index of specified vertex
int Polygon3D::GetIndex(int index) const
{
	return _indices[index];
	//Change this once you know what should be returning
}

void Polygon3D::SetBackfaceCullingTrue()
{
	_requiresCulling = true;
}

void Polygon3D::SetBackfaceCullingFalse()
{
	_requiresCulling = false;
}

bool Polygon3D::GetBackfaceCulling() const
{
	return _requiresCulling;
}

void Polygon3D::SetZDepth(float zDepth)
{
	_zDepth = zDepth;
}

float Polygon3D::GetZDepth() const
{
	return _zDepth;
}
Polygon3D& Polygon3D::operator= (const Polygon3D &rhs)
{
	return *this;
}
