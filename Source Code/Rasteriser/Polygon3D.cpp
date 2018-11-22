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
	_redColour = p.GetRedColour();
	_greenColour = p.GetGreenColour();
	_blueColour = p.GetBlueColour();
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

int Polygon3D::GetRedColour() const
{
	return _redColour;
}

void Polygon3D::SetRedColour(int value)
{
	_redColour = value;
}

int Polygon3D::GetGreenColour() const
{
	return _greenColour;
}

void Polygon3D::SetGreenColour(int value)
{
	_greenColour = value;
}

int Polygon3D::GetBlueColour() const
{
	return _blueColour;
}

void Polygon3D::SetBlueColour(int value)
{
	_blueColour = value;
}

int Polygon3D::GetColour() const
{
	//Is there a way to do this?
}

void Polygon3D::SetColour(int red, int green, int blue)
{
	_redColour = red;
	_greenColour = green;
	_blueColour = blue;
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
	_zDepth = other.GetZDepth();
	_redColour = other.GetRedColour();
	_greenColour = other.GetGreenColour();
	_blueColour = other.GetBlueColour();
}