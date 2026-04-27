#include <Canvas.h>
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Pentagon.h"
#include "Hexagon.h"

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    current = nullptr;
    selected = nullptr;
}

Canvas::~Canvas() {
    for (unsigned int i = 0; i < shapes.size(); i++) {
        delete shapes[i];
    }
    shapes.clear();
    for (unsigned int i = 0; i < redoStack.size(); i++) {
        delete redoStack[i];
    }
    redoStack.clear();
    if (current) {
        delete current;
    }
}

void Canvas::clearRedo() {
    for (unsigned int i = 0; i < redoStack.size(); i++) {
        delete redoStack[i];
    }
    redoStack.clear();
}

void Canvas::addRectangle(float x, float y, float r, float g, float b) {
    deselect();
    shapes.push_back(new Rectangle(x, y, r, g, b));
    clearRedo();
}

void Canvas::addCircle(float x, float y, float r, float g, float b) {
    deselect();
    shapes.push_back(new Circle(x, y, r, g, b));
    clearRedo();
}

void Canvas::addTriangle(float x, float y, float base, float height, float r, float g, float b) {
    deselect();
    shapes.push_back(new Triangle(x, y, base, height, r, g, b));
    clearRedo();
}

void Canvas::addPentagon(float x, float y, float length, float r, float g, float b) {
    deselect();
    shapes.push_back(new Pentagon(x, y, length, r, g, b));
    clearRedo();
}

void Canvas::addHexagon(float x, float y, float length, float r, float g, float b) {
    deselect();
    shapes.push_back(new Hexagon(x, y, length, r, g, b));
    clearRedo();
}

void Canvas::clear() {
    deselect();
    for (unsigned int i = 0; i < shapes.size(); i++) {
        delete shapes[i];
    }
    shapes.clear();
    clearRedo();
    if (current) {
        delete current;
        current = nullptr;
    }
}

void Canvas::undo() {
    if (shapes.size() > 0) {
        Shape* s = shapes.back();
        shapes.pop_back();
        if (s == selected) {
            selected = nullptr;
        }
        s->setSelected(false);
        redoStack.push_back(s);
    }
}

void Canvas::redo() {
    if (redoStack.size() > 0) {
        Shape* s = redoStack.back();
        redoStack.pop_back();
        shapes.push_back(s);
    }
}

void Canvas::startScribble() {
    deselect();
    if (current) {
        delete current;
    }
    current = new Scribble();
}

void Canvas::updateScribble(float x, float y, float r, float g, float b, int size) {
    if (current) {
        current->addPoint(x, y, r, g, b, size);
    }
}

void Canvas::endScribble() {
    if (current) {
        shapes.push_back(current);
        current = nullptr;
        clearRedo();
    }
}

Shape* Canvas::hitTest(float x, float y) {
    for (int i = (int)shapes.size() - 1; i >= 0; i--) {
        if (shapes[i]->contains(x, y)) {
            return shapes[i];
        }
    }
    return nullptr;
}

void Canvas::selectAt(float x, float y) {
    deselect();
    Shape* hit = hitTest(x, y);
    if (hit) {
        selected = hit;
        selected->setSelected(true);
    }
}

void Canvas::deselect() {
    if (selected) {
        selected->setSelected(false);
        selected = nullptr;
    }
}

Shape* Canvas::getSelected() const {
    return selected;
}

void Canvas::deleteSelected() {
    if (!selected) {
        return;
    }
    for (unsigned int i = 0; i < shapes.size(); i++) {
        if (shapes[i] == selected) {
            shapes.erase(shapes.begin() + i);
            break;
        }
    }
    delete selected;
    selected = nullptr;
}

void Canvas::moveSelected(float dx, float dy) {
    if (selected) {
        selected->translate(dx, dy);
    }
}

void Canvas::resizeSelected(float factor) {
    if (selected) {
        selected->resize(factor);
    }
}

void Canvas::recolorSelected(float r, float g, float b) {
    if (selected) {
        selected->setColor(r, g, b);
    }
}

void Canvas::bringToFront() {
    if (!selected) {
        return;
    }
    for (unsigned int i = 0; i < shapes.size(); i++) {
        if (shapes[i] == selected) {
            shapes.erase(shapes.begin() + i);
            shapes.push_back(selected);
            break;
        }
    }
}

void Canvas::sendToBack() {
    if (!selected) {
        return;
    }
    for (unsigned int i = 0; i < shapes.size(); i++) {
        if (shapes[i] == selected) {
            shapes.erase(shapes.begin() + i);
            shapes.insert(shapes.begin(), selected);
            break;
        }
    }
}

void Canvas::render() {
    for (unsigned int i = 0; i < shapes.size(); i++) {
        shapes[i]->draw();
    }

    if (current) {
        current->draw();
    }
}
