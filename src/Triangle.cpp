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
    float dx = px - x;
    float dy = py - y;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    return dx <= base/2 && dy <= height/2;
}

void Triangle::translate(float dx, float dy) {
    x += dx;
    y += dy;
}

void Triangle::resize(float factor) {
    base *= factor;
    height *= factor;
}

void Triangle::setColor(float nr, float ng, float nb) {
    r = nr; 
    g = ng; 
    b = nb;
}
