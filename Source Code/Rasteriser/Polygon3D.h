#pragma once
#include "Vector3D.h"
class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	//Accessor to return index of specified vertex
	int GetIndex(int) const;
	void SetBackfaceCullingTrue();
	void SetBackfaceCullingFalse();
	bool GetBackfaceCulling() const;

	void SetZDepth(float zDepth);
	float GetZDepth() const;

	Polygon3D& operator= (const Polygon3D &rhs);

private:
	float _zDepth;
	int _indices[3];
	bool _requiresCulling;
	Vector3D _normal;
	
};

