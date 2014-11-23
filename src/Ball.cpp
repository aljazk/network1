#include "Ball.hpp"

#define MATH_PI (3.14159265359)

int random(int min, int max){
	for (int i=0; i<time(NULL)%256; i++){
		rand();
	}
    int r = rand();
    max++;
	max -= min;
	r = rand() % max + min;
    return r;
}

Ball::Ball(){
    //load all textures and set sprite textures
	ballTexture.loadFromFile("ball.png");
	ballTexture.setSmooth(true);
	ballSprite.setTexture(ballTexture);
	lightning.setPrimitiveType(sf::LinesStrip);
	drag = 0.9;
	power = 50;
	lx = 0;
	ly = 0;
	mouseButton = 0;
	dmg = 30;
}

void Ball::setFps(int getfps){
    fps = getfps;
}

void Ball::getCoords(int &getX, int &getY){
    getX = x;
    getY = y;
}

void Ball::getMouseCoords(int &getX, int &getY){
    getX = mousex;
    getY = mousey;
}

bool Ball::getMouseButton(){
    return mouseButton;
}

float Ball::getDmg(){
    return (float)dmg/(float)fps;
}

void Ball::spawnBall(){
    x = 50;
    y = 50;
    fx = 0;
    fy = 0;
    sx = 0;
    sy = 0;
}

void Ball::addForce(int n, float power){
    fx += sin(n*MATH_PI/180) *power;
    fy -= cos(n*MATH_PI/180) *power;
}

void Ball::setForce(float setfx, float setfy){
    fx = setfx/fps;
    fy = setfy/fps;
}
void Ball::setForceX(float setfx){
    fx = setfx/fps;
}
void Ball::setForceY(float setfy){
    fy = setfy/fps;
}

int Ball::getSpeedX(){
    return (int)sx*fps;
}

int Ball::getSpeedY(){
    return (int)sy*fps;
}

void Ball::setSpeed(float setsx, float setsy){
    sx = setsx/fps;
    sy = setsy/fps;
}

void Ball::setX(int setx){
    x = setx;
}

void Ball::setY(int sety){
    y = sety;
}

void Ball::addXY(float setx, float sety){
    x += setx;
    y += sety;
}

float Ball::addPower(float addp, int slx, int sly){
    power += addp/fps;
    lx = slx;
    ly = sly;
    return addp/fps;
}

float Ball::getPower(){
    return power;
}

void Ball::takePower(float take){
    power -= take;
    if (power < 0) power = 0;
}

void Ball::moveBall(){
    power = 11;
    float addfx=0, addfy=0;
    int acc = 150;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        addfy -= (float)acc/fps;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        addfy += (float)acc/fps;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        addfx -= (float)acc/fps;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        addfx += (float)acc/fps;
    }
    if (abs(addfx)+abs(addfy) == acc*2){
        addfx *= 0.7;
        addfy *= 0.7;
    }
    if (addfx != 0 || addfy != 0){
        power -= (float)1/fps;
        if (power < 0) power = 0;
    }
    sx += fx;
    sy += fy;
    if (power != 0){
        sx += addfx;
        sy += addfy;
    }
    sx -= (drag*sx)/fps;
    sy -= (drag*sy)/fps;
    fx = 0;
    fy = 0;
    x += sx/fps;
    y += sy/fps;
    lx = 0;
    ly = 0;
}

void Ball::listenMouse(sf::Event event){
    if (event.type == sf::Event::MouseButtonReleased){
        if (event.mouseButton.button == sf::Mouse::Left){
            mouseButton = 0;
        }
    } else if (event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            mouseButton = 1;
        }
    }
    if (event.type == sf::Event::MouseMoved){
        mousex = event.mouseMove.x;
        mousey = event.mouseMove.y;
    }
}

