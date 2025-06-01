#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Renderer.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(1200, 900), "Mario");
	sf::Clock deltaClock; //для одинакового времени работы игры на любых пк
	Renderer renderer(window);

	window.setFramerateLimit(60);
	Begin(window);
	while (window.isOpen()) {

		float deltaTime = deltaClock.restart().asSeconds();

		sf::Event event{};
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
				paused = !paused;
		}

		Update(deltaTime);

		window.clear();

		window.setView(camera.GetView(window.getSize()));
		Render(renderer);

		window.setView(camera.GetUIView());
		RenderUI(renderer);

		window.display();
	}
}



