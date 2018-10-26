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
	Plank(Vec2_<float> point, float freeX, float yx, float yn, float f, Color c = Colors::Red);

private:
	
	std::vector<Vec2_<float>> MakeBall(float r, int numPoints);

};