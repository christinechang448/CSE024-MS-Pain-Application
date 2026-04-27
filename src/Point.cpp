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

void Point::setColor(float nr, float ng, float nb) {
    r = nr;
    g = ng;
    b = nb;
}
