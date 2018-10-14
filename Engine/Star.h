#pragma once
#include"Entity.h"
#include"Colors.h"
class Star :public Entity
{
public:
	Star(std::vector<Vec2_<float>> poly, Vec2_<float> p = { 0,0 }, float s = 1.0f, Color color = Colors::White, float ds = 1.0f, float ss = 1.0f, float sc = 1.0f)
		:
		Entity(std::move(poly), p, s, color),
		downScale(ds),
		speedScale(ss),
		curScale(scale),
		shrink(true),
		speedColor(sc),
		curTime(0.0f),
		white(false)
	{
	}
	float GetDownScale()const
	{
		return downScale;
	}
	float GetSpeedScale()const
	{
		return speedScale;
	}
	void Effects(float dt)
	{
		ShrinkEffect();
		ColorEffect(dt);
	}
	virtual std::vector<Vec2_<float>> GetPolyline() const override
	{
		auto poly = verticies;
		for (auto& v : poly)
		{
			v *= curScale;
			v += pos;
		}
		return poly;
	}
	/*
	virtual Color GetColor()const override
	{
		if (white)
		{
			return Colors::White;
		}
		return c;
	}
	*/
private:
	void ShrinkEffect()
	{
		if (curScale > downScale && shrink)
		{
			curScale -= speedScale;
			if (curScale <= downScale)
			{
				curScale = downScale;
				shrink = false;
			}
		}
		else if (curScale < scale && !shrink)
		{
			curScale += speedScale;
			if (curScale >= scale)
			{
				curScale = scale;
				shrink = true;
			}
		}
	}
	void ColorEffect(float dt)
	{
		/*
		curTime += dt;
		if (curTime >= speedColor)
		{
			white = !white;
			curTime = 0.0f;
		}
		*/
		this->c.SetA(0.0);
	}
	
private:
	float downScale;
	float curScale;
	float speedScale;
	bool shrink;
	float speedColor;
	float curTime;
	bool white;
};