#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include <Canvas.h>
#include <Toolbar.h>
#include <RGBColorSelector.h>
#include <ColorSelector.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Canvas* canvas;
    Toolbar* toolbar;
    ColorSelector* colorSelector;
    PresetColorSelector* presetSelector;
    float lastMx;
    float lastMy;
    bool dragging;

    void onCanvasMouseDown(bobcat::Widget* sender, float mx, float my);
    void onCanvasDrag(bobcat::Widget* sender, float mx, float my);
    void onCanvasMouseUp(bobcat::Widget* sender, float mx, float my);
    void onToolbarChange(bobcat::Widget* sender);
    void onColorChange(bobcat::Widget* sender);
    void onPresetChange(bobcat::Widget* sender);

public:
    Application();
};

#endif

