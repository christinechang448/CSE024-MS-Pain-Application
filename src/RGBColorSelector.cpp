#include <ColorSelector.h>
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <sstream>

using namespace bobcat;

int ColorSelector::clamp255(int v) {
    if (v < 0) return 0;
    if (v > 255) return 255;
    return v;
}

void ColorSelector::sliderCb(Fl_Widget*, void* self) {
    static_cast<ColorSelector*>(self)->onSliderChange();
}

void ColorSelector::onSliderChange() {
    refresh();
    if (onChangeCb) onChangeCb(this);
}

void ColorSelector::onBumpClick(bobcat::Widget* sender) {
    if      (sender == rDec) redSlider->value(clamp255((int)redSlider->value() - 1));
    else if (sender == rInc) redSlider->value(clamp255((int)redSlider->value() + 1));
    else if (sender == gDec) greenSlider->value(clamp255((int)greenSlider->value() - 1));
    else if (sender == gInc) greenSlider->value(clamp255((int)greenSlider->value() + 1));
    else if (sender == bDec) blueSlider->value(clamp255((int)blueSlider->value() - 1));
    else if (sender == bInc) blueSlider->value(clamp255((int)blueSlider->value() + 1));
    refresh();
    if (onChangeCb) onChangeCb(this);
}

void ColorSelector::refresh() {
    int r = clamp255((int)redSlider->value());
    int g = clamp255((int)greenSlider->value());
    int b = clamp255((int)blueSlider->value());

    swatch->color(fl_rgb_color(r, g, b));
    swatch->redraw();

    std::ostringstream os;
    os << r;
    rValue->copy_label(os.str().c_str());
    os.str(""); os.clear();
    os << g;
    gValue->copy_label(os.str().c_str());
    os.str(""); os.clear();
    os << b;
    bValue->copy_label(os.str().c_str());

    rValue->redraw();
    gValue->redraw();
    bValue->redraw();
    redraw();
}

Color ColorSelector::getColor() const {
    int r = (int)redSlider->value();
    int g = (int)greenSlider->value();
    int b = (int)blueSlider->value();
    if (r < 0) r = 0; if (r > 255) r = 255;
    if (g < 0) g = 0; if (g > 255) g = 255;
    if (b < 0) b = 0; if (b > 255) b = 255;
    return Color(r / 255.0f, g / 255.0f, b / 255.0f);
}

ColorSelector::ColorSelector(int x, int y, int w, int h) : Group(x, y, w, h) {
    // Layout constants
    int pad = 10;
    int swatchH = 50;
    int sliderRowH = 32;
    int labelRowH = 30;
    int valueRowH = 30;
    int bumpW = 28;

    // Swatch (live preview)
    swatch = new Button(x + pad, y + pad, w - 2*pad, swatchH, "");
    swatch->box(FL_FLAT_BOX);
    swatch->color(fl_rgb_color(0, 0, 0));
    swatch->deactivate();

    // Slider rows: each has - [slider] +
    int sliderY = y + pad + swatchH + pad;
    int sliderX = x + pad + bumpW + 4;
    int sliderW = w - 2*pad - 2*bumpW - 8;

    // Red row
    rDec = new Button(x + pad, sliderY, bumpW, sliderRowH, "-");
    redSlider = new Fl_Value_Slider(sliderX, sliderY + 4, sliderW, sliderRowH - 8);
    redSlider->type(FL_HORIZONTAL);
    redSlider->bounds(0, 255);
    redSlider->step(1);
    redSlider->value(0);
    redSlider->textsize(0);
    redSlider->color(FL_DARK1);
    redSlider->selection_color(fl_rgb_color(220, 70, 60));
    rInc = new Button(x + pad + bumpW + 4 + sliderW + 4, sliderY, bumpW, sliderRowH, "+");

    // Green row
    int greenY = sliderY + sliderRowH + 4;
    gDec = new Button(x + pad, greenY, bumpW, sliderRowH, "-");
    greenSlider = new Fl_Value_Slider(sliderX, greenY + 4, sliderW, sliderRowH - 8);
    greenSlider->type(FL_HORIZONTAL);
    greenSlider->bounds(0, 255);
    greenSlider->step(1);
    greenSlider->value(0);
    greenSlider->textsize(0);
    greenSlider->color(FL_DARK1);
    greenSlider->selection_color(fl_rgb_color(80, 170, 90));
    gInc = new Button(x + pad + bumpW + 4 + sliderW + 4, greenY, bumpW, sliderRowH, "+");

    // Blue row
    int blueY = greenY + sliderRowH + 4;
    bDec = new Button(x + pad, blueY, bumpW, sliderRowH, "-");
    blueSlider = new Fl_Value_Slider(sliderX, blueY + 4, sliderW, sliderRowH - 8);
    blueSlider->type(FL_HORIZONTAL);
    blueSlider->bounds(0, 255);
    blueSlider->step(1);
    blueSlider->value(0);
    blueSlider->textsize(0);
    blueSlider->color(FL_DARK1);
    blueSlider->selection_color(fl_rgb_color(70, 140, 230));
    bInc = new Button(x + pad + bumpW + 4 + sliderW + 4, blueY, bumpW, sliderRowH, "+");

    // Color name labels
    int labelY = blueY + sliderRowH + pad;
    int colW = (w - 2*pad) / 3;
    redLabel   = new Button(x + pad + 0*colW, labelY, colW, labelRowH, "RED");
    greenLabel = new Button(x + pad + 1*colW, labelY, colW, labelRowH, "GREEN");
    blueLabel  = new Button(x + pad + 2*colW, labelY, colW, labelRowH, "BLUE");
    redLabel->deactivate();
    greenLabel->deactivate();
    blueLabel->deactivate();

    // Numeric value boxes
    int valueY = labelY + labelRowH + 4;
    rValue = new TextBox(x + pad + 0*colW, valueY, colW, valueRowH, "0");
    gValue = new TextBox(x + pad + 1*colW, valueY, colW, valueRowH, "0");
    bValue = new TextBox(x + pad + 2*colW, valueY, colW, valueRowH, "0");
    rValue->box(FL_BORDER_BOX);
    gValue->box(FL_BORDER_BOX);
    bValue->box(FL_BORDER_BOX);
    rValue->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
    gValue->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
    bValue->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);

    // Wire callbacks
    redSlider->callback(&ColorSelector::sliderCb, this);
    greenSlider->callback(&ColorSelector::sliderCb, this);
    blueSlider->callback(&ColorSelector::sliderCb, this);

    ON_CLICK(rDec, ColorSelector::onBumpClick);
    ON_CLICK(rInc, ColorSelector::onBumpClick);
    ON_CLICK(gDec, ColorSelector::onBumpClick);
    ON_CLICK(gInc, ColorSelector::onBumpClick);
    ON_CLICK(bDec, ColorSelector::onBumpClick);
    ON_CLICK(bInc, ColorSelector::onBumpClick);

    refresh();
}
