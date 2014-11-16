#include "Enemies.hpp"

#define MATH_PI (3.14159265359)

void getAtan2(float &cx, float &cy, int ang){
    float f = atan2(cx,cy)+(float)ang*MATH_PI/180;
    float dist = sqrt(pow(cx, 2)+pow(cy, 2));
    cx = cos(f)*dist;
    cy = sin(f)*dist;
}

Enemies::Enemies()
{
    enemyVertex.setPrimitiveType(sf::Quads);
    bulletVertex.setPrimitiveType(sf::Quads);
    lineVertex.setPrimitiveType(sf::LinesStrip);
    enemyTexture.loadFromFile("enemy.png");
    enemyTexture.setSmooth(true);
    bulletTexture.loadFromFile("enemy.png");
    bulletTexture.setSmooth(true);
	font.loadFromFile("arial.ttf");
    dmgText.setFont(font);
    dmgText.setStyle(sf::Text::Bold);
    denemyCooldown = 0;
}

void Enemies::drawEnemies(sf::RenderTarget &window){
    enemyVertex.resize(enemyX.size()*4*2);
    for(unsigned int i=0; i<enemyX.size(); i++){
        if (enemyType[i] == 'm'){ //draw miniguns
            sf::Vertex* quad = &enemyVertex[i*4*2];
            quad[0].position = sf::Vector2f(enemyX[i]-25,enemyY[i]-25);
            quad[1].position = sf::Vector2f(enemyX[i]+25,enemyY[i]-25);
            quad[2].position = sf::Vector2f(enemyX[i]+25,enemyY[i]+25);
            quad[3].position = sf::Vector2f(enemyX[i]-25,enemyY[i]+25);
            quad[0].texCoords = sf::Vector2f(45,0);
            quad[1].texCoords = sf::Vector2f(95,0);
            quad[2].texCoords = sf::Vector2f(95,50);
            quad[3].texCoords = sf::Vector2f(45,50);
            float ang = enemyTurretRotation[i];
            if (ang > 360) ang -= 360;
            if (ang < 0) ang += 360;
            float cx,cy;
            cx = -20, cy = -20;
            getAtan2(cx,cy,ang);
            quad[4].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);
            cx = 20, cy = -20;
            getAtan2(cx,cy,ang);
            //quad[5].position = sf::Vector2f(enemyX[i]+21.6*degx,enemyY[i]-21.1*degy);//18, 12
            //quad[5].position = sf::Vector2f(enemyX[i]+18,enemyY[i]-12);//18, 12
            quad[5].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);//18, 12
            cx = 20, cy = 40;
            getAtan2(cx,cy,ang);
            //quad[6].position = sf::Vector2f(enemyX[i]+18,enemyY[i]+68);
            quad[6].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);//18, 12
            cx = -20, cy = 40;
            getAtan2(cx,cy,ang);

            //quad[7].position = sf::Vector2f(enemyX[i]-12,enemyY[i]+68);
            quad[7].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);//18, 12
            quad[4].texCoords = sf::Vector2f(0,0);
            quad[5].texCoords = sf::Vector2f(40,0);
            quad[6].texCoords = sf::Vector2f(40,60);
            quad[7].texCoords = sf::Vector2f(0,60);

            bar.setFillColor(sf::Color::Red);
            bar.setPosition(enemyX[i]-50, enemyY[i]-40);
            bar.setSize(sf::Vector2f(enemyHP[i]*100/100,2));
            window.draw(bar);
            bar.setFillColor(sf::Color::Yellow);
            bar.setPosition(enemyX[i]-50, enemyY[i]-38);
            bar.setSize(sf::Vector2f(enemyEnergy[i]*100/10,2));
            window.draw(bar);
        } else if (enemyType[i] == 't'){//draw tank
            sf::Vertex* quad = &enemyVertex[i*4*2];
            float ang = enemyBottomRotation[i];
            if (ang > 360) ang -= 360;
            if (ang < 0) ang += 360;
            float cx,cy;
            cx = -25, cy = -25;
            getAtan2(cx,cy,ang);
            quad[0].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);
            cx = 25, cy = -25;
            getAtan2(cx,cy,ang);
            quad[1].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);
            cx = 25, cy = 25;
            getAtan2(cx,cy,ang);
            quad[2].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);
            cx = -25, cy = 25;
            getAtan2(cx,cy,ang);
            quad[3].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);
            quad[0].texCoords = sf::Vector2f(100,0);
            quad[1].texCoords = sf::Vector2f(150,0);
            quad[2].texCoords = sf::Vector2f(150,50);
            quad[3].texCoords = sf::Vector2f(100,50);
            ang = enemyTurretRotation[i];
            if (ang > 360) ang -= 360;
            if (ang < 0) ang += 360;
            cx = -20, cy = -20;
            getAtan2(cx,cy,ang);
            quad[4].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);
            cx = 20, cy = -20;
            getAtan2(cx,cy,ang);
            quad[5].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);
            cx = 20, cy = 40;
            getAtan2(cx,cy,ang);
            quad[6].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);
            cx = -20, cy = 40;
            getAtan2(cx,cy,ang);
            quad[7].position = sf::Vector2f(enemyX[i]+cx,enemyY[i]+cy);
            quad[4].texCoords = sf::Vector2f(0,0);
            quad[5].texCoords = sf::Vector2f(40,0);
            quad[6].texCoords = sf::Vector2f(40,60);
            quad[7].texCoords = sf::Vector2f(0,60);

            bar.setFillColor(sf::Color::Red);
            bar.setPosition(enemyX[i]-50, enemyY[i]-40);
            bar.setSize(sf::Vector2f(enemyHP[i]*100/100,2));
            window.draw(bar);
            bar.setFillColor(sf::Color::Yellow);
            bar.setPosition(enemyX[i]-50, enemyY[i]-38);
            bar.setSize(sf::Vector2f(enemyEnergy[i]*100/10,2));
            window.draw(bar);
        }
    }
    window.draw(enemyVertex, &enemyTexture);
    bulletVertex.resize(bulletf.size()*4);
    for(unsigned int i=0; i<bulletf.size(); i++){
        sf::Vertex *quad = &bulletVertex[i*4];
        float cx,cy;
        int texCenterx = 50, texCentery = 55;
        float ang = bulletf[i]*180/MATH_PI;
        cx = -4, cy = -4;
        quad[0].texCoords = sf::Vector2f(texCenterx+cx,texCentery+cy);
        getAtan2(cx,cy,ang);
        quad[0].position = sf::Vector2f(bulletx[i]+cx,bullety[i]+cy);
        cx = 4, cy = -4;
        quad[1].texCoords = sf::Vector2f(texCenterx+cx,texCentery+cy);
        getAtan2(cx,cy,ang);
        quad[1].position = sf::Vector2f(bulletx[i]+cx,bullety[i]+cy);
        cx = 4, cy = 4;
        quad[2].texCoords = sf::Vector2f(texCenterx+cx,texCentery+cy);
        getAtan2(cx,cy,ang);
        quad[2].position = sf::Vector2f(bulletx[i]+cx,bullety[i]+cy);
        cx = -4, cy = 4;
        quad[3].texCoords = sf::Vector2f(texCenterx+cx,texCentery+cy);
        getAtan2(cx,cy,ang);
        quad[3].position = sf::Vector2f(bulletx[i]+cx,bullety[i]+cy);

    }
    window.draw(bulletVertex, &bulletTexture);
}

