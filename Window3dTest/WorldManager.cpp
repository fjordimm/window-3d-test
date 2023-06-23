
#include "WorldManager.h"
#include "point.h"

void drawCube3d(HDC hdc, int height, int width, double x, double y, double z, double scale);
void drawLine3d(HDC hdc, int height, int width, double x1, double y1, double z1, double x2, double y2, double z2);

namespace World
{
	WorldManager::WorldManager()
	{
		this->windowWidth = 0;
		this->windowHeight = 0;
		this->shmoffset = 0.0;

		for (int i = 0; i < 256; i++)
		{ this->keysdown[i] = false; }
	}

	void WorldManager::windowResized(int width, int height)
	{
		this->windowWidth = width;
		this->windowHeight = height;
	}

	void WorldManager::keydown(BYTE keycode)
	{
		this->keysdown[keycode] = true;
	}

	void WorldManager::keyup(BYTE keycode)
	{
		this->keysdown[keycode] = false;
	}

	void WorldManager::drawToWindow(HDC hdc)
	{
		Gdiplus::Graphics gf(hdc);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
		gf.FillRectangle(&brush, 0, 0, this->windowWidth, this->windowHeight);

		drawCube3d(hdc, this->windowHeight, this->windowWidth, -100, -100, 300 + shmoffset, 200);
		drawCube3d(hdc, this->windowHeight, this->windowWidth, -350, -100, 300 + shmoffset, 200);
		drawCube3d(hdc, this->windowHeight, this->windowWidth, 150, -100, 300 + shmoffset, 200);

		if (this->keysdown['W'])
		{
			this->shmoffset -= 5.0;
		}

		if (this->keysdown['S'])
		{
			this->shmoffset += 5.0;
		}
	}
}

void drawCube3d(HDC hdc, int height, int width, double x, double y, double z, double scale)
{
	drawLine3d(hdc, height, width, x, y, z, x, y + scale, z);
	drawLine3d(hdc, height, width, x, y + scale, z, x + scale, y + scale, z);
	drawLine3d(hdc, height, width, x + scale, y + scale, z, x + scale, y, z);
	drawLine3d(hdc, height, width, x + scale, y, z, x, y, z);

	drawLine3d(hdc, height, width, x, y, z, x, y, z + scale);
	drawLine3d(hdc, height, width, x, y + scale, z, x, y + scale, z + scale);
	drawLine3d(hdc, height, width, x + scale, y, z, x + scale, y, z + scale);
	drawLine3d(hdc, height, width, x + scale, y + scale, z, x + scale, y + scale, z + scale);

	drawLine3d(hdc, height, width, x, y, z + scale, x, y + scale, z + scale);
	drawLine3d(hdc, height, width, x, y + scale, z + scale, x + scale, y + scale, z + scale);
	drawLine3d(hdc, height, width, x + scale, y + scale, z + scale, x + scale, y, z + scale);
	drawLine3d(hdc, height, width, x + scale, y, z + scale, x, y, z + scale);
}

void drawLine3d(HDC hdc, int height, int width, double x1, double y1, double z1, double x2, double y2, double z2)
{
	z1 /= width;
	z2 /= width;

	int x1p = (int)(x1 / z1);
	int y1p = (int)(y1 / z1);

	int x2p = (int)(x2 / z2);
	int y2p = (int)(y2 / z2);

	x1p = x1p / 2 + width / 2;
	x2p = x2p / 2 + width / 2;
	y1p = y1p / 2 + height / 2;
	y2p = y2p / 2 + height / 2;

	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 255, 0));
	gf.DrawLine(&pen, x1p, height - y1p, x2p, height - y2p);
}
