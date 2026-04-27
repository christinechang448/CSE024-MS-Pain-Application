#ifndef SHAPE_H
#define SHAPE_H

#include <GL/freeflut.h>
#include <GL/gl.h>

class Shape {
protected:
    bool selected = false;

public:
    virtual void draw() = 0;
    virtual bool contains(float x, float y) = 0;
    virtual void translate(float dx, float dy) = 0;
    virtual void resize(float factor) = 0;
    virtual void setColor(float r, float g, float b) = 0;

    void setSelected(bool s) { 
        selected = s; 
    }
    bool isSelected() const { 
        return selected; 
    }

    virtual ~Shape() {}
};

#endif