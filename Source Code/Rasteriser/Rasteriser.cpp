#include "Rasteriser.h"

Rasteriser app;

bool Rasteriser::Initialise()
{
	if (!MD2Loader::LoadModel("U:\\Year2\\Graphics1\\Week 5\\Source Code\\Rasteriser\\md2\\chef.md2", _model, //Replace File name with appropriate.
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	Vertex CameraPos = { 0, 0, -50 };
	_camera = Camera(0, 0, 0, CameraPos);

	_xRotation = 0;
	_yRotation = 0;
	_zRotation = 0;

	_cameraTransformation = _camera.GetViewingMatrix();

	return true;
}
void Rasteriser::Update(Bitmap &bitmap)
{
	_yRotation++;

	_modelTransformation = Matrix::XYZRotationMatrix(_xRotation, _yRotation, _zRotation) * Matrix::TranslationMatrix(0, 0, 0);
	
	//Aspect ratio is required to be a float to stop rounding errors and streching out the object
	float aspectratio = (float)bitmap.GetWidth() / (float)bitmap.GetHeight();

	GeneratePerspectiveMatrix(1.0f, aspectratio);
	GenerateViewMatrix(1.0f, bitmap.GetWidth(), bitmap.GetHeight());
}

void Rasteriser::Render(Bitmap &bitmap)
{
	// Clear the window to black
	bitmap.Clear(RGB(0, 0, 0));

	_model.ApplyTransformToLocalVertices(_modelTransformation);
	//Backface Culling
	_model.CalculateBackfaces(_camera);
	//Apply Camera viewing transform
	_model.ApplyTransformToTransformedVertices(_cameraTransformation);
	//Sort
	_model.Sort();
	_model.ApplyTransformToTransformedVertices(_perspectiveTransformation);
	_model.DehomogenizeTransformedVertices();
	_model.ApplyTransformToTransformedVertices(_viewTransformation);

	if (_model.GetPolygonCount() != 0)
	{
		if (_yRotation < 360)
		{
			DrawWireFrame(bitmap);
		}
		else
		{
			DrawSolidFlat(bitmap);
		}
	}
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio) //Distance to screen
{
	_perspectiveTransformation = { d / aspectRatio, 0, 0, 0,
						0, d, 0, 0,
						0, 0, d, 0,
						0, 0, 1, 0};
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	_viewTransformation = { (float)width / 2, 0, 0, (float)width / 2,
						0, (float)-height / 2, 0, (float)height / 2,
						0,	0,   d / 2,   d / 2,
						0, 0, 0, 1 };
}

void Rasteriser::DrawWireFrame(Bitmap &bitmap)
{
	vector<Polygon3D> polygons = _model.GetPolygons();
	vector<Vertex> vertices = _model.GetTransformedVertices();
	
	HDC hdc = bitmap.GetDC();
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(255, 255, 255));
	
	for (auto & polygon : polygons)
	{
		if (polygon.GetBackfaceCulling() == false)
		{
			MoveToEx(hdc, (int)vertices[polygon.GetIndex(0)].GetX(), (int)vertices[polygon.GetIndex(0)].GetY(), NULL);
			for (int j = 0; j < 3; j++)
			{
				LineTo(hdc, (int)vertices[polygon.GetIndex(j)].GetX(), (int)vertices[polygon.GetIndex(j)].GetY());
			}
			LineTo(hdc, (int)vertices[polygon.GetIndex(0)].GetX(), (int)vertices[polygon.GetIndex(0)].GetY());
		}
	}
}

void Rasteriser::DrawSolidFlat(Bitmap &bitmap)
{
	vector<Polygon3D> polygons = _model.GetPolygons();
	vector<Vertex> vertices = _model.GetTransformedVertices();
	POINT points[3];

	HDC hdc = bitmap.GetDC();
	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCPenColor(hdc, RGB(0,255,255));
	SetDCBrushColor(hdc, RGB(0,255,255));

	for (auto & polygon : polygons)
	{
		if (polygon.GetBackfaceCulling() == false)
		{
			for (int j = 0; j < 3; j++)
			{
				points[j].x = (long)vertices[polygon.GetIndex(j)].GetX();
				points[j].y = (long)vertices[polygon.GetIndex(j)].GetY();
			}
			Polygon(hdc, points, 3);
		}
	}
}

