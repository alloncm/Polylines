#pragma once
#include "Graphics.h"

class CordinateTransformer
{
public:
	CordinateTransformer(Graphics& g)
		:
		gfx(g)
	{
	}
	void DrawClosedPolygone(std::vector<Vec2_<float>>& poly, Color c)
	{
		Vec2_<float> offset(float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2));
		for (auto& v : poly)
		{
			v.y *= -1.0f;
			v += offset;
		}
		gfx.DrawClosedPolygone(poly, c);
	}
private:
	Graphics& gfx;
};