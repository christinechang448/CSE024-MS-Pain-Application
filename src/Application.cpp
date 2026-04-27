#include <Application.h>
#include <Enums.h>
#include <bobcat_ui/bobcat_ui.h>

using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        canvas->startScribble();
        canvas->updateScribble(mx, my, color.getR(), color.getG(), color.getB(), 7);
    }
    else if (tool == ERASER) {
        canvas->selectAt(mx, my);
        canvas->deleteSelected();
    }
    else if (tool == SELECTOR) {
        canvas->selectAt(mx, my);
        lastMx = mx;
        lastMy = my;
        dragging = (canvas->getSelected() != nullptr);
    }
    else if (tool == RECTANGLE) {
        canvas->addRectangle(mx, my, color.getR(), color.getG(), color.getB());
    }
    else if (tool == CIRCLE) {
        canvas->addCircle(mx, my, color.getR(), color.getG(), color.getB());
    }
    else if (tool == TRIANGLE) {
        canvas->addTriangle(mx, my, 0.25, 0.25, color.getR(), color.getG(), color.getB());
    }
    else if (tool == PENTAGON) {
        canvas->addPentagon(mx, my, 0.15, color.getR(), color.getG(), color.getB());
    }
    else if (tool == HEXAGON) {
        canvas->addHexagon(mx, my, 0.15, color.getR(), color.getG(), color.getB());
    }

    canvas->redraw();
}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        canvas->updateScribble(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->selectAt(mx, my);
        canvas->deleteSelected();
        canvas->redraw();
    }
    else if (tool == SELECTOR && dragging) {
        canvas->moveSelected(mx - lastMx, my - lastMy);
        lastMx = mx;
        lastMy = my;
        canvas->redraw();
    }
}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
    canvas->endScribble();
    dragging = false;
    canvas->redraw();
}

void Application::onToolbarChange(bobcat::Widget* sender) {
    ACTION action = toolbar->getAction();

    if (action == CLEAR) {
        canvas->clear();
    }
    else if (action == UNDO) {
        canvas->undo();
    }
    else if (action == REDO) {
        canvas->redo();
    }
    else if (action == ENLARGE) {
        canvas->resizeSelected(1.1f);
    }
    else if (action == SHRINK) {
        canvas->resizeSelected(0.9f);
    }
    else if (action == BRING_FRONT) {
        canvas->bringToFront();
    }
    else if (action == SEND_BACK) {
        canvas->sendToBack();
    }

    canvas->redraw();
}

void Application::onColorChange(bobcat::Widget* sender) {
    if (canvas->getSelected()) {
        Color c = colorSelector->getColor();
        canvas->recolorSelected(c.getR(), c.getG(), c.getB());
        canvas->redraw();
    }
}

Application::Application() {
    lastMx = 0;
    lastMy = 0;
    dragging = false;

    int toolbarW = 100;
    int canvasW = 500;
    int canvasH = 500;
    int colorH = 260;

    int winW = toolbarW + canvasW;
    int winH = canvasH + colorH;

    window = new Window(25, 75, winW, winH, "CSE 024 MS Paint Application");

    canvas = new Canvas(toolbarW, 0, canvasW, canvasH);
    toolbar = new Toolbar(0, 0, toolbarW, winH);
    colorSelector = new ColorSelector(toolbarW, canvasH, canvasW, colorH);
    colorSelector->box(FL_BORDER_BOX);

    window->add(canvas);
    window->add(toolbar);
    window->add(colorSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(colorSelector, Application::onColorChange);

    window->show();
}
