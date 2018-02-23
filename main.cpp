#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <time.h>


bool Collides(sf::Sprite s1, sf::Sprite s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

int main()
{

	srand(time(0));
	sf::RenderWindow arkanode(sf::VideoMode(520, 450), "Teh Arkanode Game!");
	arkanode.setFramerateLimit(60);

	sf::Texture t1, t2, t3, t4;
	t1.loadFromFile("images/blokk.png");
	t2.loadFromFile("images/back.jpg");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/arka.png");

	sf::Sprite sBackground(t2), sBall(t3), sPaddle(t4);
	sPaddle.setPosition(300, 440);
	sBall.setPosition(300, 300);

	sf::Sprite block[1000];

	int n = 0;
	for (int i = 1; i <= 10; i++)
		for (int j = 0; j <= 10; j++)
		{
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}

	float dx = 6, dy = 5;

	while (arkanode.isOpen())
	{
		sf::Event e;
		while (arkanode.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				arkanode.close();
		}

		sBall.move(dx, 0);
		for (int i=0; i<n; i++)
			if (Collides(sBall, block[i])) { block[i].setPosition(-100, 0); dx =-dx; }

		sBall.move(0, dy);
		for (int i = 0; i < n; i++)
			if (Collides(sBall, block[i])) { block[i].setPosition(-100, 0); dy =-dy; };

		sf::Vector2f b = sBall.getPosition();
		if (b.x < 0 || b.x>520) dx = -dx;
		if (b.y < 0 || b.y>450)	dy = -dy;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) sPaddle.move(7, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) sPaddle.move(-7, 0);

		if (Collides(sPaddle, sBall)) dy = -(rand() % 5 + 2);

		arkanode.clear();
		arkanode.draw(sBackground);
		arkanode.draw(sBall);
		arkanode.draw(sPaddle);

		for (int i = 0; i < n; i++)
			arkanode.draw(block[i]);

		arkanode.display();

				
	}
	return 0;
}