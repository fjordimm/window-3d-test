
#pragma once

#include <vector>
#include <windows.h>
#include "projection.h"

namespace World
{
	class WorldManager
	{
	private:
		int windowWidth;
		int windowHeight;
		ProjectionMatrix projectionMatrix;
		bool keysdown[256];
		Vec3d cameraOffset;
		std::vector<Mesh> meshes;

	public:
		WorldManager();
		void windowResized(int width, int height);
		void keydown(BYTE keycode);
		void keyup(BYTE keycode);
		void drawToWindow(HDC hdc);
	};
}
