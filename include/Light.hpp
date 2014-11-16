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
        void intrasectLines();
    private:
        sf::VertexArray lineVertex;
        sf::VertexArray lightBall;
        vector<int> linesX;
        vector<int> linesY;
        vector<int> lightX;
        vector<int> lightY;
        float mousex, mousey;
};

#endif // LIGHT_H

