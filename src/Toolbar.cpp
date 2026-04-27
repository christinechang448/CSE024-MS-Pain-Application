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
    int idx = 0;
    auto pos = [&](int& col, int& r) { col = idx % 2; r = idx / 2; idx++; };
    int col, r;
    pos(col, r); pencilButton    = new Image(x + s*col, y + s*r, s, s, "./assets/pencil.png");
    pos(col, r); eraserButton    = new Image(x + s*col, y + s*r, s, s, "./assets/eraser.png");
    pos(col, r); selectorButton  = new Image(x + s*col, y + s*r, s, s, "./assets/mouse.png");
    pos(col, r); circleButton    = new Image(x + s*col, y + s*r, s, s, "./assets/circle.png");
    pos(col, r); triangleButton  = new Image(x + s*col, y + s*r, s, s, "./assets/triangle.png");
    pos(col, r); rectangleButton = new Image(x + s*col, y + s*r, s, s, "./assets/rectangle.png");
    pos(col, r); pentagonButton  = new Image(x + s*col, y + s*r, s, s, "./assets/pentagon.png");
    pos(col, r); hexagonButton   = new Image(x + s*col, y + s*r, s, s, "./assets/hexagon.png");
    pos(col, r); enlargeButton   = new Image(x + s*col, y + s*r, s, s, "./assets/plus.png");
    pos(col, r); shrinkButton    = new Image(x + s*col, y + s*r, s, s, "./assets/minus.png");
    pos(col, r); bringFrontButton= new Image(x + s*col, y + s*r, s, s, "./assets/bring to front.png");
    pos(col, r); sendBackButton  = new Image(x + s*col, y + s*r, s, s, "./assets/sent to back.png");
    pos(col, r); undoButton      = new Image(x + s*col, y + s*r, s, s, "./assets/undo.png");
    pos(col, r); redoButton      = new Image(x + s*col, y + s*r, s, s, "./assets/redo.png");
    pos(col, r); clearButton     = new Image(x + s*col, y + s*r, s, s, "./assets/clear.png");

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
