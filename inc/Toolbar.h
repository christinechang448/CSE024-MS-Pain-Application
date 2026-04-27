#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <bobcat_ui/all.h>
#include <Enums.h>

class Toolbar : public bobcat::Group {
    bobcat::Image*  pencilButton;
    bobcat::Image*  eraserButton;
    bobcat::Image*  selectorButton;
    bobcat::Image*  circleButton;
    bobcat::Image*  triangleButton;
    bobcat::Image*  rectangleButton;
    bobcat::Image*  pentagonButton;
    bobcat::Image*  hexagonButton;
    bobcat::Image*  enlargeButton;
    bobcat::Image*  shrinkButton;
    bobcat::Image*  bringFrontButton;
    bobcat::Image*  sendBackButton;
    bobcat::Image*  undoButton;
    bobcat::Image*  redoButton;
    bobcat::Image*  clearButton;

    TOOL tool;
    ACTION action;

    void deselectAllTools();
    void visualizeSelectedTool();
    void onClick(bobcat::Widget* sender);

public:
    Toolbar(int x, int y, int w, int h);

    TOOL getTool() const;
    ACTION getAction() const;
};

#endif
