#include "Light.hpp"

#define MATH_PI (3.14159265359)

Light::Light(){
    lineVertex.setPrimitiveType(sf::Lines);
    //lightBall.setPrimitiveType(sf::TrianglesFan);
    lightTriangles.setPrimitiveType(sf::Triangles);
}

void Light::getMap(Map level){
    vector<int> wallX, wallY, doorX, doorY;
    level.getWalls(wallX, wallY, doorX, doorY);
    vector<int> linesX;
    vector<int> linesY;
    linesX.resize(wallX.size()/2*4);
    linesY.resize(wallY.size()/2*4);
    for(unsigned int i=0; i<wallX.size(); i+=2){
        linesX[i/2*4] = wallX[i];
        linesY[i/2*4] = wallY[i];
        linesX[i/2*4+1] = wallX[i+1];
        linesY[i/2*4+1] = wallY[i];
        linesX[i/2*4+2] = wallX[i+1];
        linesY[i/2*4+2] = wallY[i+1];
        linesX[i/2*4+3] = wallX[i];
        linesY[i/2*4+3] = wallY[i+1];
    }
    triangleX.resize(linesX.size()); triangleX1.resize(linesX.size());
    triangleY.resize(linesY.size()); triangleY1.resize(linesY.size());
    for(unsigned int i=0; i<linesX.size();i++){
        triangleX[i] = linesX[i];
        triangleY[i] = linesY[i];
        if ((i+1)%4 != 0){
            triangleX1[i] = linesX[i+1];
            triangleY1[i] = linesY[i+1];
        } else {
            triangleX1[i] = linesX[i-3];
            triangleY1[i] = linesY[i-3];
        }
    }
    lineX.resize(linesX.size()); lineX1.resize(linesX.size());
    lineY.resize(linesY.size()); lineY1.resize(linesY.size());
    for(unsigned int i=0; i<linesX.size();i++){
        lineX[i] = linesX[i];
        lineY[i] = linesY[i];
        if ((i+1)%4 != 0){
            lineX1[i] = linesX[i+1];
            lineY1[i] = linesY[i+1];
        } else {
            lineX1[i] = linesX[i-3];
            lineY1[i] = linesY[i-3];
        }
    }
}
/*
void Light::intrasectLines(){
    for (float i=0; i<lightX.size(); i++){
        float f = i*6.28/lightX.size();
        int lightCenterX = mousex;
        int lightCenterY = mousey;
        lightX[i] = lightCenterX + (sin(f) * 500);
        lightY[i] = lightCenterY + (cos(f) * 500);
        for(int c=0; c<linesX.size()-1; c++){
            if (c%5 != 4){
                float s1_x = lightX[i] - lightCenterX;
                float s1_y = lightY[i] - lightCenterY;
                float s2_x = linesX[c+1] - linesX[c];
                float s2_y = linesY[c+1] - linesY[c];
                float s = (-s1_y * (lightCenterX - linesX[c]) + s1_x  * (lightCenterY - linesY[c])) / (-s2_x * s1_y + s1_x * s2_y);
                float t = ( s2_x * (lightCenterY - linesY[c]) - s2_y * (lightCenterX - linesX[c])) / (-s2_x * s1_y + s1_x * s2_y);
                if (s >= 0 && s <= 1 && t >= 0 && t <= 1){
                    lightX[i] = lightCenterX + (t * s1_x);
                    lightY[i] = lightCenterY + (t * s1_y);
                }
            }
        }
    }
}*/
void Light::intrasectLines(){
    triangleX = lineX;
    triangleY = lineY;
    triangleX1 = lineX1;
    triangleY1 = lineY1;

    bool coll = true;
    while (coll){
        coll = false;
        for(unsigned int c=0; c<triangleX.size();c++){
            for(unsigned int i=0; i<lineX.size();i++){
                float s1_x, s1_y, s2_x, s2_y;
                int pointx, pointy;
                if (triangleX[c] > mousex){
                    pointx = triangleX[c]-1;
                } else if (triangleX[c] < mousex){
                    pointx = triangleX[c]+1;
                }
                if (triangleY[c] > mousey){
                    pointy = triangleY[c]-1;
                } else if (triangleY[c] < mousey){
                    pointy = triangleY[c]+1;
                }
                s1_x = pointx - mousex;     s1_y = pointy - mousey;
                s2_x = lineX1[i] - lineX[i];     s2_y = lineY1[i] - lineY[i];

                float s, t;
                s = (-s1_y * (mousex - lineX[i]) + s1_x * (mousey - lineY[i])) / (-s2_x * s1_y + s1_x * s2_y);
                t = ( s2_x * (mousey - lineY[i]) - s2_y * (mousex - lineX[i])) / (-s2_x * s1_y + s1_x * s2_y);

                if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
                {
                    cout << "collision" << endl;
                    coll = true;
                    if (triangleX[c] == triangleX1[c] && triangleY[c] == triangleY1[c]){
                        triangleX[c] = mousex;
                        triangleY[c] = mousey;
                        triangleX1[c] = mousex;
                        triangleY1[c] = mousey;
                    }
                    if (triangleX[c] == triangleX1[c]){
                        if (triangleY[c] > triangleY1[c]){
                            triangleY[c]--;
                        } else if (triangleY[c] < triangleY1[c]){
                            triangleY[c]++;
                        }
                    } else if (triangleY[c] == triangleY1[c]){
                        if (triangleX[c] > triangleX1[c]){
                            triangleX[c]--;
                        } else if (triangleX[c] < triangleX1[c]){
                            triangleX[c]++;
                        }
                    }
                }
            }
            for(unsigned int i=0; i<triangleX.size();i++){
                float s1_x, s1_y, s2_x, s2_y;
                int pointx, pointy;
                if (triangleX1[c] > mousex){
                    pointx = triangleX1[c]-1;
                } else if (triangleX1[c] < mousex){
                    pointx = triangleX1[c]+1;
                }
                if (triangleY1[c] > mousey){
                    pointy = triangleY1[c]-1;
                } else if (triangleY1[c] < mousey){
                    pointy = triangleY1[c]+1;
                }
                s1_x = pointx - mousex;     s1_y = pointy - mousey;
                s2_x = lineX1[i] - lineX[i];     s2_y = lineY1[i] - lineY[i];

                float s, t;
                s = (-s1_y * (mousex - lineX[i]) + s1_x * (mousey - lineY[i])) / (-s2_x * s1_y + s1_x * s2_y);
                t = ( s2_x * (mousey - lineY[i]) - s2_y * (mousex - lineX[i])) / (-s2_x * s1_y + s1_x * s2_y);

                if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
                {
                    cout << "collision" << endl;
                    if ((triangleX[c] == triangleX1[c] && triangleY[c] == triangleY1[c]) || coll){
                        triangleX[c] = mousex;
                        triangleY[c] = mousey;
                        triangleX1[c] = mousex;
                        triangleY1[c] = mousey;
                    } else if (triangleX[c] == triangleX1[c]){
                        coll = true;
                        if (triangleY[c] > triangleY1[c]){
                            triangleY1[c]++;
                        } else if (triangleY[c] < triangleY1[c]){
                            triangleY1[c]--;
                        }
                    } else if (triangleY[c] == triangleY1[c]){
                        coll = true;
                        if (triangleX[c] > triangleX1[c]){
                            triangleX1[c]++;
                        } else if (triangleX[c] < triangleX1[c]){
                            triangleX1[c]--;
                        }
                    }
                }
            }
        }
    }
}


