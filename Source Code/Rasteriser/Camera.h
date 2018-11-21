#pragma once
#include "Vertex.h"
#include "Matrix.h"

class Camera
{
public:
	Camera();
	~Camera();

	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);

	void SetViewingMatrix();
	Vertex GetCameraPosition();
	Matrix GetViewingMatrix();

private:
	Matrix _viewingMatrix;
	Vertex _camera;

	float _xRotate;
	float _yRotate;
	float _zRotate;
};

