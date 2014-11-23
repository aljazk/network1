#include "Map.hpp"

#define MATH_PI (3.14159265359)

Map::Map()
{
    wallObject.setPrimitiveType(sf::Quads);
    circleObject.setFillColor(sf::Color::White);
    batteryObject.setPrimitiveType(sf::Quads);
    batteryPicture.setPrimitiveType(sf::Quads);
    doorObject.setPrimitiveType(sf::Quads);
	batteryTexture.loadFromFile("battery.png");
	batteryTexture.setSmooth(true);
	//doorTexture.loadFromFile("door.png");
	//doorTexture.setSmooth(true);
}

void Map::setBallData(Ball &player){
    //get ball coordiantes
    player.getCoords(ballx, bally);
    //colide with walls
    float dupe = 1.7;
    for(unsigned int i=0;i<wallx.size(); i+=2){
        if (ballx > wallx[i]-25 && ballx < wallx[i+1]-(wallx[i+1]-wallx[i])/2 && bally > wally[i] && bally < wally[i+1]){
            player.setForceX(-player.getSpeedX()*dupe);
            player.setX(wallx[i]-24);
        }
        if (ballx > wallx[i]+(wallx[i+1]-wallx[i])/2 && ballx < wallx[i+1]+25 && bally > wally[i] && bally < wally[i+1]){
            player.setForceX(-player.getSpeedX()*dupe);
            player.setX(wallx[i+1]+25);
        }
        if (ballx > wallx[i] && ballx < wallx[i+1] && bally > wally[i]-25 && bally < wally[i+1]-(wally[i+1]-wally[i])/2){
            player.setForceY(-player.getSpeedY()*dupe);
            player.setY(wally[i]-24);
        }
        if (ballx > wallx[i] && ballx < wallx[i+1] && bally > wally[i]+(wally[i+1]-wally[i])/2 && bally < wally[i+1]+25){
            player.setForceY(-player.getSpeedY()*dupe);
            player.setY(wally[i+1]+25);
        }
        for(unsigned int l=i; l<i+2; l++){
            for(unsigned int j=i; j<i+2;j++){
                float dist = sqrt(pow(ballx-wallx[l], 2)+pow(bally-wally[j], 2));
                if(dist < 24){
                    float f = atan2(bally - wally[j], ballx - wallx[l]);
                    float tx = cos(f);
                    float ty = sin(f);
                    f = abs(tx * player.getSpeedX() + ty * player.getSpeedY()) * dupe;
                    player.setForce(tx*f, ty*f);
                    f = 25-dist;
                    player.addXY(tx*f,ty*f);
                }
            }
        }
    }
    //collide with doors
    for(unsigned int i=0;i<doorx.size(); i+=2){
        for (int c=0; c<4; c++){
            int doorX, doorX1, doorY, doorY1;
            if(c == 0){
                doorX = doorx[i];
                doorX1 = doorx[i]+50;
                doorY = doory[i];
                doorY1 = doory[i+1];
            } else if (c == 1){
                doorX = doorx[i+1]-50;
                doorX1 = doorx[i+1];
                doorY = doory[i];
                doorY1 = doory[i+1];
            } else if (c == 2){
                float doorpos = (((doorx[i+1]-doorx[i])/2)/(float)100)*dooropen[i/2];
                doorX = doorx[i];
                doorX1 = doorx[i]+doorpos;
                doorY = doory[i]+20;
                doorY1 = doory[i+1]-20;
            } else if (c == 3){
                float doorpos = (((doorx[i+1]-doorx[i])/2)/(float)100)*dooropen[i/2];
                doorX = doorx[i+1]-doorpos;
                doorX1 = doorx[i+1];
                doorY = doory[i]+20;
                doorY1 = doory[i+1]-20;
            }

            if (ballx > doorX-25 && ballx < doorX1-(doorX1-doorX)/2 && bally > doorY && bally < doorY1){
                player.setForceX(-player.getSpeedX()*dupe);
                player.setX(doorX-24);
            }
            if (ballx > doorX+(doorX1-doorX)/2 && ballx < doorX1+25 && bally > doorY && bally < doorY1){
                player.setForceX(-player.getSpeedX()*dupe);
                player.setX(doorX1+25);
            }
            if (ballx > doorX && ballx < doorX1 && bally > doorY-25 && bally < doorY1-(doorY1-doorY)/2){
                player.setForceY(-player.getSpeedY()*dupe);
                player.setY(doorY-24);
            }
            if (ballx > doorX && ballx < doorX1 && bally > doorY+(doorY1-doorY)/2 && bally < doorY1+25){
                player.setForceY(-player.getSpeedY()*dupe);
                player.setY(doorY1+25);
            }
            float dist = sqrt(pow(ballx-doorX, 2)+pow(bally-doorY, 2));
            if(dist < 24){
                float f = atan2(bally - doorY, ballx - doorX);
                float tx = cos(f);
                float ty = sin(f);
                f = abs(tx * player.getSpeedX() + ty * player.getSpeedY()) * dupe;
                player.setForce(tx*f, ty*f);
                f = 25-dist;
                player.addXY(tx*f,ty*f);
            }
            dist = sqrt(pow(ballx-doorX1, 2)+pow(bally-doorY1, 2));
            if(dist < 24){
                float f = atan2(bally - doorY1, ballx - doorX1);
                float tx = cos(f);
                float ty = sin(f);
                f = abs(tx * player.getSpeedX() + ty * player.getSpeedY()) * dupe;
                player.setForce(tx*f, ty*f);
                f = 25-dist;
                player.addXY(tx*f,ty*f);
            }
            dist = sqrt(pow(ballx-doorX1, 2)+pow(bally-doorY, 2));
            if(dist < 24){
                float f = atan2(bally - doorY, ballx - doorX1);
                float tx = cos(f);
                float ty = sin(f);
                f = abs(tx * player.getSpeedX() + ty * player.getSpeedY()) * dupe;
                player.setForce(tx*f, ty*f);
                f = 25-dist;
                player.addXY(tx*f,ty*f);
            }
            dist = sqrt(pow(ballx-doorX, 2)+pow(bally-doorY1, 2));
            if(dist < 24){
                float f = atan2(bally - doorY1, ballx - doorX);
                float tx = cos(f);
                float ty = sin(f);
                f = abs(tx * player.getSpeedX() + ty * player.getSpeedY()) * dupe;
                player.setForce(tx*f, ty*f);
                f = 25-dist;
                player.addXY(tx*f,ty*f);
            }
        }
    }
    //colide with circle
    for(unsigned int i=0; i<circx.size(); i++){
        float dist = sqrt(pow(ballx-circx[i], 2)+pow(bally-circy[i], 2));
            if (ccd[i] > 0) ccd[i]--;
            if(dist < 25+crad[i] && ccd[i] == 0){
                float f = atan2(bally - circy[i], ballx - circx[i]);
                float wallang = f*180/MATH_PI;
                wallang += 180;
                f = atan2(player.getSpeedY(), player.getSpeedX());
                float moveang = f*180/MATH_PI;
                moveang += 180;
                float fmoveang = moveang +180;
                if (fmoveang > 360){
                    fmoveang -= 360;
                }
                float base = wallang - fmoveang;
                float out = wallang+base;
                //cout << wallang << " - " << fmoveang  << " = " << base << endl;
                //cout << out << endl;
                f = (MATH_PI/180) * out;
                float tx = cos(f);
                float ty = sin(f);
                f = (player.getSpeedX() + player.getSpeedY())*(dupe-1);
                //cout << " dist: " << dist;
                player.setForce(-tx*abs(f), -ty*abs(f));
                player.setSpeed(0,0);
                f = atan2(bally - circy[i], ballx - circx[i]);
                tx = cos(f);
                ty = sin(f);
                f = 25+(float)crad[i]-dist;
                player.addXY(tx*f,ty*f);
                ccd[i] = 5;
                //cout << " add: " << dist+abs(tx*f)+abs(ty*f) << " (" << tx*f << ")(" << ty*f << ")" << endl; pushout should be ok
            }
        //}
        /*if (dist < 25+crad[i]){
            float f = atan2(bally - circy[i], ballx - circx[i]);
            float tx = cos(f);
            float ty = sin(f);
            f = abs(tx * player.getSpeedX() + ty * player.getSpeedY()) * dupe;
            player.setForce(tx*f, ty*f);
            cout << "getSpeed: " << player.getSpeedX() << " " << player.getSpeedY() << endl;
            cout << tx*f << " " << ty*f << endl;
            f = 24+crad[i]-dist;
            player.setSpeed(0,0);
            player.addXY(tx*f,ty*f);
        }*/
    }
    //take energy from battery
    for (unsigned int i=0; i<battx.size();i++){
        float dist = sqrt(pow(ballx-battx[i]-25, 2)+pow(bally-batty[i], 2));
        if (dist < 50 && battpow[i] > 0){
            battpow[i] -= player.addPower(30, battx[i]+25, batty[i]);
        } else if (battpow[i] < 0) battpow[i] = 0;
    }
}

