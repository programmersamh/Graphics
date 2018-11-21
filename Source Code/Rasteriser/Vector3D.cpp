#include "Vector3D.h"



Vector3D::Vector3D()
{
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	vectorMagnitude();
}

Vector3D::~Vector3D()
{
}

void Vector3D::normaliseVector()
{
	vectorMagnitude();
	_x = _x / _vectorMagnitude;
	_y = _y / _vectorMagnitude;
	_z = _z / _vectorMagnitude;
}

void Vector3D::vectorMagnitude()
{
	 _vectorMagnitude = (float)((_x*_x + _y * _y + _z * _z) * 0.5);
}

float Vector3D::CalculateDotProduct(Vector3D vector1, Vector3D vector2)
{
	float dotProduct = vector1.GetX()*vector2.GetX() + vector1.GetY()*vector2.GetY() + vector1.GetZ()*vector2.GetZ();
	return dotProduct;
}

Vector3D Vector3D::CalculateCrossProduct(Vector3D vector1, Vector3D vector2)
{
	float _nx = (vector1.GetY() * vector2.GetZ()) - (vector1.GetZ() * vector2.GetY());
	float _ny = (vector1.GetZ() * vector2.GetX()) - (vector1.GetX() * vector2.GetZ());
	float _nz = (vector1.GetX() * vector2.GetY()) - (vector1.GetY() * vector2.GetX());

	return Vector3D(_nx, _ny, _nz);
}

void Vector3D::Copy(const Vector3D& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	vectorMagnitude();
}


void Vector3D::SetX(const float x)
{
	_x = x;
}
float Vector3D::GetX() const
{
	return _x;
}

void Vector3D::SetY(const float y)
{
	_y = y;
}
float Vector3D::GetY() const
{
	return _y;
}

void Vector3D::SetZ(const float z)
{
	_z = z;
}
float Vector3D::GetZ() const
{
	return _z;
}