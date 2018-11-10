#pragma once
#include"Graphics.h"
#include<vector>


class Drawable
{
private:
	std::vector<Vec2_<float>> _model;
	Color _color;
	Vec2_<float> _translation;
	Vec2_<float> _scale;

public:
	Drawable(std::vector<Vec2_<float>> model, Color c)
		:
		_color(c),
		_model(std::move(model)),
		_scale(1.0f,1.0f),
		_translation(0,0)
	{
	}

	void Translate(Vec2_<float> translate)
	{
		_translation += translate;
	}

	void Scale(float scale)
	{
		_scale *= scale;
		_translation *= scale;
	}

	void SacleIndependent(float  scaleX,float scaleY)
	{
		_scale.x *= scaleX;
		_scale.y *= scaleY;
		_translation.x *= scaleX;
		_translation.y *= scaleY;
	}

	void Render(Graphics& gfx)
	{
		for (auto& v : _model)
		{
			v.x *= _scale.x;
			v.y *= _scale.y;
			v += _translation;
		}
		gfx.DrawClosedPolygone(_model, _color);
	}
};