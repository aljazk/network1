#include "..\include\Light.hpp"

#define MATH_PI (3.14159265359)

Light::Light(){
    lineVertex.setPrimitiveType(sf::Lines);
    lightX.resize(50);
    lightY.resize(50);
}

void Light::getMap(Map level){
    vector<int> wallX, wallY, doorX, doorY;
    level.getWalls(wallX, wallY, doorX, doorY);
    linesX.resize(wallX.size()/2*5);
    linesY.resize(wallY.size()/2*5);
    for(int i=0; i<wallX.size(); i+=2){
        linesX[i/2*5] = wallX[i];
        linesY[i/2*5] = wallY[i];
        linesX[i/2*5+1] = wallX[i+1];
        linesY[i/2*5+1] = wallY[i];
        linesX[i/2*5+2] = wallX[i+1];
        linesY[i/2*5+2] = wallY[i+1];
        linesX[i/2*5+3] = wallX[i];
        linesY[i/2*5+3] = wallY[i+1];
        linesX[i/2*5+4] = wallX[i];
        linesY[i/2*5+4] = wallY[i];
    }
}

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
}


void Light::DrawEffects(sf::RenderWindow &window){
    intrasectLines();
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
}

void Light::listenMouse(sf::Event event){
    if (event.type == sf::Event::MouseMoved){
        mousex = event.mouseMove.x;
        mousey = event.mouseMove.y;
    }
}
