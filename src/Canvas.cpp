#include <Canvas.h>
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Pentagon.h"
#include "Hexagon.h"
#include <set>

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    current = nullptr;
    selected = nullptr;
}

Canvas::~Canvas() {
    std::set<Shape*> owned;
    for (unsigned int i = 0; i < shapes.size(); i++) {
        owned.insert(shapes[i]);
    }
    for (unsigned int i = 0; i < history.size(); i++) {
        if (history[i].type == DELETE_OP) {
            owned.insert(history[i].shape);
        }
    }
    for (unsigned int i = 0; i < redoStack.size(); i++) {
        if (redoStack[i].type == DELETE_OP) {
            owned.insert(redoStack[i].shape);
        }
    }
    for (std::set<Shape*>::iterator it = owned.begin(); it != owned.end(); ++it) {
        delete *it;
    }
    shapes.clear();
    history.clear();
    redoStack.clear();
    if (current) {
        delete current;
    }
}

void Canvas::clearRedo() {
    std::set<Shape*> live;
    for (unsigned int i = 0; i < shapes.size(); i++) {
        live.insert(shapes[i]);
    }
    for (unsigned int i = 0; i < history.size(); i++) {
        if (history[i].type == DELETE_OP) {
            live.insert(history[i].shape);
        }
    }
    for (unsigned int i = 0; i < redoStack.size(); i++) {
        Op op = redoStack[i];
        if (op.type == ADD_OP && live.find(op.shape) == live.end()) {
            delete op.shape;
        }
    }
    redoStack.clear();
}

void Canvas::eraseShape(Shape* s) {
    for (unsigned int i = 0; i < shapes.size(); i++) {
        if (shapes[i] == s) {
            shapes.erase(shapes.begin() + i);
            return;
        }
    }
}

void Canvas::addRectangle(float x, float y, float r, float g, float b) {
    deselect();
    Shape* s = new Rectangle(x, y, r, g, b);
    shapes.push_back(s);
    Op op = { ADD_OP, s };
    history.push_back(op);
    clearRedo();
}

void Canvas::addCircle(float x, float y, float r, float g, float b) {
    deselect();
    Shape* s = new Circle(x, y, r, g, b);
    shapes.push_back(s);
    Op op = { ADD_OP, s };
    history.push_back(op);
    clearRedo();
}

void Canvas::addTriangle(float x, float y, float base, float height, float r, float g, float b) {
    deselect();
    Shape* s = new Triangle(x, y, base, height, r, g, b);
    shapes.push_back(s);
    Op op = { ADD_OP, s };
    history.push_back(op);
    clearRedo();
}

void Canvas::addPentagon(float x, float y, float length, float r, float g, float b) {
    deselect();
    Shape* s = new Pentagon(x, y, length, r, g, b);
    shapes.push_back(s);
    Op op = { ADD_OP, s };
    history.push_back(op);
    clearRedo();
}

void Canvas::addHexagon(float x, float y, float length, float r, float g, float b) {
    deselect();
    Shape* s = new Hexagon(x, y, length, r, g, b);
    shapes.push_back(s);
    Op op = { ADD_OP, s };
    history.push_back(op);
    clearRedo();
}

void Canvas::clear() {
    deselect();
    std::set<Shape*> owned;
    for (unsigned int i = 0; i < shapes.size(); i++) {
        owned.insert(shapes[i]);
    }
    for (unsigned int i = 0; i < history.size(); i++) {
        if (history[i].type == DELETE_OP) {
            owned.insert(history[i].shape);
        }
    }
    for (unsigned int i = 0; i < redoStack.size(); i++) {
        if (redoStack[i].type == DELETE_OP) {
            owned.insert(redoStack[i].shape);
        }
    }
    for (std::set<Shape*>::iterator it = owned.begin(); it != owned.end(); ++it) {
        delete *it;
    }
    shapes.clear();
    history.clear();
    redoStack.clear();
    if (current) {
        delete current;
        current = nullptr;
    }
}

void Canvas::undo() {
    if (history.empty()) {
        return;
    }
    Op op = history.back();
    history.pop_back();
    if (op.type == ADD_OP) {
        if (op.shape == selected) {
            selected = nullptr;
        }
        op.shape->setSelected(false);
        eraseShape(op.shape);
    }
    else {
        shapes.push_back(op.shape);
    }
    redoStack.push_back(op);
}

void Canvas::redo() {
    if (redoStack.empty()) {
        return;
    }
    Op op = redoStack.back();
    redoStack.pop_back();
    if (op.type == ADD_OP) {
        op.shape->setSelected(false);
        shapes.push_back(op.shape);
    }
    else {
        if (op.shape == selected) {
            selected = nullptr;
        }
        op.shape->setSelected(false);
        eraseShape(op.shape);
    }
    history.push_back(op);
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
        Op op = { ADD_OP, current };
        history.push_back(op);
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
    Shape* s = selected;
    eraseShape(s);
    s->setSelected(false);
    selected = nullptr;
    Op op = { DELETE_OP, s };
    history.push_back(op);
    clearRedo();
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
