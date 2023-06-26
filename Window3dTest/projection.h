
#pragma once

#include <vector>
#include <windows.h>
#include <gdiplus.h>

namespace World
{
	struct Vec3d
	{
		double x;
		double y;
		double z;
	};

	struct Triangle
	{
		Vec3d a;
		Vec3d b;
		Vec3d c;
	};

	struct ProjectionMatrix
	{
		int screenWidth;
		int screenHeight;
		double mat[4][4] = {0.0};
	};

	void updateProjectionMatrix(ProjectionMatrix& pm, int screenWidth, int screenHeight, double nearPlane, double farPlane, double fov);

	class Mesh
	{
	private:
		std::vector<Triangle> triangles;
		void getProjectedPolygon(Gdiplus::Point polygon[3], ProjectionMatrix& pm, Triangle tri);
	public:
		Mesh();
		void addTriangle(Triangle tri);
		void drawWireframe(ProjectionMatrix& pm, Gdiplus::Graphics& gf, Gdiplus::Pen& pen);
		void drawFilled(ProjectionMatrix& pm, Gdiplus::Graphics& gf, Gdiplus::Brush& brush);
	};
}
