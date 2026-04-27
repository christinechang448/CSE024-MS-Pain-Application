#include <Hexagon.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>

Hexagon::Hexagon() {
    x = 0.0;
    y = 0.0;
    length = 0.15;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Hexagon::Hexagon(float x, float y, float length, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Hexagon::draw() {
    glColor3f(r, g, b);

    glBegin(GL_POLYGON);
        for (int i = 0; i < 6; i++) {
            float angle = 2.0f * M_PI * i / 6.0f;
            glVertex2f(x + length * cos(angle), y + length * sin(angle));
        }
    glEnd();

    if (selected) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2);
        float rr = length;
        glBegin(GL_LINES);
            glVertex2f(x - rr, y - rr); glVertex2f(x + rr, y - rr);
            glVertex2f(x + rr, y - rr); glVertex2f(x + rr, y + rr);
            glVertex2f(x + rr, y + rr); glVertex2f(x - rr, y + rr);
            glVertex2f(x - rr, y + rr); glVertex2f(x - rr, y - rr);
        glEnd();
    }
}

bool Hexagon::contains(float px, float py) {
    float dx = px - x;
    float dy = py - y;
    return dx*dx + dy*dy <= length*length;
}

void Hexagon::translate(float dx, float dy) {
    x += dx;
    y += dy;
}

void Hexagon::resize(float factor) {
    length *= factor;
}

void Hexagon::setColor(float nr, float ng, float nb) {
    r = nr;
    g = ng;
    b = nb;
}
