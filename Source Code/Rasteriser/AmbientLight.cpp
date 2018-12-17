#include "AmbientLight.h"



AmbientLight::AmbientLight()
{
}

AmbientLight::AmbientLight(int red, int green, int blue)
{
	_liRed = red;
	_liGreen = green;
	_liBlue = blue;
}

AmbientLight::~AmbientLight()
{
}

void AmbientLight::SetRedLightIntensity(int value)
{
	_liRed = value;
}
int AmbientLight::GetRedLightIntensity() const
{
	return _liRed;
}
void AmbientLight::SetGreenLightIntensity(int value)
{
	_liGreen = value;
}
int  AmbientLight::GetGreenLightIntensity() const
{
	return _liGreen;
}
void AmbientLight::SetBlueLightIntensity(int value)
{
	_liBlue = value;
}
int AmbientLight::GetBlueLightIntensity() const
{
	return _liBlue;
}