void Enemies::moveEnemies(Ball &player, int fps, Map &level){
    denemyCooldown -= (float)1/fps;
    int ballx, bally;
    player.getCoords(ballx, bally);
    //rotate turrets
    for (unsigned int i=0; i<enemyX.size(); i++){
        if (enemyEnergy[i] > 1){
            //rotate turret
            float f;
            if (enemySeen[i]){
                f = atan2(bally - enemyY[i], ballx - enemyX[i]);
            } else {
                f = atan2(enemySeenY[i] - enemyY[i], enemySeenX[i] - enemyX[i]);
            }
            float ang = f * 180/MATH_PI;
            float dist = (int)(ang-enemyTurretRotation[i])%360;
            float change;
            if (dist > 0){
                    change = (float)50/fps;
            } else {
                    change = -(float)50/fps;
            }
            if (abs(dist) > 180){
                change = 0 - change;
            }
            enemyTurretRotation[i] += change;
            //spawn bullets
            enemyCooldown[i] -= (float)1/(float)fps;
            if (enemyCooldown[i] <= 0 && dist < 5 && enemySeen[i]){
                f = enemyTurretRotation[i]/180*MATH_PI;
                bulletf.push_back(f);
                bullets.push_back(300);
                enemyBulletTilt[i] = !enemyBulletTilt[i];
                float tx = cos(f);
                float ty = sin(f);
                bulletx.push_back(enemyX[i]+tx*38);
                bullety.push_back(enemyY[i]+ty*38);
                enemyCooldown[i] = .1;
            }
            //move enemy
            if (enemyType[i] == 't'){
                f = atan2(enemyMoveTragetY[i] - enemyY[i], enemyMoveTragetX[i] - enemyX[i]);
                float tx = cos(f);
                float ty = sin(f);
                enemyX[i] += tx*(float)100/fps;
                enemyY[i] += ty*(float)100/fps;
                ang = f * 180/MATH_PI;
                enemyBottomRotation[i] = ang;
            }
        }
    }
    //move bullets
    for(unsigned int i=0; i<bulletf.size(); i++){
        float tx = cos(bulletf[i]);
        float ty = sin(bulletf[i]);
        bulletx[i] += tx*(float)bullets[i]/fps;
        bullety[i] += ty*(float)bullets[i]/fps;
        float dist = sqrt(pow(ballx-bulletx[i], 2)+pow(bally-bullety[i], 2));
        if (bulletx[i] > 1000 || bulletx[i] < 0 || bullety[i] > 1000 || bullety[i] < 0 || dist < 25){
            bulletx.erase (bulletx.begin()+i);
            bullety.erase (bullety.begin()+i);
            bulletf.erase (bulletf.begin()+i);
            bullets.erase (bullets.begin()+i);
            if (dist < 25){
                player.takePower(5);
            }
        }
        if (level.deleteBullet((int)bulletx[i], (int)bullety[i])){
            bulletx.erase (bulletx.begin()+i);
            bullety.erase (bullety.begin()+i);
            bulletf.erase (bulletf.begin()+i);
            bullets.erase (bullets.begin()+i);
        }
    }
}

