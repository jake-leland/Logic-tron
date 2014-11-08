// Logic_GUI.cpp

#include "Gate.h"
#include "Logic_GUI.h"


Logic_GUI::Logic_GUI(int w, int h)
: win_w(w), win_h(h), win(Point(100,100), win_w, win_h,"Logic-tron") {
    Lines input_lines;
    input_lines.add(Point(0,100), Point(win_w,100));
    input_lines.set_color(Color::black);
    win.attach(input_lines);
    win.redraw();
    win.wait_for_button();
}

void Logic_GUI::add_gate() {
    // test to see if it works
    Circle c(Point(100,100),100);
    c.set_color(Color::black);
    win.attach(c);
    win.redraw();
    win.wait_for_button(); // this causes an error
}