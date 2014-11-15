// Logic_GUI.cpp

#include "Gate.h"
#include "GUI_window.h"
#include <FL/Fl_Button.H>


GUI_window::GUI_window(int w, int h, int s) : Window(w, h, "Logic-tron"),
scale(s), // represents the number of pixels between input lines
label_size(.7*scale),
padding_top(h/20), // space between the top of the window and the uppermost input line
padding_side(w/25), // space between the side of the window and the input lines
add_AND(Point(x_max()/2-250,y_max()-100), 100, 50, "AND", cb_click),
add_OR(Point(x_max()/2-50,y_max()-100), 100, 50, "OR", cb_click),
add_NOT(Point(x_max()/2+150,y_max()-100), 100, 50, "NOT", cb_click) {
    
    input_lines.add(Point(padding_side,padding_top), Point(x_max()-padding_side,padding_top));
    input_lines.add(Point(padding_side,padding_top+scale), Point(x_max()-padding_side,padding_top+scale));
    input_lines.add(Point(padding_side,padding_top+2*scale), Point(x_max()-padding_side,padding_top+2*scale));
    input_lines.set_color(Color::black);
    attach(input_lines);
    
    int label_height = label_size/1.4;
    int label_width = label_size/1.4;
    input_labels.push_back(new Text(Point(padding_side-1.5*label_width,padding_top+label_height/2),"A"));
    input_labels.push_back(new Text(Point(x_max()-padding_side+.5*label_width,padding_top+label_height/2),"1"));
    input_labels.push_back(new Text(Point(padding_side-1.5*label_width,padding_top+scale+label_height/2),"B"));
    input_labels.push_back(new Text(Point(x_max()-padding_side+.5*label_width,padding_top+scale+label_height/2),"2"));
    input_labels.push_back(new Text(Point(padding_side-1.5*label_width,padding_top+2*scale+label_height/2),"C"));
    input_labels.push_back(new Text(Point(x_max()-padding_side+.5*label_width,padding_top+2*scale+label_height/2),"3"));
    for (int i=0; i<input_labels.size(); ++i) {
        input_labels[i].set_font_size(label_size);
        input_labels[i].set_color(Color::black);
        attach(input_labels[i]);
    }
    
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
    
    int gate_padding_top = padding_top + 2.5*scale; // includes padding_top, and the padding needed to start below the initial three input lines
    int gate_padding_left = padding_side + 2*scale; // includes padding_left, and the padding needed to start indented from the initial three input lines
    
    if (button_label == "AND") {
        gates.push_back(new Circle(Point(gate_padding_left+2*scale*gates.size(),gate_padding_top+scale*gates.size()),scale/2));
        gates[gates.size()-1].set_color(Color::red);
        attach(gates[gates.size()-1]);
    } else if (button_label == "OR") {
        gates.push_back(new Circle(Point(gate_padding_left+2*scale*gates.size(),gate_padding_top+scale*gates.size()),scale/2));
        gates[gates.size()-1].set_color(Color::green);
        attach(gates[gates.size()-1]);
    } else if (button_label == "NOT") {
        gates.push_back(new Circle(Point(gate_padding_left+2*scale*gates.size(),gate_padding_top+scale*gates.size()),scale/2));
        gates[gates.size()-1].set_color(Color::blue);
        attach(gates[gates.size()-1]);
    } else {
        cerr << "error: button label not recognized";
    }
    
    input_lines.add(Point(gate_padding_left+2*scale*(gates.size()-1),gate_padding_top+scale/2+scale*(gates.size()-1)), Point(x_max()-padding_side,gate_padding_top+scale/2+scale*(gates.size()-1))); // we use gates.size()-1 because here, unlike in the cascading if-else block above, the new gate has already been added
    
    int label_height = label_size/1.4;
    int label_width = label_size/1.4;
    input_labels.push_back(new Text(Point(x_max()-padding_side+.5*label_width,padding_top+(2+gates.size())*scale+label_height/2),to_string(gates.size()+3)));
    input_labels[input_labels.size()-1].set_font_size(label_size);
    input_labels[input_labels.size()-1].set_color(Color::black);
    attach(input_labels[input_labels.size()-1]);
    
    redraw();
}