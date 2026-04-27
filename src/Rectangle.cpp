#include "Rectangle.h"
#include <GL/freeglut.h>

Rectangle::Rectangle() {
    x = 0.0;
    y = 0.0;
    width = 0.2;
    height = 0.2;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Rectangle::Rectangle(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    width = 0.2;
    height = 0.2;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Rectangle::draw() {
    glColor3f(r, g, b);

    glBegin(GL_POLYGON);
        glVertex2f(x - width/2, y + height/2);
        glVertex2f(x + width/2, y + height/2);
        glVertex2f(x + width/2, y - height/2);
        glVertex2f(x - width/2, y - height/2);
    glEnd();

    if (selected) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(x - width/2, y - height/2);
            glVertex2f(x + width/2, y - height/2);
            glVertex2f(x + width/2, y - height/2);
            glVertex2f(x + width/2, y + height/2);
            glVertex2f(x + width/2, y + height/2);
            glVertex2f(x - width/2, y + height/2);
            glVertex2f(x - width/2, y + height/2);
            glVertex2f(x - width/2, y - height/2);
        glEnd();
    }
}

bool Rectangle::contains(float px, float py) {
    float dx = px - x;
    float dy = py - y;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    return dx <= width/2 && dy <= height/2;
}

void Rectangle::translate(float dx, float dy) {
    x += dx;
    y += dy;
}

void Rectangle::resize(float factor) {
    width *= factor;
    height *= factor;
}

void Rectangle::setColor(float nr, float ng, float nb) {
    r = nr; 
    g = ng; 
    b = nb;
}
