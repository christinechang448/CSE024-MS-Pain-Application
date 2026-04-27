#ifndef CIRCLE_H
#define CIRCLE_H

#include <Shape.h>

class Circle : public Shape {
    float x;
    float y;
    float size;
    float r;
    float g;
    float b;

public:
    Circle();
    Circle(float x, float y, float r, float g, float b);

    void draw();
    bool contains(float px, float py);
    void translate(float dx, float dy);
    void resize(float factor);
    void setColor(float nr, float ng, float nb);
};

#endif