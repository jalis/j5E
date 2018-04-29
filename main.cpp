#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "j5E.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Map");
	window.setFramerateLimit(60);


	sf::Color color;
	color=sf::Color::Green;
    sf::CircleShape shape(100.0);
	shape.setOutlineColor(color);
	sf::Vertex line[2];

	std::stringstream txtStream;
	sf::Font font;
	if(!font.loadFromFile("Consolas.ttf")) {
		std::cout << "Couldn't load font!" << std::endl;
		return 1;
	}
	sf::Text txt;
	txt.setFont(font);
	txt.setCharacterSize(30);
	txt.setFillColor(sf::Color::Cyan);
	txt.setPosition(20.f, 20.f);

	auto chars=j5E::Creature::getCreatures();
	j5E::Creature p1(j5E::circle(100.0, 200.0, 50.0));
	j5E::Creature p2(j5E::circle(200.0, 400.0, 50.0));
	j5E::circle temp;
	j5E::point mouse(0.0, 0.0);

	line[0].position=sf::Vector2f(p1.getCircle().p.x, p1.getCircle().p.y);
	line[1].position=sf::Vector2f(0.f, 0.f);

	std::vector<j5E::point*> cols;

	j5E::point moveTo(0.0, 0.0); 

#ifdef DEBUG

#endif

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::MouseMoved) {
				mouse.x=event.mouseMove.x;
				mouse.y=event.mouseMove.y;
				moveTo.x=mouse.x;
				moveTo.y=mouse.y;
				line[1].position=sf::Vector2f(mouse.x, mouse.y);
			}
        }

        window.clear(sf::Color::Black);

		for(int i=0;i<chars->size();++i) {
			temp=chars->at(i)->getCircle();
			color=sf::Color::Transparent;
			shape.setFillColor(color);
			shape.setOutlineThickness(-1.f);
			shape.setPosition(temp.p.x-temp.r, temp.p.y-temp.r);
			shape.setRadius(temp.r);
			window.draw(shape); 
		}
		if(p1.tryMove(mouse.x, mouse.y, &cols) != 0) {
			for(int i=0;i<cols.size();++i) {
				txtStream << "Collision at: (" << cols.at(i)->x << "," << cols.at(i)->y << ")" << std::endl;
				moveTo.x=cols.at(0)->x;
				moveTo.y=cols.at(0)->y;
			}
		}
		cols.clear();

		txt.setPosition(20.f, 20.f);
		txt.setString(txtStream.str());	
		window.draw(txt);
		txtStream.str("");

		txtStream << "(" << mouse.x << "," << mouse.y << ")";
		txt.setPosition(600.f, 20.f);
		txt.setString(txtStream.str());
		window.draw(txt);
		txtStream.str("");

		temp=p1.getCircle();
		color=sf::Color::Green;
		color.a=100;
		shape.setFillColor(color);
		shape.setOutlineThickness(0.f);
		shape.setPosition(moveTo.x-temp.r, moveTo.y-temp.r);
		shape.setRadius(temp.r);
		window.draw(shape);

		window.draw(line, 2, sf::Lines);

        window.display();
    }

    return 0;
}