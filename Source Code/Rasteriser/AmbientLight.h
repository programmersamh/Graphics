#pragma once
#include "Lighting.h"
class AmbientLight :
	public Lighting
{
public:
	AmbientLight();

	AmbientLight(int red, int green, int blue);

	~AmbientLight();

	void SetRedLightIntensity(int value);

	int GetRedLightIntensity() const;

	void SetGreenLightIntensity(int value);

	int  GetGreenLightIntensity() const;

	void SetBlueLightIntensity(int value);

	int GetBlueLightIntensity() const;


private:
	int _liRed, _liGreen, _liBlue;
};