void Enemies::attackEnemies(Ball &player){
    int mousex, mousey;
    player.getMouseCoords(mousex, mousey);
    int ballx, bally;
    player.getCoords(ballx, bally);
    for (unsigned int i=0; i<enemyX.size(); i++){
        float dist = sqrt(pow(enemyX[i]-mousex, 2)+pow(enemyY[i]-mousey, 2));
        if (dist < 30 && player.getMouseButton() && enemyHP[i] > 0 && player.getPower() > 0){
            enemyHP[i] -= player.getDmg();
        } else if (enemyHP[i] < 0){
            dmgtm.push_back(0);
            dmgt.push_back(enemyOldHP[i]);
            dmgtx.push_back(enemyX[i]-dmgt[i+1]/2);
            dmgty.push_back(enemyY[i]);
            dmgtfade.push_back(255);
            enemyType.erase(enemyType.begin()+i);
            enemyX.erase(enemyX.begin()+i);
            enemyY.erase(enemyY.begin()+i);
            enemyMoveTragetX.erase(enemyMoveTragetX.begin()+i);
            enemyMoveTragetY.erase(enemyMoveTragetY.begin()+i);
            enemyTurretRotation.erase(enemyTurretRotation.begin()+i);
            enemyBottomRotation.erase(enemyBottomRotation.begin()+i);
            enemyEnergy.erase(enemyEnergy.begin()+i);
            enemyOldEnergy.erase(enemyOldEnergy.begin()+i);
            enemyHP.erase(enemyHP.begin()+i);
            enemyCooldown.erase(enemyCooldown.begin()+i);
            enemyOldHP.erase(enemyOldHP.begin()+i);
            enemyBulletTilt.erase(enemyBulletTilt.begin()+i);
            enemySeenX.erase(enemySeenX.begin()+i);
            enemySeenY.erase(enemySeenY.begin()+i);
            enemySeen.erase(enemySeen.begin()+i);
        }
        dist = sqrt(pow(enemyX[i]-ballx, 2)+pow(enemyY[i]-bally, 2));
        if (dist < 50 && enemyEnergy[i] > 0){
            enemyEnergy[i] -= player.addPower(5, enemyX[i], enemyY[i]);
        } else if (enemyEnergy[i] < 0){
            enemyEnergy[i] = 0;
            dmgtm.push_back(1);
            dmgt.push_back(enemyOldEnergy[i]-enemyEnergy[i]);
            dmgtx.push_back(enemyX[i]-dmgt[i+1]/2+1);
            dmgty.push_back(enemyY[i]);
            dmgtfade.push_back(255);
            enemyEnergy[i] = 0;
        }
    }
}

