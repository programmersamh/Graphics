#pragma once
#include "Vector3D.h"

class Lighting
{
public:
	Lighting();
	Lighting(int liRed, int liGreen, int liBlue, Vector3D lightsource);
	~Lighting();

	void SetRedLightIntensity(int value);
	int GetRedLightIntensity() const;

	void SetGreenLightIntensity(int value);
	int GetGreenLightIntensity() const;

	void SetBlueLightIntensity(int value);
	int GetBlueLightIntensity() const;

	void SetLightSource(Vector3D lightsource);
	Vector3D GetLightSource() const;

	Lighting& operator= (const Lighting &rhs);
	void Copy(const Lighting& other);

private:
	int _liRed, _liGreen, _liBlue; //Light Intensity for all colours
	Vector3D _lightsource;
};

