#pragma once
#include "Vector3D.h"
#include "Vertex.h"
#include "Framework.h"

class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	//Accessor to return index of specified vertex
	int GetIndex(int) const;
	
	//Methods to set and get if the polygon is facing away from the camera or not
	void SetBackfaceCullingTrue();
	void SetBackfaceCullingFalse();
	bool GetBackfaceCulling() const;
	
	//Used for the sorting algorithm to order all the polygons
	void SetZDepth(float zDepth);
	float GetZDepth() const;
	void SetNormalVector(Vector3D normal);
	Vector3D GetNormalVector() const;

	//Controlling the colour of each of the polygons
	COLORREF GetColour() const;
	void SetColour(int red, int green, int blue);
	int ColourClamp(int value);
	void sortVerticesAscendingByY();

	Polygon3D& operator= (const Polygon3D &rhs);
	void Copy(const Polygon3D& other);

private:
	int _redColour, _blueColour, _greenColour;
	float _zDepth;
	int _indices[3];
	bool _requiresCulling;
	Vector3D _normal;
	COLORREF _colour;
};