void Enemies::loadEnemies(string fileName){
    ifstream mapfile(fileName.c_str());
    string line;
    if (mapfile.is_open()){
        while(getline (mapfile, line)){//45 = '-'; 48 = ';';
            if(line[0] == 'm'){//if object is mingun
                enemyType.push_back('m');
                int n=0;
                int c=1;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                enemyX.push_back(n);
                enemyMoveTragetX.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                enemyY.push_back(n);
                enemyMoveTragetY.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                enemyTurretRotation.push_back(0);
                enemyBottomRotation.push_back(0);
                enemyEnergy.push_back(10);
                enemyOldEnergy.push_back(10);
                enemyHP.push_back(100);
                enemyOldHP.push_back(100);
                enemyCooldown.push_back(3);
                enemyBulletTilt.push_back(0);
                enemySeenX.push_back(-1);
                enemySeenY.push_back(-1);
                enemySeen.push_back(0);
            } else if (line[0] == 't'){ //object is tank
                enemyType.push_back('t');
                int n=0;
                int c=1;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                enemyX.push_back(n);
                enemyMoveTragetX.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                enemyY.push_back(n);
                enemyMoveTragetY.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                enemyTurretRotation.push_back(0);
                enemyBottomRotation.push_back(0);
                enemyEnergy.push_back(10);
                enemyOldEnergy.push_back(10);
                enemyHP.push_back(100);
                enemyOldHP.push_back(100);
                enemyCooldown.push_back(3);
                enemyBulletTilt.push_back(0);
                enemySeenX.push_back(-1);
                enemySeenY.push_back(-1);
                enemySeen.push_back(0);
            } else if (line[0] != 'r' && line[0] != 'c' && line[0] != 'b' && line[0] != 'd'){
                cout << "Enemy: Unknown object" << endl;
            }
        }
        mapfile.close();
    } else {
        cout << "Enemy: Cannot load file" << endl;
    }
}

