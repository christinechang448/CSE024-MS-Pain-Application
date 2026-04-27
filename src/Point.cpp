#include <Point.h>
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

Point::Point(float x, float y) {
    this->x = x;
    this->y = y;
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
}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

float Point::getR() const {
    return r;
}

float Point::getG() const {
    return g;
}

float Point::getB() const {
    return b;
}

int Point::getSize() const {
    return size;
}

void Point::setX(float x) {
    this->x = x;
}

void Point::setY(float y) {
    this->y = y;
}

void Point::setColor(float newRed, float newGreen, float newBlue) {
    r = newRed;
    g = newGreen;
    b = newBlue;
}
