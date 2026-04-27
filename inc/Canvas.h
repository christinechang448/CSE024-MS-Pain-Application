#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/canvas.h>
#include <vector>
#include "Shape.h"
#include "Scribble.h"

class Canvas : public bobcat::Canvas_ {
    std::vector<Shape*> shapes;
    std::vector<Shape*> redoStack;
    Shape* selected;
    Scribble* current;

    void clearRedo();

public:
    Canvas(int x, int y, int w, int h);

    void addRectangle(float x, float y, float r, float g, float b);
    void addCircle(float x, float y, float r, float g, float b);
    void addTriangle(float x, float y, float base, float height, float r, float g, float b);
    void addPentagon(float x, float y, float length, float r, float g, float b);
    void addHexagon(float x, float y, float length, float r, float g, float b);
    void clear();

    void undo();
    void redo();
    void startScribble();
    void updateScribble(float x, float y, float r, float g, float b, int size);
    void endScribble();

    Shape* hitTest(float x, float y);
    void selectAt(float x, float y);
    void deselect();
    Shape* getSelected() const;
    void deleteSelected();
    void moveSelected(float dx, float dy);
    void resizeSelected(float factor);
    void recolorSelected(float r, float g, float b);
    void bringToFront();
    void sendToBack();

    void render();

    ~Canvas();
};

#endif