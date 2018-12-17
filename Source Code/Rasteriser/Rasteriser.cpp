#include "Rasteriser.h"

Rasteriser app;

bool Rasteriser::Initialise()
{
	if (!MD2Loader::LoadModel("U:\\Year2\\Graphics1\\Week 5\\Source Code\\Rasteriser\\md2\\teapot.md2", _model, //Replace File name with appropriate.
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	Vertex CameraPos = { 0, 0, -10 };
	_camera = Camera(0, 0, 0, CameraPos);

	_xRotation = 0;
	_yRotation = 0;
	_zRotation = 0;

	_cameraTransformation = _camera.GetViewingMatrix();

	Lighting _lighting1(0 ,100, 100, Vector3D{ 1,0,1});
	_directionalLighting.push_back(_lighting1);

	AmbientLight _ambient(50, 50, 50);
	_ambientLighting.push_back(_ambient);

	PointLight _pointLight(150, 150, 150, { 0,0, -10 }, 0, (float)0.2,0);
	_pointLighting.push_back(_pointLight);

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
	_model.CalculateLightingAmbient(_ambientLighting);
	_model.CalculateLightingDirectional(_directionalLighting);
	_model.CalculateLightingPoint(_pointLighting);
	//Apply Camera viewing transform
	_model.ApplyTransformToTransformedVertices(_cameraTransformation);
	//Sort
	_model.Sort();
	_model.ApplyTransformToTransformedVertices(_perspectiveTransformation);
	_model.DehomogenizeTransformedVertices();
	_model.ApplyTransformToTransformedVertices(_viewTransformation);

	if (_model.GetPolygonCount() != 0)
	{
	//if (_yRotation < 360)
	//{
	//	DrawWireFrame(bitmap);
	//}
	//else
	//{
			MyDrawSolidFlat(bitmap);
	//	}
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

	for (auto & polygon : polygons)
	{
		SetDCPenColor(hdc, polygon.GetColour());
		SetDCBrushColor(hdc, polygon.GetColour());

		if (polygon.GetBackfaceCulling() == false)
		{
			for (int j = 0; j < 3; j++)
			{
				points[j].x = (int)vertices[polygon.GetIndex(j)].GetX();
				points[j].y = (int)vertices[polygon.GetIndex(j)].GetY();
			}
			Polygon(hdc, points, 3);
		}
	}
}

void Rasteriser::MyDrawSolidFlat(Bitmap &bitmap)
{
	vector<Polygon3D> polygons = _model.GetPolygons();
	vector<Vertex> vertices = _model.GetTransformedVertices();

	for (auto & polygon : polygons)
	{
		if (!polygon.GetBackfaceCulling())
		{
			FillPolygonFlat(bitmap, vertices[polygon.GetIndex(0)], vertices[polygon.GetIndex(1)], vertices[polygon.GetIndex(2)], polygon.GetColour());
		}
	}
}

void fillBottomFlatTriangle(Bitmap &bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour)
{
	float invslope1 = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY()); //Returns a negative number
	float invslope2 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());

	float curx1 = v1.GetX();
	float curx2 = (v1.GetX() + 1.0f);

	HDC hdc = bitmap.GetDC();

	if (invslope2 < invslope1)
	{
		float invslopeTemp = invslope1;
		invslope1 = invslope2;
		invslope2 = invslopeTemp;
	}

	for (float scanlineY = v1.GetY(); scanlineY <= v2.GetY(); scanlineY++)
	{
		for (float i = curx1; i < curx2; i++)
		{
			SetPixel(hdc, (int)i, (int)scanlineY, colour);
		}

		curx1 += invslope1;
		curx2 += invslope2;
	}
}


void fillTopFlatTriangle(Bitmap &bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour)
{
	float invslope1 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());
	float invslope2 = (v3.GetX() - v2.GetX()) / (v3.GetY() - v2.GetY());

	float curx1 = v3.GetX();
	float curx2 = (v3.GetX() + 1.0f);
	
	HDC hdc = bitmap.GetDC();

	if (invslope1 < invslope2)
	{
		float invslopeTemp = invslope1;
		invslope1 = invslope2;
		invslope2 = invslopeTemp;
	}
	

	for (float scanlineY = v3.GetY(); scanlineY > v1.GetY(); scanlineY--)
	{
		for (float i = curx1; i < curx2; i++)
		{
			SetPixel(hdc, (int)i, (int)(scanlineY), colour);
		}
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}

void Rasteriser::FillPolygonFlat(Bitmap &bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour)
{
	Vertex Tmp;

	if (v1.GetY() > v2.GetY())
	{
		Tmp = v1;
		v1 = v2;
		v2 = Tmp;
	}
	/* here v1.y <= v2.y */
	if (v1.GetY() > v3.GetY())
	{
		Tmp = v1;
		v1 = v3;
		v3 = Tmp;
	}
	/* here v1.y <= v2.y and v1.y <= v3.y so test v2 vs. v3 */
	if (v2.GetY() > v3.GetY())
	{
		Tmp = v2;
		v2 = v3;
		v3 = Tmp;
	}

	/* here we know that v1.y <= v2.y <= v3.y */
	/* check for trivial case of bottom-flat triangle */
	if (v2.GetY() == v3.GetY())
	{
		fillBottomFlatTriangle(bitmap, v1, v2, v3, colour);
	}
	/* check for trivial case of top-flat triangle */
	else if (v1.GetY() == v2.GetY())
	{
		fillTopFlatTriangle(bitmap, v1, v2, v3, colour);
	}
	else
	{
		/* general case - split the triangle in a topflat and bottom-flat one */
		float tempX = v1.GetX() + ((v2.GetY() - v1.GetY()) / (v3.GetY() - v1.GetY())) * (v3.GetX() - v1.GetX());
		Vertex vTmp = {tempX, v2.GetY(), v2.GetZ() };
		fillBottomFlatTriangle(bitmap, v1, v2, vTmp, colour);
		fillTopFlatTriangle(bitmap, v2, vTmp, v3, colour);
	}
}