#define NOMINMAX
#include "StarField.h"
#include<limits>
StarField::StarField(MainWindow& m, Camera& c)
	:
	wnd(m),
	camera(c),
	entities(),
	rd(),
	rng(rd()),
	scale(0.01),
	mousePos(0, 0),
	timer()
{
	//for benchmarking test 
	std::ofstream ofs("benchmark.txt");
	Timer t;

	std::uniform_real_distribution<float> scale(0.65, 3.0);
	std::uniform_int_distribution<int> xPos(-10000, 10000);
	std::uniform_int_distribution<int> yPos(-7500, 7500);
	std::uniform_int_distribution<int> maxSize(70, 150);
	std::uniform_int_distribution<int> minSize(20, 70);
	std::uniform_int_distribution<int> spikes(3, 15);
	std::uniform_int_distribution<unsigned int> color(0,std::numeric_limits<unsigned int>::max());
	std::uniform_real_distribution<float> downScale(0.4, 0.65);
	std::uniform_real_distribution<float> speedScale(0.001, 0.07);
	std::uniform_real_distribution<float> speedColor(1.0, 3.5);
	Timer total;		//also for benchmark
	for (int i = 0; i <2500; i++)
	{
		float r = maxSize(rng);
		Vec2_<float> pos((float)xPos(rng), (float)yPos(rng));
		float s = scale(rng);
		while (IsStarsCollide(pos, r*s))
		{
			r = maxSize(rng);
			pos.x = (float)xPos(rng);
			pos.y = (float)yPos(rng);
			s = scale(rng);
		}
		auto v = MakeStar(minSize(rng), r, spikes(rng));
		Star ent(v, pos, s, Color(color(rng)), downScale(rng), speedScale(rng), speedColor(rng));
		ofs << "Star #" << i << ": " << (t.Tick()) << std::endl;
		entities.emplace_back(ent);
	}
	ofs << "total time of the operation: " << total.Tick() << std::endl;
}

void StarField::Update()
{
	MakeEffects();
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
	if (eve.GetType() == Mouse::Event::Type::LPress)
	{
		mousePos = eve.GetPos();
	}
	if (eve.LeftIsPressed() && eve.GetType() == Mouse::Event::Type::Move)
	{
		auto pos = eve.GetPos();
		pos = mousePos - pos;
		pos.y *= -1;
		Vec2_<float> vec = Cast(pos);
		vec = vec.Normalize();
		vec *= 20;								//making it move faster
		vec /= camera.GetScale();				//sacling the movement 
		camera.MoveBy(vec);
		mousePos = eve.GetPos();				//saving the last position of the mouse
	}
	if (eve.GetType() == Mouse::Event::Type::WheelUp)
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

std::vector<Vec2_<float>> StarField::MakeStar(float innerR, float outerR, int numSpikes)
{
	std::vector<Vec2_<float>> verts;
	verts.reserve(numSpikes * 2);									//reserve the memory for all the vertices
	float delta = (std::acos(0.0) * 4) / float(numSpikes * 2);			//(std::acos(0.0) * 4) equals 2*pi
	float count = 0;
	for (int i = 0; i < numSpikes; i++)
	{
		verts.emplace_back(Vec2_<float>(outerR*std::cos(count), outerR*std::sin(count)));
		count += delta;
		verts.push_back(Vec2_<float>(innerR*std::cos(count), innerR*std::sin(count)));
		count += delta;
	}
	return verts;
}

bool StarField::IsStarsCollide(Vec2_<float> pos, float radius)
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

void StarField::MakeEffects()
{
	float dt = timer.Tick();
	for (auto& ent : entities)
	{
		ent.Effects(dt);
	}
}

void StarField::Draw()
{
	for (const auto& ent : entities)
	{
		camera.Draw(ent.GetDrawable());
	}
}
