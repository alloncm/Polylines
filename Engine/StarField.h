#pragma once
#include<random>
#include"Star.h"
#include"Timer.h"
#include<fstream>
#include"MainWindow.h"
#include"Camera.h"
class StarField
{
private:
	std::vector<Star> entities;
	std::random_device rd;
	std::mt19937 rng;
	float scale;
	Vec2_<int> mousePos;
	Timer timer;
	MainWindow& wnd;
	Camera& camera;

public:
	StarField(MainWindow& m,Camera& c);
	void Update();
	void Draw();

private:
	std::vector<Vec2_<float>> MakeStar(float innerR, float outerR, int numSpikes);
	bool IsStarsCollide(Vec2_<float> pos, float radius);
	void MakeEffects();
};