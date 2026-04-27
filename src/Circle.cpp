#include <Circle.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>

Circle::Circle() {
    x = 0.0;
    y = 0.0;
    radius = 0.15f;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Circle::Circle(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    radius = 0.15f;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Circle::draw() {
    glColor3f(r, g, b);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 36; i++) {
            float angle = 2.0f * M_PI * i / 36.0f;
            glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
    glEnd();

    if (selected) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(x - radius, y - radius);
            glVertex2f(x + radius, y - radius);
            glVertex2f(x + radius, y - radius);
            glVertex2f(x + radius, y + radius);
            glVertex2f(x + radius, y + radius);
            glVertex2f(x - radius, y + radius);
            glVertex2f(x - radius, y + radius);
            glVertex2f(x - radius, y - radius);
        glEnd();
    }
}

bool Circle::contains(float px, float py) {
    float dx = px - x;
    float dy = py - y;
    return dx*dx + dy*dy <= radius*radius;
}

void Circle::translate(float dx, float dy) {
    x += dx;
    y += dy;
}

void Circle::resize(float factor) {
    radius *= factor;
}

void Circle::setColor(float newRed, float newGreen, float newBlue) {
    r = newRed;
    g = newGreen;
    b = newBlue;
}
