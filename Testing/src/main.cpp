#include <SFML/Graphics.hpp>
#include <SpriteBatch.h>
#include <iostream>

int main()
{
	sf::RenderWindow win(sf::VideoMode(720, 720), "Test!", sf::Style::Default);
	win.setVerticalSyncEnabled(true);

	sf::Event ev;

	sf::Texture tx;
	tx.loadFromFile("res/text.png");

	std::vector<sf::Sprite> v;
	srand((unsigned)time(NULL));

	v.resize(255);
	for (int i = 0; i < 255; ++i)
	{
		v[i].setTexture(tx);
		v[i].setTextureRect({ 0, 0, 32, 32 });
		v[i].setOrigin(16.f, 16.f);

		float x = ((float)rand() / (float)RAND_MAX) * 720.f;
		float y = ((float)rand() / (float)RAND_MAX) * 720.f;
		v[i].setPosition(x, y);

		float angle = ((float)rand() / (float)RAND_MAX) * 360.f;
		v[i].setRotation(angle);

		v[i].setColor(sf::Color(i, i, i, i));
	}

	sfex::SpriteBatch b;
	b.Init(tx);

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