#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_requiresCulling = false;
	_colour = RGB(255, 255, 255);
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_requiresCulling = false;
	_colour = RGB(0, 0, 0);
}

Polygon3D::~Polygon3D()
{

}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	Copy(p);
}

//Accessor to return index of specified vertex
int Polygon3D::GetIndex(int index) const
{
	return _indices[index];
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
void Polygon3D::SetNormalVector(Vector3D normal)
{
	_normal = normal;
}
Vector3D Polygon3D::GetNormalVector() const
{
	return _normal;
}

COLORREF Polygon3D::GetColour() const
{
	return _colour;
}

void Polygon3D::SetColour(int red, int green, int blue)
{
	_colour = RGB(red, green, blue);
}

Polygon3D& Polygon3D::operator= (const Polygon3D &rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}
void Polygon3D::Copy(const Polygon3D& other)
{
	for (int i = 0; i < 3; i++)
	{
		_indices[i] = other.GetIndex(i);
	}
	_requiresCulling = other.GetBackfaceCulling();
	_normal = other.GetNormalVector();
	_zDepth = other.GetZDepth();
	_colour = other.GetColour();
}

int Polygon3D::ColourClamp(int value)
{
	if (value < 0)
	{
		return 0;
	}
	else if (value > 255)
	{
		return 255;
	}
	return value;
}