void Enemies::test(sf::RenderTarget &window, Map &level, Ball &player){
    sf::Vector2u size = window.getSize();
    int ballx, bally;
    player.getCoords(ballx, bally);
    unsigned int windowWidth = size.x;
    unsigned int windowHeight = size.y;
    unsigned int squareSize = 40;
    windowWidth /= squareSize;
    windowHeight /= squareSize;
    level.getGrid(grid);
    //resize line vertex for view line
    for (unsigned int i=0;i<enemyType.size();i++){
        if (enemyType[i] == 't'){
            //show view line
            //check if enemy can see you
            float dist = sqrt(pow(ballx-enemyX[i], 2)+pow(bally-enemyY[i], 2));
            lineVertex.resize(enemyType.size()*((dist/squareSize)-1));
            lineVertex[i].position = sf::Vector2f(enemyX[i],enemyY[i]);
            if (dist < 2000){
                float f = atan2(bally-enemyY[i],ballx-enemyX[i]);
                float cx = cos(f)*squareSize;
                float cy = sin(f)*squareSize;
                int x = enemyX[i]+cx;
                int y = enemyY[i]+cy;
                bool seen = true;
                for(int c=0;c<(dist/squareSize)-2;c++){
                    x += cx;
                    y += cy;
                    lineVertex[i+c].position = sf::Vector2f(x,y);
                    lineVertex[i+c].color = sf::Color::White;
                    if (grid[x/squareSize][y/squareSize] == 1){
                        seen = false;
                        lineVertex[i+c].color = sf::Color::Red;
                    }
                }
                if (seen){
                    lineVertex[i].color = sf::Color::Green;
                    lineVertex[i+1].color = sf::Color::Green;
                    enemySeenX[i] = ballx;
                    enemySeenY[i] = bally;
                    enemySeen[i] = true;
                } else {
                    enemySeen[i] = false;
                }

            }
            //find shortest path
            int enemyCordX = enemyX[i]/squareSize;
            int enemyCordY = enemyY[i]/squareSize;
            int ballCordX = enemySeenX[i]/squareSize;
            int ballCordY = enemySeenY[i]/squareSize;
            grid[enemyCordX][enemyCordY] = 3;
            if (ballCordX > 0 && ballCordX < (int)windowWidth && ballCordY > 0 && ballCordY < (int)windowHeight)
                grid[ballCordX][ballCordY] = 0;
            if (ballCordX != enemyCordX || ballCordY != enemyCordY){
                vector< vector<int> > pathX, pathY;
                int paths = 1;
                int shortestPath = -1;
                pathX.resize(paths);
                pathY.resize(paths);
                pathX[0].push_back(enemyCordX);
                pathY[0].push_back(enemyCordY);
                grid[enemyCordX][enemyCordY] = 4;
                for(int steps=0; steps<20; steps++){
                    int oldPaths = paths;
                    for(int path=0; path<oldPaths; path++){
                        //cout << "new left " << pathX[1][1] << " " << pathY[1][1] << endl;
                        //cout << "Path " << path << ", Step " << steps << ": " << pathX[path][steps] << " " << pathY[path][steps] << endl;
                        bool newpath = false;
                        if (grid[pathX[path][steps]+1][pathY[path][steps]] != 1 && grid[pathX[path][steps]+1][pathY[path][steps]] != 4 && pathX[path][steps]+1 < (int)windowWidth-1){
                            grid[pathX[path][steps]+1][pathY[path][steps]] = 4;
                            pathX[path].push_back(pathX[path][steps]+1);
                            pathY[path].push_back(pathY[path][steps]);
                            if (pathX[path][steps+1] == ballCordX && pathY[path][steps+1] == ballCordY){
                                shortestPath = path;
                            }
                            newpath = true;
                        }
                        if (grid[pathX[path][steps]-1][pathY[path][steps]] != 1 && grid[pathX[path][steps]-1][pathY[path][steps]] != 4 && pathX[path][steps]-1 > 0){
                            grid[pathX[path][steps]-1][pathY[path][steps]] = 4;
                            if (newpath){
                                paths++;
                                pathX.resize(paths);
                                pathY.resize(paths);
                                pathX[paths-1] = pathX[path];
                                pathY[paths-1] = pathY[path];
                                pathX[paths-1][steps+1] = pathX[path][steps]-1;
                                pathY[paths-1][steps+1] = pathY[path][steps];
                                if (pathX[paths-1][steps+1] == ballCordX && pathY[paths-1][steps+1] == ballCordY){
                                    shortestPath = paths-1;
                                }
                            } else {
                                pathX[path].push_back(pathX[path][steps]-1);
                                pathY[path].push_back(pathY[path][steps]);
                                if (pathX[path][steps+1] == ballCordX && pathY[path][steps+1] == ballCordY){
                                    shortestPath = path;
                                }
                            }
                            newpath = true;
                        }
                        if (grid[pathX[path][steps]][pathY[path][steps]+1] != 1 && grid[pathX[path][steps]][pathY[path][steps]+1] != 4 && pathY[path][steps]+1 < (int)windowHeight-1){
                            grid[pathX[path][steps]][pathY[path][steps]+1] = 4;
                            if (newpath){
                                paths++;
                                pathX.resize(paths);
                                pathY.resize(paths);
                                pathX[paths-1] = pathX[path];
                                pathY[paths-1] = pathY[path];
                                pathX[paths-1][steps+1] = pathX[path][steps];
                                pathY[paths-1][steps+1] = pathY[path][steps]+1;
                                if (pathX[paths-1][steps+1] == ballCordX && pathY[paths-1][steps+1] == ballCordY){
                                    shortestPath = paths-1;
                                }
                            } else {
                                pathX[path].push_back(pathX[path][steps]);
                                pathY[path].push_back(pathY[path][steps]+1);
                                if (pathX[path][steps+1] == ballCordX && pathY[path][steps+1] == ballCordY){
                                    shortestPath = path;
                                }
                            }
                            newpath = true;
                        }
                        if (grid[pathX[path][steps]][pathY[path][steps]-1] != 1 && grid[pathX[path][steps]][pathY[path][steps]-1] != 4 && pathY[path][steps]-1 > 0){
                            grid[pathX[path][steps]][pathY[path][steps]-1] = 4;
                            if (newpath){
                                paths++;
                                pathX.resize(paths);
                                pathY.resize(paths);
                                pathX[paths-1] = pathX[path];
                                pathY[paths-1] = pathY[path];
                                pathX[paths-1][steps+1] = pathX[path][steps];
                                pathY[paths-1][steps+1] = pathY[path][steps]-1;
                                if (pathX[paths-1][steps+1] == ballCordX && pathY[paths-1][steps+1] == ballCordY){
                                    shortestPath = paths-1;
                                }
                            } else {
                                pathX[path].push_back(pathX[path][steps]);
                                pathY[path].push_back(pathY[path][steps]-1);
                                if (pathX[path][steps+1] == ballCordX && pathY[path][steps+1] == ballCordY){
                                    shortestPath = path;
                                }
                            }
                            newpath = true;
                        }
                        if (newpath == false){
                            pathX[path].push_back(pathX[path][steps]);
                            pathY[path].push_back(pathY[path][steps]);
                        }
                        if (shortestPath > -1){
                            break;
                        }
                    }
                    if (shortestPath > -1){
                        break;
                    }
                }
                grid[enemyCordX][enemyCordY] = 3;
                if(shortestPath != -1){
                    for(unsigned int c=0; c<pathX[shortestPath].size();c++){
                        grid[pathX[shortestPath][c]][pathY[shortestPath][c]] = 5;
                    }
                    float dist = sqrt(pow(ballx-enemyX[i], 2)+pow(bally-enemyY[i], 2));
                    if (dist/squareSize > 5){
                        enemyMoveTragetX[i] = (pathX[shortestPath][1]) * squareSize + squareSize/2;
                        enemyMoveTragetY[i] = (pathY[shortestPath][1]) * squareSize + squareSize/2;
                    }
                }
            }
        }
    }
    enemyVertex.resize(windowWidth*windowHeight*4);
    for (unsigned int i=0;i<windowWidth;i++){
        for (unsigned int j=0;j<windowHeight;j++){
            sf::Vertex* quad = &enemyVertex[(i+j*windowWidth)*4];
            quad[0].position = sf::Vector2f(i*squareSize,j*squareSize);
            quad[1].position = sf::Vector2f(i*squareSize+squareSize,j*squareSize);
            quad[2].position = sf::Vector2f(i*squareSize+squareSize,j*squareSize+squareSize);
            quad[3].position = sf::Vector2f(i*squareSize,j*squareSize+squareSize);
            unsigned int trasperencyLevel = 50;
            quad[0].color = sf::Color(255,255,255,trasperencyLevel);
            for(int c=1;c<4;c++)quad[c].color = sf::Color(255,255,255,0);
            if(grid[i][j] == 1){
                for(int c=0;c<4;c++)quad[c].color = sf::Color(255,0,0,trasperencyLevel);
            } else if (grid[i][j] == 2){
                for(int c=0;c<4;c++)quad[c].color = sf::Color(0,255,0,trasperencyLevel);
            } else if (grid[i][j] == 3){
                for(int c=0;c<4;c++)quad[c].color = sf::Color(0,0,255,trasperencyLevel);
            } else if (grid[i][j] == 4){
                for(int c=0;c<4;c++)quad[c].color = sf::Color(255,0,255,trasperencyLevel);
            } else if (grid[i][j] == 5){
                for(int c=0;c<4;c++)quad[c].color = sf::Color(0,255,255,trasperencyLevel);
            }
        }
    }
    //window.draw(enemyVertex);
    window.draw(lineVertex);
    for(unsigned int c=0;c<windowWidth*windowHeight*4;c++) enemyVertex[c].color = sf::Color(255,255,255,255);

}

