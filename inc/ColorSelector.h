#ifndef PRESET_COLOR_SELECTOR_H
#define PRESET_COLOR_SELECTOR_H

#include <bobcat_ui/all.h>
#include "Color.h"
#include "Enums.h"

class PresetColorSelector : public bobcat::Group {
    bobcat::Button* redButton;
    bobcat::Button* orangeButton;
    bobcat::Button* yellowButton;
    bobcat::Button* greenButton;
    bobcat::Button* blueButton;
    bobcat::Button* indigoButton;
    bobcat::Button* violetButton;

    COLOR color;
    void deselectAllColors();
    void visualizeSelectedColor();
    void onClick(bobcat::Widget* sender);

public:
    PresetColorSelector(int x, int y, int w, int h);

    Color getColor() const;
};

#endif