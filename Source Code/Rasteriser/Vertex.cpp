#include "Vertex.h"

Vertex::Vertex()
{
	Initialise(0, 0, 0,1);
}

Vertex::Vertex(float x, float y, float z)
{
	Initialise(x, y, z,1);
}

Vertex::Vertex(const Vertex & other)
{
	Initialise(other.GetX(), other.GetY(), other.GetZ(), other.GetW());
}

float Vertex::GetX() const
{
	return _x;
}

void Vertex::SetX(const float x)
{
	_x = x;
}
 
float Vertex::GetY() const
{
	return _y;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

float Vertex::GetZ() const
{
	return _z;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}

float Vertex::GetW() const
{
	return _w;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

Vector3D Vertex::GetNormalVector() const
{
	return _normalVector;
}
void Vertex::SetNormalVector(Vector3D vector)
{
	_normalVector = vector;
}
COLORREF Vertex::GetVertexColour() const
{
	return _vertexColour;
}
void Vertex::SetVertexColour(COLORREF colour)
{
	_vertexColour = colour;
}

int Vertex::GetPolyContribute() const
{
	return _polyContributeCount;
}
void Vertex::SetPolyContribute(int value)
{
	_polyContributeCount = value;
}
void Vertex::IncrementPolyContribute()
{
	_polyContributeCount++;
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_w = rhs.GetW();
		_vertexColour = rhs.GetVertexColour();
		_normalVector = rhs.GetNormalVector();
		_polyContributeCount = rhs.GetPolyContribute();
	}
	return *this;
}

// The const at the end of the declaraion for '==" indicates that this operation does not change
// any of the member variables in this class.

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ());
}

// You can see three different uses of 'const' here:
//
// The first const indicates that the method changes the return value, but it is not moved in memory
// The second const indicates that the parameter is passed by reference, but it is not modified
// The third const indicates that the operator does not change any of the memory variables in the class.

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

const Vector3D Vertex::operator-(const Vertex& rhs) const
{
	return Vector3D(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
}

//PRIVATE

void Vertex::Dehomogenize()
{
	_x = _x / _w;
	_y = _y / _w;
	_z = _z / _w;
	_w = _w / _w;
}
void Vertex::Initialise(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
	_normalVector = { 0,0,0 };
	_polyContributeCount = 0;
}

void Vertex::Copy(const Vertex& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = v.GetW();
}