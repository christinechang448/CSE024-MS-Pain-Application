#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include <bobcat_ui/all.h>
#include <FL/Fl_Slider.H>
#include <Color.h>

class ColorSelector : public bobcat::Group {
    bobcat::Button*  swatch;

    Fl_Slider* redSlider;
    Fl_Slider* greenSlider;
    Fl_Slider* blueSlider;

    bobcat::Image* rDec;
    bobcat::Image* rInc;
    bobcat::Image* gDec;
    bobcat::Image* gInc;
    bobcat::Image* bDec;
    bobcat::Image* bInc;

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

public:
    ColorSelector(int x, int y, int w, int h);

    Color getColor() const;
};

#endif
