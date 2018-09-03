#pragma once

#include "Vec2.h"
#include <vector>

class Entity
{
public:
	Entity(std::vector<Vec2_<float>> poly, Vec2_<float> p = { 0,0 },float s = 1.0f, Color color = Colors::White,float ds=1.0f)
		:
		verticies(std::move(poly)),
		pos(p),
		scale(s),
		c(color),
		downScale(ds)
	{
	}
	const Vec2_<float>& GetPosition() const 
	{
		return pos;
	}
	void SetPosition(Vec2_<float> p)
	{
		pos = p;
	}
	float GetScale()
	{
		return scale;
	}
	void SetScale(float s)
	{
		scale = s;
	}
	void TranslateBy(Vec2_<float> offset)
	{
		pos += offset;
	}
	std::vector<Vec2_<float>> GetPolyline() const 
	{
		auto poly = verticies;
		for (auto& v : poly)
		{
			v *= scale;
			v += pos;
		}
		return poly;
	}
	Color GetColor()const
	{
		return c;
	}
	void SetColor(Color color)
	{
		c = color;
	}
	float GetDownScale()const
	{
		return downScale;
	}
private:
	float scale;
	Vec2_<float> pos;
	std::vector<Vec2_<float>> verticies;
	Color c;
	float downScale;
};