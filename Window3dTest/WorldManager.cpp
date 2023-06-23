
#include "WorldManager.h"

namespace World
{
	WorldManager::WorldManager(UINT windowWidth, UINT windowHeight)
	{
		this->windowWidth = windowWidth;
		this->windowHeight = windowHeight;
	}

	void WorldManager::windowResized(UINT width, UINT height)
	{
		this->windowWidth = width;
		this->windowHeight = height;
	}

	void WorldManager::keydown(UINT keycode)
	{ }

	void WorldManager::keyup(UINT keycode)
	{ }

	void WorldManager::drawToWindow(HDC hdc)
	{
		Gdiplus::Graphics gf(hdc);
		Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 255));
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));

		gf.DrawLine(&pen, 0, 0, this->windowWidth, this->windowHeight);
	}
}