void Ball::drawBall(sf::RenderTarget &window){
    ballSprite.setPosition(x-25,y-25);
    window.draw(ballSprite);
    int lights = 100;
    if (power/10 < 100)
        lights = (int)power/10;
    if (!lx && !ly){
        int joints = 6;
        lightning.resize(joints*lights);
        for (int j = 0; j < lights; j++){
            sf::Vertex* light = &lightning[j*joints];
            light[0].position = sf::Vector2f(x,y);
            light[0].color = sf::Color::Transparent;
            light[1].position = sf::Vector2f(x,y);
            light[1].color = sf::Color(255,255,51,30);
            float ang = random(0,360)+180;
            if (ang > 360) ang -= 360;
            ang *= MATH_PI/180;
            float xbase = cos(ang);
            float ybase = sin(ang);
            int nx = x;
            int ny = y;
            for(int i=2; i<joints-1; i++){
                nx +=(25/joints)*xbase+(random(0,6)-3);
                ny +=(25/joints)*ybase+(random(0,6)-3);
                light[i].position = sf::Vector2f(nx,ny);
                light[i].color = sf::Color(255,255,51,200);
            }
            light[joints-1].position = sf::Vector2f(x+25*xbase,y+25*ybase);
            light[joints-1].color = sf::Color::Transparent;
        }
    } else {
        if (lights > 50)
            lights = 50;
        float dist = sqrt(pow(x-lx, 2)+pow(y-ly, 2));
        int joints = (dist)/4;
        if (joints < 3)
            joints = 3;
        lightning.resize(joints*lights);
        for (int j=0; j < lights; j++){
            float f = atan2(y - ly, x - lx);
            f = f*180/MATH_PI;
            sf::Vertex* light = &lightning[j*joints];
            light[0].position = sf::Vector2f(x,y);
            light[0].color = sf::Color::Transparent;
            light[1].position = sf::Vector2f(x,y);
            light[1].color = sf::Color(255,255,51,30);
            float ang = f+180;
            if (ang > 360) ang -= 360;
            ang *= MATH_PI/180;
            float xbase = cos(ang);
            float ybase = sin(ang);
            int nx = x;
            int ny = y;
            for(int i=2; i<joints-1; i++){
                f = atan2(ny - ly, nx - lx);
                f = f*180/MATH_PI;
                ang = f+180;
                if (ang > 360) ang -= 360;
                ang *= MATH_PI/180;
                xbase = cos(ang);
                ybase = sin(ang);
                nx +=(dist/joints*0.845)*xbase+(random(0,6)-3);
                ny +=(dist/joints*0.845)*ybase+(random(0,6)-3);
                light[i].position = sf::Vector2f(nx,ny);
                light[i].color = sf::Color(255,255,51,200);
            }
            light[joints-1].position = sf::Vector2f(lx,ly);
            light[joints-1].color = sf::Color::Transparent;

        }
    }

    window.draw(lightning);


    /*
    lang ++;
    if (lang > 360){
        lang = 0;
    }
    float xbase = sin(ang);
    float ybase = cos(ang);
    cout << xbase << " " << ybase << endl;
    float r = random(0,6);
    r -= 3;
    r /= 10;
    lightning[1].position = sf::Vector2f(x+5*(xbase+r),y+5*(ybase-r));
    r = random(0,5);
    r -= 2.5;
    r /= 10;
    lightning[2].position = sf::Vector2f(x+10*(xbase+r),y+10*(ybase-r));
    r = random(0,3);
    r -= 1.5;
    r /= 10;
    lightning[3].position = sf::Vector2f(x+15*(xbase+r),y+15*(ybase-r));
    r = random(0,1);
    r -= 0.5;
    r /= 10;
    lightning[4].position = sf::Vector2f(x+20*(xbase+r),y+20*(ybase-r));
    lightning[5].position = sf::Vector2f(x+25*xbase,y+25*ybase);*/
}

void Ball::makeLightning(sf::RenderTarget &window){
    if (mouseButton && power > 0){
        power -= (float)1/fps;
        float dist = sqrt(pow(x-mousex, 2)+pow(y-mousey, 2));
        int joints = (dist)/10;
        lightning.resize(joints);
        float f = atan2(y - mousey, x - mousex);
        f = f*180/MATH_PI;
        sf::Vertex* light = &lightning[0];
        light[0].position = sf::Vector2f(x,y);
        light[0].color = sf::Color::Transparent;
        light[1].position = sf::Vector2f(x,y);
        light[1].color = sf::Color(255,255,51,30);
        float ang = f+180;
        if (ang > 360) ang -= 360;
        ang *= MATH_PI/180;
        float xbase = cos(ang);
        float ybase = sin(ang);
        int nx = x;
        int ny = y;
        for(int i=2; i<joints-1; i++){
            f = atan2(ny - mousey, nx - mousex);
            f = f*180/MATH_PI;
            ang = f+180;
            if (ang > 360) ang -= 360;
            ang *= MATH_PI/180;
            xbase = cos(ang);
            ybase = sin(ang);
            nx +=(dist/joints*0.87)*xbase+(random(0,10)-5);
            ny +=(dist/joints*0.87)*ybase+(random(0,10)-5);
            light[i].position = sf::Vector2f(nx,ny);
            light[i].color = sf::Color(255,255,51,200);
        }
        light[joints-1].position = sf::Vector2f(mousex,mousey);
        light[joints-1].color = sf::Color::Transparent;

        window.draw(lightning);
    } else if (power < 0) power = 0;
}

