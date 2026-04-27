#ifndef PENTAGON_H
#define PENTAGON_H

#include <Shape.h>

class Pentagon : public Shape {
    float x;
    float y;
    float length;
    float r;
    float g;
    float b;

public:
    Pentagon();
    Pentagon(float x, float y, float length, float r, float g, float b);

    void draw();
    bool contains(float px, float py);
    void translate(float dx, float dy);
    void resize(float factor);
    void setColor(float nr, float ng, float nb);
};

#endif