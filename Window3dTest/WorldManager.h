
#pragma once

#include <windows.h>
#include <gdiplus.h>

namespace World
{
	class WorldManager
	{
	private:
		UINT windowWidth;
		UINT windowHeight;

	public:
		WorldManager(UINT windowWidth, UINT windowHeight);
		void windowResized(UINT width, UINT height);
		void keydown(UINT keycode);
		void keyup(UINT keycode);
		void drawToWindow(HDC hdc);
	};
}
