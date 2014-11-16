#ifndef Ball_H
#define Ball_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

class Ball{
	public:
		Ball();
		void setFps(int);
		void getCoords(int&, int&);
		void getMouseCoords(int&, int&);
		bool getMouseButton();
		float getDmg();
		void spawnBall();
		void addForce(int, float);
		void setForce(float, float);
		void setForceX(float);
		void setForceY(float);
        int getSpeedX();
        int getSpeedY();
        void setSpeed(float, float);
		void setX(int);
		void setY(int);
		void addXY(float, float);
		float addPower(float, int, int);
		float getPower();
		void takePower(float);
		void setang(float);
		void moveBall();
		void listenMouse(sf::Event);
		void drawBall(sf::RenderTarget&);
		void makeLightning(sf::RenderTarget&);
		void setLcoord(int, int);
	private:
		float x,y;
		float fx, fy;
		float sx, sy;
		float drag;
		int fps;
		int lx, ly;
		float power;
		int dmg;
		bool mouseButton;
		int mousex, mousey;
		sf::Texture ballTexture;
		sf::Sprite ballSprite;
		sf::VertexArray lightning;
};

#endif
