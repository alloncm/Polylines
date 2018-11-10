#pragma once
#include"Entity.h"

class Plank : public Entity
{
private:
	float yMax;
	float yMin;
	Vec2_<float> freePoint;
	float fat;

public:
	Plank(Vec2_<float> point, float freeX, float yn, float yx, float f, Color c = Colors::Red);
	Drawable GetDrawable();
	Vec2_<float> GetFreePoint();
	Vec2_<float> GetPlankSurfaceVector();
	void MoveFreeY(float deltaY);
	void SetFreeY(float deltaY);
private:
	
	std::vector<Vec2_<float>> MakeBall(float r, int numPoints);
};