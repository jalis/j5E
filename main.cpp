#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "j5E.h"

int main(int argc, char *argv[])
{
	if(argc!=3)
		return 0;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Map");
	window.setFramerateLimit(60);


	sf::Color color;
	color=sf::Color::Green;
    sf::CircleShape circle;
	circle.setOutlineColor(color);
	circle.setOutlineThickness(1.f);
	circle.setFillColor(sf::Color::Transparent);

	sf::CircleShape point;
	point.setFillColor(sf::Color::Red);
	point.setRadius(3.f);

	std::stringstream txtStream;
	sf::Font font;
	if(!font.loadFromFile("Consolas.ttf")) {
		std::cout << "Couldn't load font!" << std::endl;
		return 1;
	}
	sf::Text txt;
	txt.setFont(font);
	txt.setCharacterSize(20);
	txt.setFillColor(sf::Color::Cyan);
	txt.setPosition(20.f, 20.f);

	j5E::point mouse(0.0, 0.0);


	j5E::circle c(400.0, 400.0, 25.0);
	j5E::point c1(400.0, 375.0);
	j5E::point c2(400.0, 425.0);
	j5E::line a({std::atof(argv[1]), std::atof(argv[2])}, {0.0, 0.0});
	sf::Vertex line[2];
	line[0].position=sf::Vector2f(a[0].x, a[0].y);
	circle.setPosition(c.p.x-c.r, c.p.y-c.r);
	circle.setRadius(c.r);

	int n=0;
	j5E::point cols[2];

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

			if(event.type == sf::Event::MouseButtonPressed) {
				a[0].x=event.mouseButton.x;
				a[0].y=event.mouseButton.y;
				line[0].position=sf::Vector2f(a[0].x, a[0].y);
			}

			if(event.type == sf::Event::MouseMoved) {
				a[1].x=event.mouseMove.x;
				a[1].y=event.mouseMove.y;
				line[1].position=sf::Vector2f(a[1].x, a[1].y);
			}
        }

		window.clear();

		window.draw(circle);
		window.draw(line, 2, sf::Lines);

		n=j5E::intersectLineCircle(a, c, cols);
		std::cout << " n:" << n;

		if(n==1) {
			txtStream.str(std::string());
			point.setPosition(cols[0].x-3.f, cols[0].y-3.f);
			window.draw(point);
			txtStream << "(" << cols[0].x << "," << cols[0].y << ")";
			txt.setString(txtStream.str());
			window.draw(txt);
			txt.setPosition(cols[0].x+10.0, cols[0].y-25.0);
		}
		else if(n==2) {
			txtStream.str(std::string());
			point.setPosition(cols[0].x-3.f, cols[0].y-3.f);
			window.draw(point);
			txtStream << "(" << cols[0].x << "," << cols[0].y << ")";
			txt.setString(txtStream.str());
			window.draw(txt);
			txt.setPosition(cols[0].x+10.0, cols[0].y-25.0);

			txtStream.str(std::string());
			point.setPosition(cols[1].x-3.f, cols[1].y-3.f);
			window.draw(point);
			txtStream << "(" << cols[1].x << "," << cols[1].y << ")";
			txt.setString(txtStream.str());
			window.draw(txt);
			txt.setPosition(cols[1].x+10.0, cols[1].y-25.0);
		}
		else if(n==3) {
			txtStream.str(std::string());
			point.setPosition(cols[1].x-3.f, cols[1].y-3.f);
			window.draw(point);
			txtStream << "(" << cols[1].x << "," << cols[1].y << ")";
			txt.setString(txtStream.str());
			window.draw(txt);
			txt.setPosition(cols[1].x+10.0, cols[1].y-25.0);
		}

		std::cout << " mouse:(" << a[1].x << "," << a[1].y << ")" << "                                      ";

        window.display();
    }

    return 0;
}