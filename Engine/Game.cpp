/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ct(gfx),
	entities(),
	camera(ct),
	rd(),
	rng(rd()),
	scale(0.01),
	mousePos(0,0)
{
	std::numeric_limits<unsigned int> nl;
	std::uniform_real_distribution<float> scale(0.3,5.0);
	std::uniform_int_distribution<int> xPos(-3000, 3000);
	std::uniform_int_distribution<int> yPos(-1500, 1500);
	std::uniform_int_distribution<int> maxSize(50, 200);
	std::uniform_int_distribution<int> minSize(20, 70);
	std::uniform_int_distribution<int> spikes(3, 15);
	std::uniform_int_distribution<unsigned int> color(0,nl.max() );
	std::uniform_real_distribution<float> downScale(0.1, 0.9);
	std::uniform_real_distribution<float> speedScale(0.05, 0.5);

	for (int i = 0; i <200; i++)
	{
		float r = maxSize(rng);
		Vec2_<float> pos ( (float)xPos(rng),(float)yPos(rng) );
		float s = scale(rng);
		while (IsStarsCollide(pos, r*s))
		{
			r = maxSize(rng);
			pos.x = (float)xPos(rng);
			pos.y = (float)yPos(rng);
			s = scale(rng);
		}
		auto v = MakeStar(minSize(rng),r , spikes(rng));
		Entity ent (v, pos, s, Color(color(rng)),downScale(rng));

		entities.emplace_back(ent);
	}

}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		camera.MoveBy({ 0,5 });
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		camera.MoveBy({ 0,-5 });
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		camera.MoveBy({ 5,0 });
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		camera.MoveBy({ -5,0 });
	}
	auto eve = wnd.mouse.Read();
	if (eve.GetType()==Mouse::Event::Type::LPress)
	{
		mousePos = eve.GetPos();
	}
	if (eve.LeftIsPressed()&&eve.GetType()==Mouse::Event::Type::Move)
	{
		auto pos = eve.GetPos();
		pos =  mousePos - pos;
		pos.y *= -1;
		Vec2_<float> vec = Cast(pos);
		vec = vec.Normalize();
		vec *= 10;
		camera.MoveBy(vec);
	}
	if ( eve.GetType() == Mouse::Event::Type::WheelUp)
	{
		camera.SetScale(camera.GetScale() + scale);
	}
	if (eve.GetType() == Mouse::Event::Type::WheelDown)
	{
		camera.SetScale(camera.GetScale() - scale);
		if (camera.GetScale() < scale)
		{
			camera.SetScale(scale);
		}
	}
	
}

std::vector<Vec2_<float>> Game::MakeStar(float innerR, float outerR, int numSpikes)
{	
	std::vector<Vec2_<float>> verts;
	verts.reserve(numSpikes * 2);									//reserve the memory for all the vertices
	float delta = (std::acos(0.0) * 4) / float(numSpikes * 2);			//(std::acos(0.0) * 4) equals 2*pi
	float count = 0;
	for (int i = 0; i < numSpikes; i++)
	{
		verts.emplace_back( Vec2_<float>(outerR*std::cos(count), outerR*std::sin(count)));
		count += delta;
		verts.push_back(Vec2_<float>(innerR*std::cos(count), innerR*std::sin(count)));
		count += delta;
	}
	return verts;
}

bool Game::IsStarsCollide(Vec2_<float> pos, float radius)
{
	for (const auto& ent : entities)
	{
		auto vec = ent.GetPolyline();
		float r = std::max(vec[0].Distance(ent.GetPosition()), vec[1].Distance(ent.GetPosition()));
		float dis = pos.Distance(ent.GetPosition());
		if (r + radius > dis)
		{
			return true;
		}
	}
	return false;
}

void Game::ComposeFrame()
{
	for (const auto& ent : entities)
	{
		camera.DrawClosedPolygone(ent.GetPolyline(), ent.GetColor());
	}
}

