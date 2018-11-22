#include "Lighting.h"



Lighting::Lighting()
{
	_liRed = 0;
	_liGreen = 0;
	_liBlue = 0;
}

Lighting::Lighting(int liRed, int liGreen, int liBlue, Vector3D lightsource)
{
	_liRed = liRed;
	_liGreen = liGreen;
	_liBlue = liBlue;
	_lightsource = lightsource;
}
Lighting::~Lighting()
{
}

void Lighting::SetRedLightIntensity(int value)
{
	_liRed = value;
}
int Lighting::GetRedLightIntensity() const
{
	return _liRed;
}
void Lighting::SetGreenLightIntensity(int value)
{
	_liGreen = value;
}
int  Lighting::GetGreenLightIntensity() const
{
	return _liGreen;
}
void Lighting::SetBlueLightIntensity(int value)
{
	_liBlue = value;
}
int Lighting::GetBlueLightIntensity() const
{
	return _liBlue;
}

Lighting& Lighting::operator= (const Lighting &rhs)
{
	//Does this need to be here?
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}
void Lighting::Copy(const Lighting &other)
{
	_liRed = other.GetRedLightIntensity();
	_liGreen = other.GetGreenLightIntensity();
	_liBlue = other.GetBlueLightIntensity();
	//This also requires to copy the Vector
}
