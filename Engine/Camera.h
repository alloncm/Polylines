#pragma once

#include "CordinateTransformer.h"

class Camera
{
public:
	Camera(CordinateTransformer& c)
		:
		ct(c),
		pos({0,0}),
		scale(1.0f)
	{
	}

	void MoveBy(Vec2_<float> dPos)
	{
		pos += dPos;
	}
	const Vec2_<float>& GetPosition()
	{
		return pos;
	}
	void SetScale(float s)
	{
		scale = s;
	}
	float GetScale()
	{
		return scale;
	}
	void Draw(Drawable& draw)
	{
		draw.Translate(-pos);
		draw.Scale(scale);
		ct.Draw(draw);
	}
private:
	Vec2_<float> pos;
	float scale;
	CordinateTransformer& ct;
};