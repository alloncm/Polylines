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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ct(gfx),
	ent(MakeStar(75,150)),
	camera(ct)
{
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

void Game::ComposeFrame()
{
	auto verts = ent.GetPolyline();
	ent.SetPosition({ 100,100 });
	ent.SetScale(0.6);
	camera.DrawClosedPolygone(verts, Colors::White);
}

