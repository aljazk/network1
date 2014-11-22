#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

class Light
{
    public:
        Light();
        void getMap(Map);
        void DrawEffects(sf::RenderWindow&);
        void listenMouse(sf::Event);
        void intrasectLines(int, int);
    private:
        sf::VertexArray lineVertex;
        sf::VertexArray lightBall;
        sf::VertexArray lightTriangles;
        sf::Texture light;
        sf::RenderTexture lightBlend;
        sf::RenderTexture lightsBlend;
        sf::Sprite displayLight;
        sf::Sprite addLight;
        sf::RenderStates states;
        vector<int> triangleX, triangleX1;
        vector<int> triangleY, triangleY1;
        vector<int> quadX, quadX1;
        vector<int> quadY, quadY1;
        float mousex, mousey;
};

#endif // LIGHT_H

