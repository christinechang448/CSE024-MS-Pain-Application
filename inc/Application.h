#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include "Canvas.h"
#include "Toolbar.h"
#include "Canvas.h"
#include "Color Selector.h"

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Canvas* canvas;
    Toolbar* toolbar;
    

public:
    Application();
};

#endif

