#include "ColorSelector.h"
using namespace bobcat;

void PresetColorSelector::deselectAllColors() {
    redButton->label("");
    orangeButton->label("");
    yellowButton->label("");
    greenButton->label("");
    blueButton->label("");
    indigoButton->label("");
    violetButton->label("");
}

void PresetColorSelector::visualizeSelectedColor() {
    if (color == RED) {
        redButton->label("@+5square");
    }
    else if (color == ORANGE) {
        orangeButton->label("@+5square");
    }
    else if (color == YELLOW) {
        yellowButton->label("@+5square");
    }
    else if (color == GREEN) {
        greenButton->label("@+5square");
    }
    else if (color == BLUE) {
        blueButton->label("@+5square");
    }
    else if (color == INDIGO) {
        indigoButton->label("@+5square");
    }
    else if (color == VIOLET) {
        violetButton->label("@+5square");
    }
}

void PresetColorSelector::onClick(bobcat::Widget* sender) {
    deselectAllColors();

    if (sender == redButton) {
        color = RED;
    }
    else if (sender == orangeButton) {
        color = ORANGE;
    }
    else if (sender == yellowButton) {
        color = YELLOW;
    }
    else if (sender == greenButton) {
        color = GREEN;
    }
    else if (sender == blueButton) {
        color = BLUE;
    }
    else if (sender == indigoButton) {
        color = INDIGO;
    }
    else if (sender == violetButton) {
        color = VIOLET;
    }

    visualizeSelectedColor();
    redraw();
    if (onChangeCb) onChangeCb(this);
}

Color PresetColorSelector::getColor() const {
    if (color == RED) {
        return Color(255/255.0, 0/255.0, 0/255.0);
    }
    else if (color == ORANGE) {
        return Color(255/255.0, 127/255.0, 0/255.0);
    }
    else if (color == YELLOW) {
        return Color(255/255.0, 255/255.0, 0/255.0);
    }
    else if (color == GREEN) {
        return Color(0/255.0, 255/255.0, 0/255.0);
    }
    else if (color == BLUE) {
        return Color(0/255.0, 0/255.0, 255/255.0);
    }
    else if (color == INDIGO) {
        return Color(75/255.0, 0/255.0, 130/255.0);
    }
    else if (color == VIOLET) {
        return Color(148/255.0, 0/255.0, 211/255.0);
    }
    else {
        return Color();
    }
}

PresetColorSelector::PresetColorSelector(int x, int y, int w, int h) : Group(x, y, w, h) {
    int bw = w / 2;
    int bh = 50;
    redButton    = new Button(x,      y,         bw, bh, "");
    orangeButton = new Button(x + bw, y,         bw, bh, "");
    yellowButton = new Button(x,      y + bh,    bw, bh, "");
    greenButton  = new Button(x + bw, y + bh,    bw, bh, "");
    blueButton   = new Button(x,      y + 2*bh,  bw, bh, "");
    indigoButton = new Button(x + bw, y + 2*bh,  bw, bh, "");
    violetButton = new Button(x,      y + 3*bh,  bw, bh, "");

    color = RED;

    redButton->color(fl_rgb_color(255, 0, 0));
    redButton->labelcolor(FL_WHITE);
    orangeButton->color(fl_rgb_color(255, 127, 0));
    orangeButton->labelcolor(FL_WHITE);
    yellowButton->color(fl_rgb_color(255, 255, 0));
    yellowButton->labelcolor(FL_WHITE);
    greenButton->color(fl_rgb_color(0, 255, 0));
    greenButton->labelcolor(FL_WHITE);
    blueButton->color(fl_rgb_color(0, 0, 255));
    blueButton->labelcolor(FL_WHITE);
    indigoButton->color(fl_rgb_color(75, 0, 130));
    indigoButton->labelcolor(FL_WHITE);
    violetButton->color(fl_rgb_color(148, 0, 211));
    violetButton->labelcolor(FL_WHITE);

    visualizeSelectedColor();

    ON_CLICK(redButton, PresetColorSelector::onClick);
    ON_CLICK(orangeButton, PresetColorSelector::onClick);
    ON_CLICK(yellowButton, PresetColorSelector::onClick);
    ON_CLICK(greenButton, PresetColorSelector::onClick);
    ON_CLICK(blueButton, PresetColorSelector::onClick);
    ON_CLICK(indigoButton, PresetColorSelector::onClick);
    ON_CLICK(violetButton, PresetColorSelector::onClick);
}