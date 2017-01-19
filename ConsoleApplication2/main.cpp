#include <iostream>
#include <SFML\Graphics.hpp>
#include "ClickGrid.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML window");
	ClickGrid grid(6, sf::Vector2f(50.f, 50.f));

	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				grid.chooseSquare(event.mouseButton.x, event.mouseButton.y);
			}
		}
		
		window.clear();
		
		window.draw(grid);
		
		window.display();
	}

	return 0;
}