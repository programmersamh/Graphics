#pragma once
#include <vector>
#include "Framework.h"
#include "Vertex.h"
#include "Polygon3D.h"
#include "Matrix.h"
#include "Camera.h"
#include "Rasteriser.h"



class Model
{
public:
	Model();
	~Model();

	//Accessors
	vector<Polygon3D>& GetPolygons();
	vector<Vertex>& GetVertices();
	vector<Vertex>& GetTransformedVertices();

	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;

	void AddPolygon(int i0, int i1, int i2);
	void AddVertex(float x, float y, float z);
	void ApplyTransformToLocalVertices(const Matrix &transform);
	void ApplyTransformToTransformedVertices(const Matrix &transform);

	void DehomogenizeTransformedVertices();
	void CalculateBackfaces(Camera camera);
	void Sort(void);

	void CalculateLightingDirectional(vector<Lighting> directionalLighting);

private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;

	//Reflection Coefficents
	float kd_red, kd_green, kd_blue; //(0.0f - 1.0f) where 0.0 is all light absorbed and 1.0f is all light reflected. Set to 1.0f then test later.
};

