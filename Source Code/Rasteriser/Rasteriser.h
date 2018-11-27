#pragma once
#include <vector>
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "Polygon3D.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "Lighting.h"

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(Bitmap &bitmap);
	void Render(Bitmap &bitmap);

	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);

	void DrawWireFrame(Bitmap &bitmap);
	void DrawSolidFlat(Bitmap &bitmap);

private:
	Matrix _perspectiveTransformation;
	Matrix _viewTransformation;
	Matrix _modelTransformation;
	Matrix _cameraTransformation;

	float _xRotation;
	float _yRotation;
	float _zRotation;
	Matrix _translation;

	vector<Lighting> _directionalLighting;

	Model _model;
	Camera _camera;
	float _x;
	float _y; 
};

