#pragma once
#include "Graphics.h"
#include"Drawable.h"
class CordinateTransformer
{
public:
	CordinateTransformer(Graphics& g)
		:
		gfx(g)
	{
	}
	void Draw(Drawable& drawable)
	{
		Vec2_<float> offset(float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2));
		drawable.SacleIndependent(1.0f, -1.0f);
		drawable.Translate(offset);
		drawable.Render(gfx);
	}
private:
	Graphics& gfx;
};