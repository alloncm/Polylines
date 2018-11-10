#pragma once

#include "Vec2.h"
#include <vector>
#include"Colors.h"
#include"Drawable.h"
class Entity
{
public:
	Entity(std::vector<Vec2_<float>> poly, Vec2_<float> p = { 0,0 }, Color color = Colors::White)
		:
		verticies(std::move(poly)),
		pos(p),
		c(color)
	{
		scale = 1.0f;
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

	Drawable GetDrawable() const
	{
		Drawable d(verticies, c);
		d.Scale(scale);
		d.Translate(pos);
		return d;
	}
	void SetModel(std::vector<Vec2_<float>> model)
	{
		verticies = std::move(model);
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