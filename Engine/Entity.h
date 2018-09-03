#pragma once

#include "Vec2.h"
#include <vector>

class Entity
{
public:
	Entity(std::vector<Vec2_<float>> poly, Vec2_<float> p = { 0,0 },float s = 1.0f, Color color = Colors::White)
		:
		verticies(std::move(poly)),
		pos(p),
		scale(s),
		c(color)
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
	virtual std::vector<Vec2_<float>> GetPolyline() const 
	{
		auto poly = verticies;
		for (auto& v : poly)
		{
			v *= scale;
			v += pos;
		}
		return poly;
	}
	virtual Color GetColor()const
	{
		return c;
	}
	void SetColor(Color color)
	{
		c = color;
	}
	
protected:
	float scale;
	Vec2_<float> pos;
	std::vector<Vec2_<float>> verticies;
	Color c;
	
};