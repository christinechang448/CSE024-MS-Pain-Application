#include <Triangle.h>
#include <GL/freeglut.h>

Triangle::Triangle() {
    x = 0.0;
    y = 0.0;
    base = 0.25;
    height = 0.25;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Triangle::Triangle(float x, float y, float base, float height, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->base = base;
    this->height = height;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Triangle::draw() {
    glColor3f(r, g, b);

    glBegin(GL_POLYGON);
        glVertex2f(x - base/2, y - height/2);
        glVertex2f(x, y + height/2);
        glVertex2f(x + base/2, y - height/2);
    glEnd();

    if (selected) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(x - base/2, y - height/2);
            glVertex2f(x + base/2, y - height/2);
            glVertex2f(x + base/2, y - height/2);
            glVertex2f(x + base/2, y + height/2);
            glVertex2f(x + base/2, y + height/2);
            glVertex2f(x - base/2, y + height/2);
            glVertex2f(x - base/2, y + height/2);
            glVertex2f(x - base/2, y - height/2);
        glEnd();
    }
}

bool Triangle::contains(float px, float py) {
    float v0x = x - base/2;
    float v0y = y - height/2;
    float v1x = x;
    float v1y = y + height/2;
    float v2x = x + base/2;
    float v2y = y - height/2;

    float d1 = (px - v1x) * (v0y - v1y) - (v0x - v1x) * (py - v1y);
    float d2 = (px - v2x) * (v1y - v2y) - (v1x - v2x) * (py - v2y);
    float d3 = (px - v0x) * (v2y - v0y) - (v2x - v0x) * (py - v0y);

    bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(hasNeg && hasPos);
}

void Triangle::translate(float dx, float dy) {
    x += dx;
    y += dy;
}

void Triangle::resize(float factor) {
    base *= factor;
    height *= factor;
}

void Triangle::setColor(float newRed, float newGreen, float newBlue) {
    r = newRed;
    g = newGreen;
    b = newBlue;
}
