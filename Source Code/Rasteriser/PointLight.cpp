#include "PointLight.h"
#include <math.h>



PointLight::PointLight()
{
	_liRed = 0;
	_liGreen = 0;
	_liBlue = 0;
	_lightPosition = { 0, 0, -50 };
	_attenA = 0;
	_attenB = 1;
	_attenC = 0;
}

PointLight::~PointLight()
{
}

PointLight::PointLight(int red, int green, int blue, Vertex point, float attenA, float attenB, float attenC)
{
	_liRed = red;
	_liGreen = green;
	_liBlue = blue;
	_lightPosition = point;
	_attenA = attenA;
	_attenB = attenB;
	_attenC = attenC;
}

void PointLight::CalculateAttenuation(float distance)
{
	float value = (float)(_attenA + _attenB * distance + _attenC * pow(distance, 2));
	_attenuation = (1 / value);
}

float PointLight::GetAttenuation()
{
	return _attenuation;
}
Vertex PointLight::GetPosition()
{
	return _lightPosition;
}

void PointLight::SetRedLightIntensity(int value)
{
	_liRed = value;
}
int PointLight::GetRedLightIntensity() const
{
	return _liRed;
}
void PointLight::SetGreenLightIntensity(int value)
{
	_liGreen = value;
}
int  PointLight::GetGreenLightIntensity() const
{
	return _liGreen;
}
void PointLight::SetBlueLightIntensity(int value)
{
	_liBlue = value;
}
int PointLight::GetBlueLightIntensity() const
{
	return _liBlue;
}
void PointLight::SetAttenuationAValue(float value)
{
	_attenA = value;
}
float PointLight::GetAttenuationAValue() const
{
	return _attenA;
}

void PointLight::SetAttenuationBValue(float value)
{
	_attenB = value;
}
float PointLight::GetAttenuationBValue() const
{
	return _attenB;
}
void PointLight::SetAttenuationCValue(float value)
{
	_attenC = value;
}
float PointLight::GetAttenuationCValue() const
{
	return _attenC;
}