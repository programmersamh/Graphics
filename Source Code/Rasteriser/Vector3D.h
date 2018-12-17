#pragma once
class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();

	void SetX(const float x);
	float GetX()const;

	void SetY(const float y);
	float GetY()const;

	void SetZ(const float z);
	float GetZ()const;

	float GetVectorMagnitude() const;

	void normaliseVector();
	void vectorMagnitude();

	static float CalculateDotProduct(Vector3D vector1, Vector3D vector2);
	
	static Vector3D CalculateCrossProduct(Vector3D vector1, Vector3D vector2);

	void Copy(const Vector3D& v);
private:
	float _x, _y, _z, _oldZ;
	float _vectorMagnitude;
};

