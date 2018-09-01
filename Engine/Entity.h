#pragma once

#include "Vec2.h"
#include <vector>

class Entity
{
public:
	Entity(std::vector<Vec2_<float>> poly)
		:
		verticies(std::move(poly)),
		pos({0,0}),
		scale(1.0f)
	{
	}
	const Vec2_<float>& GetPosition()
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
	std::vector<Vec2_<float>> GetPolyline()
	{
		auto poly = verticies;
		for (auto& v : poly)
		{
			v *= scale;
			v += pos;
		}
		return poly;
	}
private:
	float scale;
	Vec2_<float> pos;
	std::vector<Vec2_<float>> verticies;
};