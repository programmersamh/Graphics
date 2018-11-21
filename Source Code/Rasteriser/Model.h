#pragma once
#include <vector>
#include "Framework.h"
#include "Vertex.h"
#include "Polygon3D.h"
#include "Matrix.h"
#include "Camera.h"

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

private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;

};

