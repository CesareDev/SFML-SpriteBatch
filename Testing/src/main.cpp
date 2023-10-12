#include <SFML/Graphics.hpp>
#include <SpriteBatch.h>
#include <iostream>
#include <chrono>

constexpr size_t ENTITIES_COUNT = 200;
constexpr unsigned int WIN_W = 800;
constexpr unsigned int WIN_H = 800;

int main()
{
	sf::RenderWindow win(sf::VideoMode(WIN_W, WIN_H), "Test!", sf::Style::Default);

	sf::Event ev;

	sf::Texture tx;
	tx.loadFromFile("res/text.png");

	std::vector<sf::Sprite> v;

	sfex::SpriteBatch b;
	b.Init(tx);

	v.resize(ENTITIES_COUNT);

	srand((unsigned)time(NULL));
	for (int i = 0; i < ENTITIES_COUNT; ++i)
	{
		v[i].setTextureRect({ 0, 0, 32, 32 });
		v[i].setOrigin(16.f, 16.f);

		float x = ((float)rand() / (float)RAND_MAX) * (float)WIN_W;
		float y = ((float)rand() / (float)RAND_MAX) * (float)WIN_H;
		v[i].setPosition(x, y);

		float angle = ((float)rand() / (float)RAND_MAX) * 360.f;
		v[i].setRotation(angle);

		v[i].setColor(sf::Color(i, i, i, i));
	}

	
	while (win.isOpen())
	{
		while (win.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				win.close();
		}

		b.Begin(v.size());

		for (auto& s : v)
			b.Submit(s);

		win.clear(sf::Color::Black);

		win.draw(b);

		win.display();

	}

	return 0;
}