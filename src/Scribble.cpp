#include <Scribble.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

void Scribble::addPoint(float x, float y, float r, float g, float b, int size) {
    points.push_back(new Point(x, y, r, g, b, size));
}

void Scribble::draw(){
    for (unsigned int i = 0; i < points.size(); i++){
        points[i]->draw();
    }

    if (selected && !points.empty()) {
        float minX = points[0]->getX();
        float maxX = minX;
        float minY = points[0]->getY();
        float maxY = minY;
        for (unsigned int i = 1; i < points.size(); i++) {
            float px = points[i]->getX();
            float py = points[i]->getY();
            if (px < minX) {
                minX = px;
            }
            if (px > maxX) {
                maxX = px;
            }
            if (py < minY) {
                minY = py;
            }
            if (py > maxY) {
                maxY = py;
            }
        }
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(minX, minY); 
            glVertex2f(maxX, minY);
            glVertex2f(maxX, minY); 
            glVertex2f(maxX, maxY);
            glVertex2f(maxX, maxY); 
            glVertex2f(minX, maxY);
            glVertex2f(minX, maxY); 
            glVertex2f(minX, minY);
        glEnd();
    }
}

bool Scribble::contains(float x, float y) {
    const float tol = 0.03f;
    for (unsigned int i = 0; i < points.size(); i++) {
        float dx = points[i]->getX() - x;
        float dy = points[i]->getY() - y;
        if (dx*dx + dy*dy <= tol*tol) {
            return true;
        }
    }
    return false;
}

void Scribble::translate(float dx, float dy) {
    for (unsigned int i = 0; i < points.size(); i++) {
        points[i]->setX(points[i]->getX() + dx);
        points[i]->setY(points[i]->getY() + dy);
    }
}

void Scribble::resize(float factor) {
    if (points.empty()){
        return;
    }
    float cx = 0;
    float cy = 0;
    for (unsigned int i = 0; i < points.size(); i++) {
        cx += points[i]->getX();
        cy += points[i]->getY();
    }
    cx /= points.size();
    cy /= points.size();
    for (unsigned int i = 0; i < points.size(); i++) {
        float nx = cx + (points[i]->getX() - cx) * factor;
        float ny = cy + (points[i]->getY() - cy) * factor;
        points[i]->setX(nx);
        points[i]->setY(ny);
    }
}

void Scribble::setColor(float r, float g, float b) {
    for (unsigned int i = 0; i < points.size(); i++) {
        points[i]->setColor(r, g, b);
    }
}

Scribble::~Scribble(){
    for (unsigned int i = 0; i < points.size(); i++){
        delete points[i];
    }
    points.clear();
}
