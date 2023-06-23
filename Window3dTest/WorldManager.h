
#pragma once

#include <windows.h>
#include <gdiplus.h>

namespace World
{
	class WorldManager
	{
	private:
		int windowWidth;
		int windowHeight;
		bool keysdown[256];
		double shmoffset;

	public:
		WorldManager();
		void windowResized(int width, int height);
		void keydown(BYTE keycode);
		void keyup(BYTE keycode);
		void drawToWindow(HDC hdc);
	};
}
