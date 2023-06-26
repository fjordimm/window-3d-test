
#include "WorldManager.h"

#include <gdiplus.h>

/*
void drawLine3d(HDC hdc, int width, int height, World::Point p1, World::Point p2);
void drawCube3d(HDC hdc, int width, int height, World::Point p, double scale);
*/

constexpr double NEAR_PLANE = 0.1;
constexpr double FAR_PLANE = 1000.0;
constexpr double FOV = 1.5708; // 90 degrees in radians

namespace World
{
	void addCubeMesh(std::vector<Mesh>& meshes, Vec3d pos, double scale);

	WorldManager::WorldManager()
	{
		windowWidth = 0;
		windowHeight = 0;
		cameraOffset = {0.0, 0.0, 0.0};

		for (int i = 0; i < 256; i++)
		{ keysdown[i] = false; }

		updateProjectionMatrix(projectionMatrix, windowWidth, windowHeight, NEAR_PLANE, FAR_PLANE, FOV);

		// temporary testing lines
		addCubeMesh(meshes, {-50, -50, 100}, 100.0);
	}

	void WorldManager::windowResized(int width, int height)
	{
		windowWidth = width;
		windowHeight = height;
		updateProjectionMatrix(projectionMatrix, windowWidth, windowHeight, NEAR_PLANE, FAR_PLANE, FOV);
	}

	void WorldManager::keydown(BYTE keycode)
	{
		keysdown[keycode] = true;
	}

	void WorldManager::keyup(BYTE keycode)
	{
		keysdown[keycode] = false;
	}

	void WorldManager::drawToWindow(HDC hdc)
	{
		Gdiplus::Graphics gf(hdc);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
		gf.FillRectangle(&brush, 0, 0, windowWidth, windowHeight);

		Gdiplus::Pen pepe(Gdiplus::Color(255, 0, 255, 0));
		Gdiplus::SolidBrush bebe(Gdiplus::Color(255, 0, 255, 0));

		for (Mesh mesh : meshes)
		{
			mesh.drawWireframe(projectionMatrix, gf, pepe);
		}

		if (keysdown['W'])
		{ cameraOffset.z -= 5.0; }

		if (keysdown['S'])
		{ cameraOffset.z += 5.0; }
	}

	void addCubeMesh(std::vector<Mesh>& meshes, Vec3d pos, double scale)
	{
		double x1 = pos.x;
		double y1 = pos.y;
		double z1 = pos.z;
		double x2 = pos.x + scale;
		double y2 = pos.y + scale;
		double z2 = pos.z + scale;

		Mesh mesh;

		// front face
		mesh.addTriangle({ {x1, y1, z1}, {x1, y2, z1}, {x2, y1, z1} });
		mesh.addTriangle({ {x2, y1, z1}, {x1, y2, z1}, {x2, y2, z1} });

		// back face
		mesh.addTriangle({ {x1, y1, z2}, {x1, y2, z2}, {x2, y1, z2} });
		mesh.addTriangle({ {x2, y1, z2}, {x1, y2, z2}, {x2, y2, z2} });

		// left face
		mesh.addTriangle({ {x1, y1, z1}, {x1, y2, z1}, {x1, y1, z2} });
		mesh.addTriangle({ {x1, y1, z2}, {x1, y2, z1}, {x1, y2, z2} });

		// right face
		mesh.addTriangle({ {x2, y1, z1}, {x2, y2, z1}, {x2, y1, z2} });
		mesh.addTriangle({ {x2, y1, z2}, {x2, y2, z1}, {x2, y2, z2} });

		// bottom face
		mesh.addTriangle({ {x1, y1, z1}, {x1, y1, z1}, {x2, y1, z1} });
		mesh.addTriangle({ {x2, y1, z1}, {x1, y1, z2}, {x2, y1, z2} });

		// top face
		mesh.addTriangle({ {x1, y2, z1}, {x1, y2, z1}, {x2, y2, z1} });
		mesh.addTriangle({ {x2, y2, z1}, {x1, y2, z2}, {x2, y2, z2} });

		meshes.push_back(mesh);
	}
}

/*
void drawCube3d(HDC hdc, int width, int height, World::Point p, double scale)
{
	double x = p.x;
	double y = p.y;
	double z = p.z;

	drawLine3d(hdc, width, height, {x, y, z}, {x, y + scale, z});
	drawLine3d(hdc, width, height, {x, y + scale, z}, {x + scale, y + scale, z});
	drawLine3d(hdc, width, height, {x + scale, y + scale, z}, {x + scale, y, z});
	drawLine3d(hdc, width, height, {x + scale, y, z}, {x, y, z});

	drawLine3d(hdc, width, height, {x, y, z}, {x, y, z + scale});
	drawLine3d(hdc, width, height, {x, y + scale, z}, {x, y + scale, z + scale});
	drawLine3d(hdc, width, height, {x + scale, y, z}, {x + scale, y, z + scale});
	drawLine3d(hdc, width, height, {x + scale, y + scale, z}, {x + scale, y + scale, z + scale});

	drawLine3d(hdc, width, height, {x, y, z + scale}, {x, y + scale, z + scale});
	drawLine3d(hdc, width, height, {x, y + scale, z + scale}, {x + scale, y + scale, z + scale});
	drawLine3d(hdc, width, height, {x + scale, y + scale, z + scale}, {x + scale, y, z + scale});
	drawLine3d(hdc, width, height, {x + scale, y, z + scale}, {x, y, z + scale});
}

void drawLine3d(HDC hdc, int width, int height, World::Point p1, World::Point p2)
{
	World::CanvasPoint cp1;
	bool res1 = projectPoint(width, height, p1, cp1);
	World::CanvasPoint cp2;
	bool res2 = projectPoint(width, height, p2, cp2);

	if (!res1 || !res2)
	{ return; }

	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 255, 0));
	gf.DrawLine(&pen, cp1.x, cp1.y, cp2.x, cp2.y);
}
*/
