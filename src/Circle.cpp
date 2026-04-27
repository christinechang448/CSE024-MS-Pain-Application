#include "Circle.h"
#include <GL/freeglut.h>
#include <GL/gl.h>

Circle::Circle() {
    x = 0.0;
    y = 0.0;
    size = 60.0f;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Circle::Circle(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    size = 60.0f;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Circle::draw() {
    glEnable(GL_POINT_SMOOTH);
    glColor3f(r, g, b);
    glPointSize(size);

    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();

    if (selected) {
        float rr = size * 0.005f + 0.01f;
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(x - rr, y - rr); glVertex2f(x + rr, y - rr);
            glVertex2f(x + rr, y - rr); glVertex2f(x + rr, y + rr);
            glVertex2f(x + rr, y + rr); glVertex2f(x - rr, y + rr);
            glVertex2f(x - rr, y + rr); glVertex2f(x - rr, y - rr);
        glEnd();
    }
}

bool Circle::contains(float px, float py) {
    float rr = size * 0.005f;
    float dx = px - x;
    float dy = py - y;
    return dx*dx + dy*dy <= rr*rr;
}

void Circle::translate(float dx, float dy) {
    x += dx;
    y += dy;
}

void Circle::resize(float factor) {
    size *= factor;
}

void Circle::setColor(float nr, float ng, float nb) {
    r = nr; g = ng; b = nb;
}
