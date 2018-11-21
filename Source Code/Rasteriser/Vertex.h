#pragma once
#include "Vector3D.h"

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(const Vertex& other);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);
	float GetW() const;
	void SetW(const float W);

	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;

	const Vector3D operator- (const Vertex& rhs) const;

	void Dehomogenize();

private:
	void Initialise(float x, float y, float z, float w);
	void Copy(const Vertex& v);

	float _x;
	float _y;
	float _z;
	float _w;
};