void Light::DrawEffects(sf::RenderWindow &window){
    intrasectLines();
    /*
    lineVertex.resize(lightX.size()*2);
    for (int i=0; i<lightX.size()*2; i+=2){
        lineVertex[i].position = sf::Vector2f(mousex,mousey);
        lineVertex[i+1].position = sf::Vector2f(lightX[i/2],lightY[i/2]);
        lineVertex[i].color = sf::Color::Blue;
        lineVertex[i+1].color = sf::Color::Blue;
    }
    window.draw(lineVertex);
    lineVertex.resize(linesX.size()*2);
    for (int i=0; i<linesX.size()*2-2; i+=2){
        lineVertex[i].position = sf::Vector2f(linesX[i/2],linesY[i/2]);
        lineVertex[i+1].position = sf::Vector2f(linesX[i/2+1],linesY[i/2+1]);
        if (i%5 != 3){
            lineVertex[i].color = sf::Color::Blue;
            lineVertex[i+1].color = sf::Color::Blue;
        } else {
            lineVertex[i].color = sf::Color::Transparent;
            lineVertex[i+1].color = sf::Color::Transparent;
        }
    }

    window.draw(lineVertex);
    lightBall.resize(lightX.size()+2);
    lightBall[0].position = sf::Vector2f(mousex, mousey);
    lightBall[0].color = sf::Color(255,255,255,100);
    for(int i=0; i<lightX.size(); i++){
        lightBall[i+1].position = sf::Vector2f(lightX[i],lightY[i]);
        float dist = sqrt(pow(mousex-lightX[i], 2)+pow(mousey-lightY[i], 2));
        lightBall[i+1].color = sf::Color(255,255,255,(float)100/(float)500*(float)((float)500-dist));
    }
    lightBall[lightX.size()+1].position = sf::Vector2f(lightX[0], lightY[0]);
    float dist = sqrt(pow(mousex-lightX[0], 2)+pow(mousey-lightY[0], 2));
    lightBall[lightX.size()+1].color = sf::Color(255,255,255,(float)100/(float)500*(float)((float)500-dist));
    window.draw(lightBall);*/
    lightTriangles.resize(triangleX.size()*3);
    for(unsigned int i=0; i<triangleX.size(); i++){
        sf::Vertex *triangles = &lightTriangles[i*3];
        triangles[0].position = sf::Vector2f(mousex, mousey);
        triangles[1].position = sf::Vector2f(triangleX[i], triangleY[i]);
        triangles[2].position = sf::Vector2f(triangleX1[i], triangleY1[i]);
        for(int i=0; i<3; i++) triangles[i].color = sf::Color(0,0,255,155);
    }
    lightTriangles[1].color = sf::Color::Red;
    window.draw(lightTriangles);
}

void Light::listenMouse(sf::Event event){
    if (event.type == sf::Event::MouseMoved){
        mousex = event.mouseMove.x;
        mousey = event.mouseMove.y;
    }
}
