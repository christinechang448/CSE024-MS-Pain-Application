#include "Point.h"
#include <GL/freeglut.h>
#include <GL/gl.h>

Point::Point() {
    x = 0.0;
    y = 0.0;
    size = 7.0f;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Point::Point(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    size = 7.0f;
    this->r = r;
    this->g = g;
    this->b = b;
}

Point::Point(float x, float y, float r, float g, float b, int size) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Point::draw() {
    glEnable(GL_POINT_SMOOTH);
    glColor3f(r, g, b);
    glPointSize(size);

    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();

    if (selected) {
        float rr = size * 0.1f;
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

bool Point::contains(float px, float py) {
    float rr = size * 0.1f;
    float dx = px - x;
    float dy = py - y;
    return dx*dx + dy*dy <= rr*rr;
}

void Point::translate(float dx, float dy) {
    x += dx;
    y += dy;
}

void Point::resize(float factor) {
    size *= factor;
}

void Point::setColor(float nr, float ng, float nb) {
    r = nr;
    g = ng;
    b = nb;
}
