#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

class Map
{
    public:
        Map();
        void drawMap(sf::RenderWindow&);
        void setBallData(Ball &player);
        bool deleteBullet(int,int);
        void loadMap(string);
        void getGrid(vector < vector<char> >&);
        void getWalls(vector<int>&, vector<int>&, vector<int>&, vector<int>&);
    private:
        int ballx, bally;
        vector<int> wallx, wally;
        vector<int> circx, circy, crad, ccd;
        vector<int> battx, batty;
        vector<float> battpow;
        vector<int> doorx, doory, doorpowr;
        vector<float> doorpow, dooropen;
        vector< vector<char> > grid;
        sf::VertexArray wallObject;
        sf::CircleShape circleObject;
        sf::VertexArray batteryObject;
        sf::VertexArray batteryPicture;
		sf::Texture batteryTexture;
        sf::VertexArray doorObject;
		//sf::Texture doorTexture;
};

#endif // MAP_H
