#pragma once
#include "Lighting.h"
#include "Vertex.h"
class PointLight :
	public Lighting
{
public:
	PointLight();
	PointLight(int red, int green, int blue, Vertex point, float attenA, float attenB, float attenC);

	void SetRedLightIntensity(int value);
	int GetRedLightIntensity() const;

	void SetGreenLightIntensity(int value);
	int GetGreenLightIntensity() const;

	void SetBlueLightIntensity(int value);
	int GetBlueLightIntensity() const;

	void SetAttenuationAValue(float value);
	float GetAttenuationAValue() const;

	void SetAttenuationBValue(float value);
	float GetAttenuationBValue() const;

	void SetAttenuationCValue(float value);
	float GetAttenuationCValue() const;

	void CalculateAttenuation(float distance);
	float GetAttenuation();

	Vertex GetPosition();
	~PointLight();

private:
	int _liRed, _liGreen, _liBlue;
	float _attenA, _attenB, _attenC;
	float _attenuation;
	Vertex _lightPosition;
	
};