void Enemies::drawDmg(sf::RenderTarget &window){
    if (denemyCooldown < 0){
        for(unsigned int i=0; i<enemyX.size(); i++){
            if (enemyOldHP[i] > enemyHP[i]){
                dmgtm.push_back(0);
                dmgt.push_back(enemyOldHP[i]-enemyHP[i]);
                dmgtx.push_back(enemyX[i]);
                dmgty.push_back(enemyY[i]);
                dmgtfade.push_back(255);
                enemyOldHP[i] = enemyHP[i];
            }
            if (enemyOldEnergy[i] > enemyEnergy[i]){
                dmgtm.push_back(1);
                dmgt.push_back(enemyOldEnergy[i]-enemyEnergy[i]);
                dmgtx.push_back(enemyX[i]);
                dmgty.push_back(enemyY[i]);
                dmgtfade.push_back(255);
                enemyOldEnergy[i] = enemyEnergy[i];
            }
        }
        denemyCooldown = .5;
    }
    for(unsigned int i=0; i<dmgt.size(); i++){
		std::ostringstream s;
		s << (int)dmgt[i];
		dmgText.setString(s.str());
		if(dmgt[i] > 10)
            dmgText.setCharacterSize(dmgt[i]);
        else
            dmgText.setCharacterSize(10);
		dmgText.setPosition(dmgtx[i],dmgty[i]);
        dmgText.setColor(sf::Color(0,0,255,(int)dmgtfade[i]));
		if (dmgtm[i] == 0)
            dmgText.setColor(sf::Color(255,0,0,(int)dmgtfade[i]));
        else if (dmgtm[i] == 1)
            dmgText.setColor(sf::Color(255,255,0,(int)dmgtfade[i]));
		window.draw(dmgText);
		dmgty[i] -= 0.1;
		dmgtfade[i] -= 0.2;
        if(dmgtfade[i] < 0){
            dmgt.erase(dmgt.begin()+i);
            dmgtm.erase(dmgtm.begin()+i);
            dmgtx.erase(dmgtx.begin()+i);
            dmgty.erase(dmgty.begin()+i);
            dmgtfade.erase(dmgtfade.begin()+i);
        }
    }
}
