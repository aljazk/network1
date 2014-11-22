#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Map.hpp"
#include "Enemies.hpp"
#include "Light.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define MATH_PI (3.14159265359)

using namespace std;

void wait(){
    cin.ignore();
}

int main()
{

    // create the window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1000,1000), "My window", sf::Style::Default, settings);
	window.setKeyRepeatEnabled(false);

	// create font
	sf::Font font;
	font.loadFromFile("arial.ttf");

	// create text
	sf::Text text;
	text.setFont(font);

	// define fps components
	sf::Clock clock;
	float fps = 1;

    string mapname = "map.txt";

    //create map
    Map level;
    level.loadMap(mapname);

    // create ball for player
    Ball player;
    player.spawnBall();

    Enemies enemy;
    enemy.loadEnemies(mapname);

    Light light;
    light.getMap(level);

	// start loop
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            player.listenMouse(event);
            light.listenMouse(event);
		}
		// wasd key events


		// clear window

        window.clear(sf::Color::Blue);

		// do game stuff


		//draw map
		level.drawMap(window);
		level.setBallData(player);

        if(fps > 10) enemy.moveEnemies(player, fps, level);
        enemy.attackEnemies(player);
        enemy.drawEnemies(window);
        enemy.drawDmg(window);
        enemy.test(window, level, player);
		//draw player
		player.setFps(fps);

        player.drawBall(window);
		player.moveBall();
        player.makeLightning(window);

		light.DrawEffects(window);

		// end the current frame
		float currentTime = clock.restart().asSeconds();
		fps = 1.f / currentTime;
		// display fps
		std::ostringstream s;
		s << fps << endl << player.getSpeedX() << " " << player.getSpeedY() << endl << player.getPower();
		text.setString(s.str());
		text.setCharacterSize(10);
		text.setColor(sf::Color::White);
		text.setPosition(10,10);
		window.draw(text);


		// draw stuff on window
        window.display();
        //wait();
    }


    return 0;
}
