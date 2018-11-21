#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRotate = xRotation;
	_yRotate = yRotation;
	_zRotate = zRotation;
	_camera = position;
	SetViewingMatrix();
}

Vertex Camera::GetCameraPosition()
{
	return _camera;
}
void Camera::SetViewingMatrix()
{
	_viewingMatrix = Matrix::XYZRotationMatrix(_xRotate, _yRotate, _zRotate) * Matrix::TranslationMatrix(-_camera.GetX(), -_camera.GetY(), -_camera.GetZ());
}

Matrix Camera::GetViewingMatrix()
{
	return _viewingMatrix;
}