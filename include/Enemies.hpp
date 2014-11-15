#ifndef ENEMIES_H
#define ENEMIES_H

#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Map.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

class Enemies
{
    public:
        Enemies();
        void drawEnemies(sf::RenderTarget&);
        void moveEnemies(Ball &player, int, Map &level);
        void attackEnemies(Ball &player);
        void loadEnemies(string);
        void drawDmg(sf::RenderTarget&);
        void test(sf::RenderTarget&, Map &level, Ball &player);
    private:
        sf::VertexArray enemyVertex;
        sf::VertexArray bulletVertex;
        sf::VertexArray lineVertex;
        sf::Texture enemyTexture;
        sf::Texture bulletTexture;
        sf::RectangleShape bar;
        sf::Text dmgText;
        sf::Font font;
        float ang;
        vector< vector<char> > grid;

        vector<float> enemyX, enemyY, enemyMoveTragetX, enemyMoveTragetY;
        vector<int> enemySeenX, enemySeenY;
        vector<float> enemyTurretRotation, enemyBottomRotation, enemyEnergy, enemyOldEnergy, enemyHP, enemyOldHP, enemyCooldown;
        vector<char> enemyType;
        vector<bool> enemyBulletTilt, enemySeen;
        //vector<float> tax, tay, tar, tae, taolde, tahp, taoldhp, tacd;
        //vector<bool> tabm;
        vector<float> bulletx, bullety, bulletf;
        vector<int> bullets;
        vector<int> dmgtm;
        vector<float> dmgt, dmgtx, dmgty, dmgtfade;
        float denemyCooldown;
};

#endif // ENEMIES_H
