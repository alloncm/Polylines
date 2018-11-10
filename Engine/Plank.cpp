#include "Plank.h"
#include<cmath>

Plank::Plank(Vec2_<float> point, float freeX, float yn, float yx, float f, Color c)
	:
	Entity({},point,c),
	yMax(yx - point.y),
	yMin(yn - point.y),
	freePoint(freeX - point.x,yMin),
	fat(f)
{

}

std::vector<Vec2_<float>> Plank::MakeBall(float r, int numPoints)
{
	std::vector<Vec2_<float>> verts;
	verts.reserve(numPoints);

	float delta = (std::cos(0) * 4) / numPoints;
	float count = 0;

	for (int i = 0; i < numPoints; i++)
	{
		verts.emplace_back(Vec2_<float>(r*std::cos(count), r*std::sin(count)));
		count += delta;
	}
	return verts;
}

Drawable Plank::GetDrawable()
{
	std::vector<Vec2_<float>> model;
	model.reserve(4);
	model.emplace_back(0.0f, 0.0f);
	model.emplace_back(freePoint);	
	model.emplace_back(freePoint + Vec2_<float>(0.0f, fat));
	model.emplace_back(Vec2_<float>(0.0f, fat));	
	SetModel(model);
	return Entity::GetDrawable();
}

Vec2_<float> Plank::GetFreePoint()
{
	return freePoint + GetPosition();
}

Vec2_<float> Plank::GetPlankSurfaceVector()
{
	return -freePoint;
}

void Plank::MoveFreeY(float deltaY)
{
	SetFreeY(GetFreePoint().y + deltaY);
}


void Plank::SetFreeY(float yIn)
{
	if (yIn < yMin)
	{
		freePoint.y = yMin;
	}
	else if (yIn < yMax)
	{
		freePoint.y = yMax;
	}
	else
	{
		freePoint.y = yIn;
	}
}
