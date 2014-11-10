// Logic_GUI.cpp

#include "Gate.h"
#include "GUI_window.h"


GUI_window::GUI_window(int w, int h) : Window(w, h, "Logic-tron") {
    Lines input_lines;
    input_lines.add(Point(0,100), Point(x_max(),100));
    input_lines.set_color(Color::black);
    attach(input_lines);
    redraw();
}

void GUI_window::add_gate() {
    Circle c(Point(100,100),100);
    c.set_fill_color(Color::black);
    attach(c);
    redraw();
}