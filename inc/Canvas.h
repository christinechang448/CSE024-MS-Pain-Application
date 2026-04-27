#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/canvas.h>
#include <vector>
#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Shape.h"
#include "Scribble.h"

cclass Canvas : public bobcat::Canvas_ {
    std::vector<Point*> points;
    Scribble* scribbles

public:
    Canvas(int x, int y, int w, int h);

    void addPoint(float x, float y, float r, float g, float b, int size);
    void addCircle(float x, float y, float r, float g, float b);
    void addTriangle(float x, float y, float base, float height, float r, float g, float b);
    void addRectangle(float x, float y, float width, float height, float r, float g, float b);
    void addPentagon(float x, float y, float r, float g, float b, float size)
    void clear();

    void undo();
    void startScribble();
    void updateScribble(float x, float y, float r, float g, float b, int size);
    void endScribble();

    void render();

    ~Canvas();
};

#endif