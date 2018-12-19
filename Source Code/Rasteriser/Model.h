#pragma once
#include <vector>
#include "Framework.h"
#include "Vertex.h"
#include "Vector3D.h"
#include "Polygon3D.h"
#include "Matrix.h"
#include "Camera.h"
#include "Lighting.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include <algorithm>

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

	void CalculateLightingAmbient(vector<AmbientLight> ambientLighting);

	void CalculateLightingPoint(vector<PointLight> pointLights);

	void GenerateNormalVertexVectors();

private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;

	//Reflection Coefficents
	float kd_red = 1.0f;
	float kd_green = 1.0f;
	float kd_blue = 1.0f;//(0.0f - 1.0f) where 0.0 is all light absorbed and 1.0f is all light reflected. Set to 1.0f then test later.

	float ka_red = 0.2f; //Reflection Coefficents for ambient light
	float ka_green = 0.2f;
	float ka_blue = 0.2f;

	float kp_red = 0.7f; //Reflection Coefficents for point light
	float kp_green = 0.7f;
	float kp_blue = 0.7f;
};