bool Map::deleteBullet(int x, int y){
    for(unsigned int i=0;i<wallx.size(); i+=2)
        if (x > wallx[i] && x < wallx[i+1] && y > wally[i] && y < wally[i+1])
            return true;
    for(unsigned int i=0; i<circx.size(); i++)
        if (sqrt(pow(x-circx[i], 2)+pow(y-circy[i], 2)) < 2+crad[i])
            return true;
    return false;
}

void Map::drawMap(sf::RenderWindow &window){//make one map.texture for all objects so you can use one draw
    wallObject.resize(400);
    int f = 0;
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            sf::Vertex* quad = &wallObject[f];
            quad[0].position = sf::Vector2f(x*100, y*100);
            quad[1].position = sf::Vector2f(x*100+99, y*100);
            quad[2].position = sf::Vector2f(x*100+99, y*100+99);
            quad[3].position = sf::Vector2f(x*100, y*100+99);
            for(int c=0; c<4; c++) quad[c].color = sf::Color(100,100,100,255);
            f+=4;
        }
    }
    window.draw(wallObject);
    wallObject.clear();
    wallObject.resize(wallx.size()*2);
    for(unsigned int i=0;i<wallx.size();i+=2){
        sf::Vertex* quad = &wallObject[i*2];
        quad[0].position = sf::Vector2f(wallx[i], wally[i]);
        quad[1].position = sf::Vector2f(wallx[i+1], wally[i]);
        quad[2].position = sf::Vector2f(wallx[i+1], wally[i+1]);
        quad[3].position = sf::Vector2f(wallx[i], wally[i+1]);
        for (int c=0; c<4; c++) quad[c].color = sf::Color::White;
    }
    window.draw(wallObject);

    for(unsigned int i=0;i<circx.size();i++){
        circleObject.setPosition(sf::Vector2f(circx[i]-crad[i], circy[i]-crad[i]));
        circleObject.setRadius(crad[i]);
        if(crad[i] > 10) circleObject.setPointCount(crad[i]);
        window.draw(circleObject);
    }
    batteryObject.resize(battx.size()*4);
    batteryPicture.resize(battx.size()*4);
    for(unsigned int i=0;i<battx.size();i++){
        int batteryWidth = 50;
        int batteryHeight = 90;
        float pvl = (float)78/(float)100*abs(battpow[i]-100);
        sf::Vertex* quad = &batteryObject[i*4];
        /*//bottom layer
        quad[0].position = sf::Vector2f(battx[i], batty[i]+batteryHeight);
        quad[1].position = sf::Vector2f(battx[i]+batteryWidth, batty[i]+batteryHeight);
        quad[2].position = sf::Vector2f(battx[i]+batteryWidth, batty[i]+batteryHeight*1.5);
        quad[3].position = sf::Vector2f(battx[i], batty[i]+batteryHeight*1.5);*/
        //power level
        quad[0].position = sf::Vector2f(battx[i]+2, batty[i]+10+pvl);
        quad[1].position = sf::Vector2f(battx[i]+batteryWidth-2, batty[i]+10+pvl);
        quad[2].position = sf::Vector2f(battx[i]+batteryWidth-2, batty[i]+batteryHeight-2);
        quad[3].position = sf::Vector2f(battx[i]+2, batty[i]+batteryHeight-2);
        for (int c=0;c<4;c++) quad[c].color = sf::Color(255,255,51);
        //picture
        quad = &batteryPicture[i*4];
        quad[0].position = sf::Vector2f(battx[i], batty[i]);
        quad[1].position = sf::Vector2f(battx[i]+batteryWidth, batty[i]);
        quad[2].position = sf::Vector2f(battx[i]+batteryWidth, batty[i]+batteryHeight);
        quad[3].position = sf::Vector2f(battx[i], batty[i]+batteryHeight);
        quad[0].texCoords = sf::Vector2f(0,0);
        quad[1].texCoords = sf::Vector2f(batteryWidth,0);
        quad[2].texCoords = sf::Vector2f(batteryWidth,batteryHeight);
        quad[3].texCoords = sf::Vector2f(0,batteryHeight);

    }
    window.draw(batteryObject);
    window.draw(batteryPicture, &batteryTexture);
    doorObject.resize(doorx.size()*8);
    for(unsigned int i=0;i<doorx.size();i+=2){
        sf::Vertex* quad = &doorObject[i*8];
        float doorpos = (((doorx[i+1]-doorx[i])/2)/(float)100)*dooropen[i/2];
        quad[0].position = sf::Vector2f(doorx[i]+20, doory[i]+20);
        quad[1].position = sf::Vector2f(doorx[i]+doorpos, doory[i]+20);
        quad[1].color = sf::Color::Red;
        quad[2].position = sf::Vector2f(doorx[i]+doorpos, doory[i+1]-20);
        quad[3].position = sf::Vector2f(doorx[i], doory[i+1]-20);

        quad[4].position = sf::Vector2f(doorx[i+1]-doorpos, doory[i]+20);
        quad[5].position = sf::Vector2f(doorx[i+1], doory[i]+20);
        quad[6].position = sf::Vector2f(doorx[i+1], doory[i+1]-20);
        quad[7].position = sf::Vector2f(doorx[i+1]-doorpos, doory[i+1]-20);

        quad[8].position = sf::Vector2f(doorx[i], doory[i]);
        quad[9].position = sf::Vector2f(doorx[i]+50, doory[i]);
        quad[10].position = sf::Vector2f(doorx[i]+50, doory[i+1]);
        quad[11].position = sf::Vector2f(doorx[i], doory[i+1]);

        quad[12].position = sf::Vector2f(doorx[i+1]-50, doory[i]);
        quad[13].position = sf::Vector2f(doorx[i+1], doory[i]);
        quad[14].position = sf::Vector2f(doorx[i+1], doory[i+1]);
        quad[15].position = sf::Vector2f(doorx[i+1]-50, doory[i+1]);
    }
    window.draw(doorObject);
    //window.draw(doorObject, &doorTexture);
}

