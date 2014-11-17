// TT_window.cpp

#include "Gate.h"
#include "TT_window.h"
#include <FL/Fl_Button.H>


TT_window::TT_window(int w, int h) : Window(Point(1024,0), w, h, "Truth Table") {
    
    redraw();
}

void TT_window::cb_click(Address b, Address pw)
{
    reference_to<TT_window>(pw).click(b);
}

void TT_window::click(Address b)
{
    Fl_Button* button = &reference_to<Fl_Button>(b);
    String button_label = button->label();
}