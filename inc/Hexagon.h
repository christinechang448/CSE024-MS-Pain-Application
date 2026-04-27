#ifndef HEXAGON_H
#define HEXAGON_H

#include <Shape.h>

class Hexagon : public Shape {
    float x;
    float y;
    float length;
    float r;
    float g;
    float b;

public:
    Hexagon();
    Hexagon(float x, float y, float length, float r, float g, float b);

    void draw();
    bool contains(float px, float py);
    void translate(float dx, float dy);
    void resize(float factor);
    void setColor(float newRed, float newGreen, float newBlue);
};

#endif