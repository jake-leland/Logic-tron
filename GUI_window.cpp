// Logic_GUI.cpp

#include "Gate.h"
#include "GUI_window.h"


GUI_window::GUI_window(int w, int h) : Window(w, h, "Logic-tron") {
    Lines input_lines;
    input_lines.add(Point(0,100), Point(x_max(),100));
    input_lines.set_color(Color::black);
    attach(input_lines);
    
    Button add_AND(Point(x_max()/2-250,y_max()-100), 100, 50, "AND", cb_add_AND_click);
    Button add_OR(Point(x_max()/2-50,y_max()-100), 100, 50, "OR", cb_add_OR_click);
    Button add_NOT(Point(x_max()/2+150,y_max()-100), 100, 50, "NOT", cb_add_NOT_click);
    attach(add_AND);
    attach(add_OR);
    attach(add_NOT);
    Fl::redraw();
    keep_open();
}

void GUI_window::cb_add_AND_click(Address, Address pw)
{
    reference_to<GUI_window>(pw).add_AND_click();
}

void GUI_window::add_AND_click()
{
    updating = true;
    Circle c(Point(100,100),100);
    c.set_color(Color::red);
    attach(c);
    FL:redraw();
    keep_open();
}

void GUI_window::cb_add_OR_click(Address, Address pw)
{
    reference_to<GUI_window>(pw).add_OR_click();
}

void GUI_window::add_OR_click()
{
    updating = true;
    Circle c(Point(x_max()/2,100),100);
    c.set_color(Color::green);
    attach(c);
    FL:redraw();
    keep_open();
}

void GUI_window::cb_add_NOT_click(Address, Address pw)
{
    reference_to<GUI_window>(pw).add_NOT_click();
}

void GUI_window::add_NOT_click()
{
    updating = true;
    Circle c(Point(x_max()-100,100),100);
    c.set_color(Color::blue);
    attach(c);
    FL:redraw();
    keep_open();
}

void GUI_window::keep_open() {
    updating = false;
    while (!updating) Fl::wait();
    Fl::redraw();
}

void GUI_window::update() {
    updating = true;
    cout << "updating = true\n";
}