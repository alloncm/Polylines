#include "Plank.h"
#include<cmath>

Plank::Plank(Vec2_<float> point, float freeX, float yx, float yn, float f, Color c)
	:
	Entity({},point,1.0,c),
	yMax(yx),
	yMin(yn),
	freePoint(freeX,yMin),
	fat(f)
{
	this->verticies.reserve(4);
	verticies.emplace_back(Vec2_<float>(0,0));
	verticies.emplace_back(Vec2_<float>(0, 0) -Vec2_<float>(0, fat));
	verticies.emplace_back(freePoint - Vec2_<float>(0, fat));
	verticies.emplace_back(freePoint);
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
