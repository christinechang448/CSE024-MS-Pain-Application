#include "Toolbar.h"
#include <FL/Enumerations.H>
using namespace bobcat;

void Toolbar::deselectAllTools() {
    pencilButton->color(FL_BACKGROUND_COLOR);
    eraserButton->color(FL_BACKGROUND_COLOR);
    selectorButton->color(FL_BACKGROUND_COLOR);
    circleButton->color(FL_BACKGROUND_COLOR);
    triangleButton->color(FL_BACKGROUND_COLOR);
    rectangleButton->color(FL_BACKGROUND_COLOR);
    pentagonButton->color(FL_BACKGROUND_COLOR);
    hexagonButton->color(FL_BACKGROUND_COLOR);
}

void Toolbar::visualizeSelectedTool() {
    if (tool == PENCIL){
        pencilButton->color(FL_WHITE);
    }
    else if (tool == ERASER){
        eraserButton->color(FL_WHITE);
    }
    else if (tool == SELECTOR){
        selectorButton->color(FL_WHITE);
    }
    else if (tool == CIRCLE){
        circleButton->color(FL_WHITE);
    }
    else if (tool == TRIANGLE){
        triangleButton->color(FL_WHITE);
    }
    else if (tool == RECTANGLE){
        rectangleButton->color(FL_WHITE);
    }
    else if (tool == PENTAGON){
        pentagonButton->color(FL_WHITE);
    }
    else if (tool == HEXAGON){
        hexagonButton->color(FL_WHITE);
    }
}

void Toolbar::onClick(bobcat::Widget* sender) {
    deselectAllTools();
    action = NONE;

    if (sender == pencilButton){
        tool = PENCIL;
    }
    else if (sender == eraserButton){
        tool = ERASER;
    }
    else if (sender == selectorButton){
        tool = SELECTOR;
    }
    else if (sender == circleButton){
        tool = CIRCLE;
    }
    else if (sender == triangleButton){
        tool = TRIANGLE;
    }
    else if (sender == rectangleButton){
        tool = RECTANGLE;
    }
    else if (sender == pentagonButton){
        tool = PENTAGON;
    }
    else if (sender == hexagonButton){
        tool = HEXAGON;
    }
    else if (sender == enlargeButton){
        action = ENLARGE;
    }
    else if (sender == shrinkButton){
        action = SHRINK;
    }
    else if (sender == bringFrontButton){
        action = BRING_FRONT;
    }
    else if (sender == sendBackButton){
        action = SEND_BACK;
    }
    else if (sender == undoButton){
        action = UNDO;
    }
    else if (sender == redoButton){
        action = REDO;
    }
    else if (sender == clearButton){
        action = CLEAR;
    }

    if (onChangeCb) {
        onChangeCb(this);
    }

    visualizeSelectedTool();
    redraw();
}

TOOL Toolbar::getTool() const {
    return tool;
}

ACTION Toolbar::getAction() const {
    return action;
}

Toolbar::Toolbar(int x, int y, int w, int h) : Group(x, y, w, h) {
    int s = 50;
    int row = 0;
    pencilButton = new Image(x, y + s*(row++), s, s, "./assets/pencil.png");
    eraserButton = new Image(x, y + s*(row++), s, s, "./assets/eraser.png");
    selectorButton = new Image(x, y + s*(row++), s, s, "./assets/mouse.png");
    circleButton = new Image(x, y + s*(row++), s, s, "./assets/circle.png");
    triangleButton = new Image(x, y + s*(row++), s, s, "./assets/triangle.png");
    rectangleButton = new Image(x, y + s*(row++), s, s, "./assets/rectangle.png");
    pentagonButton = new Image(x, y + s*(row++), s, s, "./assets/pentagon.png");
    hexagonButton = new Image(x, y + s*(row++), s, s, "./assets/hexagon.png");
    enlargeButton = new Image(x, y + s*(row++), s, s, "./assets/plus.png");
    shrinkButton = new Image(x, y + s*(row++), s, s, "./assets/minus.png");
    bringFrontButton = new Image(x, y + s*(row++), s, s, "./assets/bring to front.png");
    sendBackButton = new Image(x, y + s*(row++), s, s, "./assets/sent to back.png");
    undoButton = new Image(x, y + s*(row++), s, s, "./assets/undo.png");
    redoButton = new Button(x, y + s*(row++), s, s, "redo");
    clearButton = new Image(x, y + s*(row++), s, s, "./assets/clear.png");

    tool = PENCIL;
    action = NONE;

    pencilButton->box(FL_BORDER_BOX);
    eraserButton->box(FL_BORDER_BOX);
    selectorButton->box(FL_BORDER_BOX);
    circleButton->box(FL_BORDER_BOX);
    triangleButton->box(FL_BORDER_BOX);
    rectangleButton->box(FL_BORDER_BOX);
    pentagonButton->box(FL_BORDER_BOX);
    hexagonButton->box(FL_BORDER_BOX);
    enlargeButton->box(FL_BORDER_BOX);
    shrinkButton->box(FL_BORDER_BOX);
    bringFrontButton->box(FL_BORDER_BOX);
    sendBackButton->box(FL_BORDER_BOX);
    undoButton->box(FL_BORDER_BOX);
    redoButton->box(FL_BORDER_BOX);
    clearButton->box(FL_BORDER_BOX);

    visualizeSelectedTool();

    ON_CLICK(pencilButton, Toolbar::onClick);
    ON_CLICK(eraserButton, Toolbar::onClick);
    ON_CLICK(selectorButton, Toolbar::onClick);
    ON_CLICK(circleButton, Toolbar::onClick);
    ON_CLICK(triangleButton, Toolbar::onClick);
    ON_CLICK(rectangleButton, Toolbar::onClick);
    ON_CLICK(pentagonButton, Toolbar::onClick);
    ON_CLICK(hexagonButton, Toolbar::onClick);
    ON_CLICK(enlargeButton, Toolbar::onClick);
    ON_CLICK(shrinkButton, Toolbar::onClick);
    ON_CLICK(bringFrontButton, Toolbar::onClick);
    ON_CLICK(sendBackButton, Toolbar::onClick);
    ON_CLICK(undoButton, Toolbar::onClick);
    ON_CLICK(redoButton, Toolbar::onClick);
    ON_CLICK(clearButton, Toolbar::onClick);
}
