#include <iostream>
#include <SFML\Graphics.hpp>
#include "ClickGrid.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML window");
	ClickGrid grid1(5, 100, sf::Vector2f(50.f, 50.f), 1);
	//ClickGrid grid2(3, sf::Vector2f(400.f, 400.f));

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
				if (event.mouseButton.button == sf::Mouse::Left) {
					grid1.chooseSquare(event.mouseButton.x, event.mouseButton.y);
					//grid2.chooseSquare(event.mouseButton.x, event.mouseButton.y);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					//make waves
				}
				else {
					std::cout << "weird mouse button press" << std::endl;
				}
			}
		}
		grid1.update();
		
		window.clear();
		
		window.draw(grid1);
		//window.draw(grid2);
		
		window.display();
	}

	return 0;
}

/*
Todo:
-Work on chooseSquare, isnt working right on higher resolutions
*/