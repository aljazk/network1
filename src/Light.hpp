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
        sf::VertexArray lightTriangles;
        vector<int> triangleX, triangleX1;
        vector<int> triangleY, triangleY1;
        vector<int> lineX, lineX1;
        vector<int> lineY, lineY1;
        float mousex, mousey;
};

#endif // LIGHT_H

