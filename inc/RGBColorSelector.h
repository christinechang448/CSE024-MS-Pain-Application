#ifndef RGBCOLOR_SELECTOR_H
#define RGBCOLOR_SELECTOR_H

#include <bobcat_ui/all.h>
#include <FL/Fl_Value_Slider.H>
#include "Color.h"

class ColorSelector : public bobcat::Group {
    bobcat::Button*  swatch;

    Fl_Value_Slider* redSlider;
    Fl_Value_Slider* greenSlider;
    Fl_Value_Slider* blueSlider;

    bobcat::Button* rDec;
    bobcat::Button* rInc;
    bobcat::Button* gDec;
    bobcat::Button* gInc;
    bobcat::Button* bDec;
    bobcat::Button* bInc;

    bobcat::Button* redLabel;
    bobcat::Button* greenLabel;
    bobcat::Button* blueLabel;

    bobcat::TextBox* rValue;
    bobcat::TextBox* gValue;
    bobcat::TextBox* bValue;

    static void sliderCb(Fl_Widget*, void* self);
    void onSliderChange();
    void onBumpClick(bobcat::Widget* sender);
    void refresh();
    int clamp255(int v);

public:
    ColorSelector(int x, int y, int w, int h);

    Color getColor() const;
};

#endif
