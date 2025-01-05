
#include "breakout/game/app.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace brk
{
	int App::run()
	{
		const float        gameWidth  = 800;
		const float        gameHeight = 600;
		const sf::Vector2f paddleSize(25, 100);
		const float        ballRadius = 10.f;

		sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(gameWidth), static_cast<unsigned int>(gameHeight)}, 32), "Game", sf::Style::Titlebar | sf::Style::Close);
		window.setVerticalSyncEnabled(true);

		// TODO: Setup sound stuff
		//const sf::SoundBuffer ballSoundBuffer(resourcesDir() / "ball.wav");
		//sf::Sound             ballSound(ballSoundBuffer);

		// TODO: Setup textures and handling sprites
		// Create the SFML logo texture:
		//const sf::Texture ballTexture(resourcesDir() / "ball.png");
		//sf::Sprite        ball(sfmlLogoTexture);
		//ball.setPosition({170.f, 50.f});

		sf::RectangleShape leftPaddle;
		leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
		leftPaddle.setOutlineThickness(3);
		leftPaddle.setOutlineColor(sf::Color::Black);
		leftPaddle.setFillColor(sf::Color(100, 100, 200));
		leftPaddle.setOrigin(paddleSize / 2.f);

		sf::Clock clock;
		bool      isPlaying = false;
		while (window.isOpen())
		{
			while (const std::optional event = window.pollEvent())
			{
				// Window closed or escape key pressed: exit
				if (event->is<sf::Event::Closed>() ||
					(event->is<sf::Event::KeyPressed>() &&
					 event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
				{
					window.close();
					break;
				}
			}
		}

		return EXIT_SUCCESS;
	}
}
