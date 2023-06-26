
#include "projection.h"

namespace World
{
	void updateProjectionMatrix(ProjectionMatrix& pm, int screenWidth, int screenHeight, double nearPlane, double farPlane, double fov)
	{
		pm.screenWidth = screenWidth;
		pm.screenHeight = screenHeight;

		double aspectRatio = (double)screenHeight / (double)screenWidth;
		double invTan = 1.0 / tan(fov * 0.5);

		pm.mat[0][0] = aspectRatio * invTan;
		pm.mat[1][1] = invTan;
		pm.mat[2][2] = farPlane / (farPlane - nearPlane);
		pm.mat[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
		pm.mat[2][3] = 1.0;
		pm.mat[3][3] = 0.0;
	}

	void multiplyMatrixVector(ProjectionMatrix& pm, Vec3d& i, Vec3d& o)
	{
		o.x = i.x * pm.mat[0][0] + i.y * pm.mat[1][0] + i.z * pm.mat[2][0] + pm.mat[3][0];
		o.y = i.x * pm.mat[0][1] + i.y * pm.mat[1][1] + i.z * pm.mat[2][1] + pm.mat[3][1];
		o.z = i.x * pm.mat[0][2] + i.y * pm.mat[1][2] + i.z * pm.mat[2][2] + pm.mat[3][2];
		double w = i.x * pm.mat[0][3] + i.y * pm.mat[1][3] + i.z * pm.mat[2][3] + pm.mat[3][3];

		if (w != 0.0)
		{
			o.x /= w;
			o.y /= w;
			o.z /= w;
		}
	}

	Mesh::Mesh()
	{ }

	void Mesh::addTriangle(Triangle tri)
	{
		triangles.push_back(tri);
	}

	void Mesh::getProjectedPolygon(Gdiplus::Point polygon[3], ProjectionMatrix& pm, Triangle tri)
	{
		Triangle newTri;
		multiplyMatrixVector(pm, tri.a, newTri.a);
		multiplyMatrixVector(pm, tri.b, newTri.b);
		multiplyMatrixVector(pm, tri.c, newTri.c);

		newTri.a.x += 1.0;
		newTri.a.y += 1.0;
		newTri.b.x += 1.0;
		newTri.b.y += 1.0;
		newTri.c.x += 1.0;
		newTri.c.y += 1.0;

		newTri.a.x *= 0.5 * pm.screenWidth;
		newTri.a.y *= 0.5 * pm.screenHeight;
		newTri.b.x *= 0.5 * pm.screenWidth;
		newTri.b.y *= 0.5 * pm.screenHeight;
		newTri.c.x *= 0.5 * pm.screenWidth;
		newTri.c.y *= 0.5 * pm.screenHeight;

		int ax = (int)newTri.a.x;
		int ay = pm.screenHeight - (int)newTri.a.y;
		int bx = (int)newTri.b.x;
		int by = pm.screenHeight - (int)newTri.b.y;
		int cx = (int)newTri.c.x;
		int cy = pm.screenHeight - (int)newTri.c.y;

		polygon[0] = Gdiplus::Point(ax, ay);
		polygon[1] = Gdiplus::Point(bx, by);
		polygon[2] = Gdiplus::Point(cx, cy);
	}

	void Mesh::drawWireframe(ProjectionMatrix& pm, Gdiplus::Graphics& gf, Gdiplus::Pen& pen)
	{
		for (Triangle tri : triangles)
		{
			Gdiplus::Point polygon[3];
			getProjectedPolygon(polygon, pm, tri);

			gf.DrawPolygon(&pen, polygon, 3);
		}
	}

	void Mesh::drawFilled(ProjectionMatrix& pm, Gdiplus::Graphics& gf, Gdiplus::Brush& brush)
	{
		for (Triangle tri : triangles)
		{
			Gdiplus::Point polygon[3];
			getProjectedPolygon(polygon, pm, tri);
			
			gf.FillPolygon(&brush, polygon, 3);
		}
	}
}