void Map::loadMap(string fileName){
    ifstream mapfile(fileName.c_str());
    string line;
    if (mapfile.is_open()){
        while(getline (mapfile, line)){//45 = '-'; 48 = ';';
            if(line[0] == 'r'){//if object is rectangles
                int n=0;
                int c=1;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                wallx.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                wally.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                wallx.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                }
                wally.push_back(n);

            } else if(line[0] == 'c'){//if object is circle
                int n = 0;
                int c = 1;
                for (int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                circx.push_back(n);
                n = 0;
                for (int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                circy.push_back(n);
                n = 0;
                for (int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                crad.push_back(n);
                ccd.push_back(0);

            } else if(line[0] == 'b'){//if object is battery
                int n = 0;
                int c = 1;
                for (int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                battx.push_back(n);
                n = 0;
                for (int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                batty.push_back(n);
                n = 0;
                for (int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                battpow.push_back(n);

            } else if(line[0] == 'd'){//if object is door
                int n=0;
                int c=1;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                doorx.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                doory.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                    c = i+2;
                }
                doorx.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                }
                doory.push_back(n);
                n = 0;
                for(int i=c; line[i] != 45; i++){
                    n *= 10;
                    n += (int)line[i]-48;
                }
                doorpowr.push_back(n);

                doorpow.push_back(0);
                dooropen.push_back(100);


            } else if (line[0] != 'm' && line[0] != 't'){
                cout << "Map: Unknown object" << endl;
            }
        }
        mapfile.close();
    } else {
        cout << "Map: Cannot load file" << endl;
    }
    unsigned int windowWidth = 1000;
    unsigned int windowHeight = 1000;
    unsigned int squareSize = 40;
    windowWidth /= squareSize;
    windowHeight /= squareSize;
    grid.resize(windowWidth);
    for(unsigned int i=0;i<windowWidth;i++) grid[i].resize(windowHeight);
    for(unsigned int i=0; i<wallx.size(); i+=2){
        int x1 = wallx[i]/squareSize, y1 = wally[i]/squareSize;
        int x2 = wallx[i+1]/squareSize, y2 = wally[i+1]/squareSize;
        for(int x=x1;x<=x2;x++){
            for(int y=y1;y<=y2;y++){
                grid[x][y] = 1;
            }
        }

    }
    for(unsigned int i=0; i<circx.size(); i++){
        int x1 = (circx[i]-crad[i])/squareSize, y1 = (circy[i]-crad[i])/squareSize;
        int x2 = (circx[i]+crad[i])/squareSize, y2 = (circy[i]+crad[i])/squareSize;
        for(int x=x1;x<=x2;x++){
            for(int y=y1;y<=y2;y++){
                grid[x][y] = 1;
            }
        }

    }
    for(unsigned int i=0;i<windowWidth;i++) grid[i].resize(windowHeight);
    for(unsigned int i=0; i<doorx.size(); i+=2){
        int x1 = doorx[i]/squareSize, y1 = doory[i]/squareSize;
        int x2 = doorx[i+1]/squareSize, y2 = doory[i+1]/squareSize;
        for(int x=x1;x<=x2;x++){
            for(int y=y1;y<=y2;y++){
                grid[x][y] = 1;
            }
        }

    }

}

void Map::getGrid(vector< vector<char> > &setGrid){
    setGrid = grid;
}

void Map::getWalls(vector<int> &getWallX,vector<int> &getWallY, vector<int> &getDoorX, vector<int> &getDoorY){
    getWallX = wallx;
    getWallY = wally;
    getDoorX = doorx;
    getDoorY = doory;
}
