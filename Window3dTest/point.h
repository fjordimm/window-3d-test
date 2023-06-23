
#pragma once

namespace World
{
	struct Point
	{
		double x;
		double y;
		double z;
	};

	struct CanvasPoint
	{
		int w;
		int h;
	};

	CanvasPoint project(int width, int height, Point p)
	{
		double x = p.x;
		double y = p.y;
		double z = p.z / width;

		CanvasPoint ret;
		ret.w = (int)(x / z) / 2 + width / 2;
		ret.h = (int)(y / z) / 2 + height / 2;

		return ret;
	}
}
