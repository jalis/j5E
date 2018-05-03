#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>

#include "j5E.h"

void drawArcSFML(double r, double a, double b, double start, double end, sf::RenderWindow *target) {
	sf::Vertex line[2];
	if(end<start) end+=2*M_PI;
	line[0].position=sf::Vector2f(a+r*std::cos(start), b+r*std::sin(start));
	line[0].color=sf::Color::Magenta;
	line[1].color=sf::Color::Magenta;

	do {
		start+=0.1f;
		line[1].position=sf::Vector2f(a+r*std::cos(start), b+r*std::sin(start));
		target->draw(line, 2, sf::Lines);
		line[0].position=line[1].position;
	} while(start<end);
}

int main(int argc, char *argv[])
{
	if(argc!=3)
		return 0;

	std::ios_base::sync_with_stdio(false);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Map");
//	window.setFramerateLimit(60);


	sf::Color color;
	color=sf::Color::Green;
    sf::CircleShape circle;
	circle.setOutlineColor(color);
	circle.setOutlineThickness(1.f);
	circle.setFillColor(sf::Color::Transparent);

	sf::CircleShape point;
	point.setFillColor(sf::Color::Red);
	point.setRadius(3.f);
	point.setOrigin(3.f, 3.f);

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

	sf::Text fpsTxt;
	fpsTxt.setString("0 FPS");
	fpsTxt.setFont(font);
	fpsTxt.setCharacterSize(20);
	fpsTxt.setFillColor(sf::Color::Green);
	fpsTxt.setPosition(window.getSize().x - fpsTxt.getLocalBounds().width - 5.f, 0.f);

	j5E::point mouse(0.0, 0.0);


	j5E::circle c(400.0, 400.0, 25.0);
	j5E::point c1(400.0, 375.0);
	j5E::point c2(400.0, 425.0);

	double astart=std::atan2(c1.y-c.p.y, c1.x-c.p.x);
	double aend=std::atan2(c2.y-c.p.y, c2.x-c.p.x);

	j5E::line a({std::atof(argv[1]), std::atof(argv[2])}, {0.0, 0.0});
	sf::Vertex line[2];
	line[0].position=sf::Vector2f(a[0].x, a[0].y);
	circle.setOrigin(c.r, c.r);
	circle.setPosition(c.p.x, c.p.y);
	circle.setRadius(c.r);

	int n=0;
	j5E::point cols[2];

	sf::Clock clock;
	float curTime=0;
	int frameCount=0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

			if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Button::Left) {
				a[0].x=event.mouseButton.x;
				a[0].y=event.mouseButton.y;
				line[0].position=sf::Vector2f(a[0].x, a[0].y);
			}
			if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Button::Middle) {
				c1.x=event.mouseButton.x;
				c1.y=event.mouseButton.y;
				astart=std::atan2(c1.y-c.p.y, c1.x-c.p.x);
			}
			if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Button::Right) {
				c2.x=event.mouseButton.x;
				c2.y=event.mouseButton.y;
				aend=std::atan2(c2.y-c.p.y, c2.x-c.p.x);
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
#ifdef DEBUG
		std::cout << " n:" << n;
#endif

		if(n==1) {
			txtStream.str(std::string());
			point.setPosition(cols[0].x, cols[0].y);
			window.draw(point);
			txtStream << "(" << cols[0].x << "," << cols[0].y << ")";
			txt.setString(txtStream.str());
			txt.setPosition(cols[0].x+10.0, cols[0].y-25.0);
			window.draw(txt);
		}
		else if(n==2) {
			txtStream.str(std::string());
			point.setPosition(cols[0].x, cols[0].y);
			window.draw(point);
			txtStream << "(" << cols[0].x << "," << cols[0].y << ")";
			txt.setString(txtStream.str());
			txt.setPosition(cols[0].x+10.0, cols[0].y-25.0);
			window.draw(txt);
			
			txtStream.str(std::string());
			point.setPosition(cols[1].x, cols[1].y);
			window.draw(point);
			txtStream << "(" << cols[1].x << "," << cols[1].y << ")";
			txt.setString(txtStream.str());
			txt.setPosition(cols[1].x+10.0, cols[1].y-25.0);
			window.draw(txt);
		}
		else if(n==3) {
			txtStream.str(std::string());
			point.setPosition(cols[1].x, cols[1].y);
			window.draw(point);
			txtStream << "(" << cols[1].x << "," << cols[1].y << ")";
			txt.setString(txtStream.str());
			txt.setPosition(cols[1].x+10.0, cols[1].y-25.0);
			window.draw(txt);
		}


		if((clock.getElapsedTime().asSeconds() + curTime) >= 1.f) {
			curTime+=clock.restart().asSeconds()-1.f;
			txtStream.str(std::string());
			txtStream << frameCount << " FPS";
			fpsTxt.setString(txtStream.str());
			fpsTxt.setPosition(window.getSize().x - fpsTxt.getLocalBounds().width - 5.f, 0.f);
			frameCount=0;
		}
		window.draw(fpsTxt);
		++frameCount;

		drawArcSFML(c.r, c.p.x, c.p.y, astart, aend, &window);
#ifdef DEBUG
		std::cout << " mouse:(" << a[1].x << "," << a[1].y << ")";
		std::cout << "     " << j5E::collisionLineArc(a, c, c1, c2) << "   ";
		std::cout  << "                    \r";
#endif

        window.display();
    }

    return 0;
}