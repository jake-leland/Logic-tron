// Logic_GUI.cpp

#include "Gate.h"
#include "GUI_window.h"
#include "Fl_Button.H"


GUI_window::GUI_window(int w, int h) : Window(w, h, "Logic-tron"),
    add_AND(Point(x_max()/2-250,y_max()-100), 100, 50, "AND", cb_click),
    add_OR(Point(x_max()/2-50,y_max()-100), 100, 50, "OR", cb_click),
    add_NOT(Point(x_max()/2+150,y_max()-100), 100, 50, "NOT", cb_click) {
    
    input_lines.add(Point(0,20), Point(x_max(),20));
    input_lines.add(Point(0,40), Point(x_max(),40));
    input_lines.add(Point(0,60), Point(x_max(),60));
    input_lines.set_color(Color::black);
    attach(input_lines);
    
    attach(add_AND);
    attach(add_OR);
    attach(add_NOT);
    
    redraw();
}

void GUI_window::cb_click(Address b, Address pw)
{
    reference_to<GUI_window>(pw).click(b);
}

void GUI_window::click(Address b)
{
    Fl_Button* button = &reference_to<Fl_Button>(b);
    String button_label = button->label();
    
    if (button_label == "AND") {
        gates.push_back(new Circle(Point(40+40*gates.size(),70+20*gates.size()),10));
        gates[gates.size()-1].set_color(Color::red);
        attach(gates[gates.size()-1]);
    } else if (button_label == "OR") {
        gates.push_back(new Circle(Point(40+40*gates.size(),70+20*gates.size()),10));
        gates[gates.size()-1].set_color(Color::green);
        attach(gates[gates.size()-1]);
    } else if (button_label == "NOT") {
        gates.push_back(new Circle(Point(40+40*gates.size(),70+20*gates.size()),10));
        gates[gates.size()-1].set_color(Color::blue);
        attach(gates[gates.size()-1]);
    } else {
        cerr << "error: button label not recognized";
    }
    
    input_lines.add(Point(40*gates.size(),80+20*(gates.size()-1)), Point(x_max(),80+20*(gates.size()-1)));
    
    redraw();
}