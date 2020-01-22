#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

struct point {
    int x,y;
};

int main() 
{

    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Jump");
    app.setFramerateLimit(60);

    Texture bgr, stair, doodle;

    bgr.loadFromFile("img/background.png");
    stair.loadFromFile("img/stair.png");
    doodle.loadFromFile("img/doodle.png");

    Sprite sBackround(bgr), sStair(stair), sDoodle(doodle);

    point plat[20];

    for (int i=0; i<10; i++) {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 533;
    }

    int x=100, y=100, h=200;
    float dx=0, dy=0;

    while (app.isOpen()) {

        Event e;

        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
        };

        if (Keyboard::isKeyPressed(Keyboard::Right)) x+= 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x-= 3;

        dy += 0.2;
        y+= dy;

        if (y > 500) dy=-10;

        sDoodle.setPosition(x, y);

        if (y<h) {
            for (int i=0; i<10; i++) {
                y=h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533) {
                    plat[i].y=0;
                    plat[i].x=rand() % 400;
                }
            }
        }

        for (int i=0; i<10; i++) {
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) 
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy>0)) dy =-10;
        }

        app.draw(sBackround);
        app.draw(sDoodle);

        for (int i=0; i<10; i++) {

            sStair.setPosition(plat[i].x, plat[i].y);
            app.draw(sStair);
        };

        app.display();
    }

    return 0;
}