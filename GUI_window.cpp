// GUI_window.cpp

#include "Gate.h"
#include "Input.h"
#include "GUI_window.h"
#include <FL/Fl_Button.H>


GUI_window::GUI_window(int w, int h, int s) : Window(w, h, "Logic-tron"),
tt(),
scale(s), // represents the number of pixels between input lines
label_size(.7*scale),
padding_top(h/20), // space between the top of the window and the uppermost input line
padding_side(w/25), // space between the side of the window and the input lines
seperator(Point(0,.8*y_max()),Point(x_max(),.8*y_max())),
add_AND(Point(x_max()/2-250,y_max()-100), 100, 50, "AND", cb_click),
add_OR(Point(x_max()/2-50,y_max()-100), 100, 50, "OR", cb_click),
add_NOT(Point(x_max()/2+150,y_max()-100), 100, 50, "NOT", cb_click),
i1(1,get_window_data()),
i2(2,get_window_data()),
i3(3,get_window_data()) {
    
    attach(i1);
    attach(i2);
    attach(i3);
    
    /*
    input_lines.add(Point(padding_side,padding_top), Point(x_max()-padding_side,padding_top));
    input_lines.add(Point(padding_side,padding_top+scale), Point(x_max()-padding_side,padding_top+scale));
    input_lines.add(Point(padding_side,padding_top+2*scale), Point(x_max()-padding_side,padding_top+2*scale));
    input_lines.set_color(Color::black);
    attach(input_lines);

    int label_height = label_size/1.4;
    int label_width = label_size/1.4;
    int button_height = scale;
    int button_width = scale;
    input_labels.push_back(new Text(Point(padding_side-1.5*label_width,padding_top+label_height/2),"A"));
    input_buttons.push_back(new Button(Point(x_max()-padding_side+button_width/3,padding_top-button_height/2),button_width,button_height,"1",cb_click));
    
    input_labels.push_back(new Text(Point(padding_side-1.5*label_width,padding_top+scale+label_height/2),"B"));
    input_buttons.push_back(new Button(Point(x_max()-padding_side+button_width/3,padding_top+scale-button_height/2),button_width,button_height,"2",cb_click));
    input_labels.push_back(new Text(Point(padding_side-1.5*label_width,padding_top+2*scale+label_height/2),"C"));
    input_buttons.push_back(new Button(Point(x_max()-padding_side+button_width/3,padding_top+2*scale-button_height/2),button_width,button_height,"3",cb_click));
for (int i=0; i<input_labels.size(); ++i) {
        input_labels[i].set_font_size(label_size);
        input_labels[i].set_color(Color::black);
        attach(input_labels[i]);
    }
    for (int i=0; i<input_buttons.size(); ++i) {
        attach(input_buttons[i]);
    }
    */
    
    seperator.set_color(Color::black);
    seperator.set_style(Line_style::dash);
    attach(seperator);
    attach(add_AND);
    attach(add_OR);
    attach(add_NOT);
    
    /*
    gates.push_back(INITIAL INPUT A);
    tt.add_column(gates[gates.size()-1]);
    gates.push_back(INITIAL INPUT A);
    tt.add_column(gates[gates.size()-1]);
    gates.push_back(INITIAL INPUT A);
    tt.add_column(gates[gates.size()-1]);
    */
    
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
    
    if (button_label == "AND" or button_label == "OR" or button_label == "NOT") {
        add_gate(button_label);
    } else if (isdigit(stoi(button_label))) { // stoi(String) converts a string into an integer
        // future implementation
    } else {
        cerr << "error: no action set for button\n";
    }
}

void GUI_window::add_gate(String type) {
    int gate_padding_top = padding_top + 2.5*scale; // includes padding_top, and the padding needed to start below the initial three input lines
    int gate_padding_left = padding_side + 2*scale; // includes padding_left, and the padding needed to start indented from the initial three input lines
    
    if (type == "AND") {
        gates.push_back(new Circle(Point(gate_padding_left+2*scale*gates.size(),gate_padding_top+scale*gates.size()),scale/2));
        gates[gates.size()-1].set_color(Color::red);
        
        //gates1.push_back(new Gate(&gates1[0], &gates1[1], Operand::AND, gates.size()));
    } else if (type == "OR") {
        gates.push_back(new Circle(Point(gate_padding_left+2*scale*gates.size(),gate_padding_top+scale*gates.size()),scale/2));
        gates[gates.size()-1].set_color(Color::green);
    } else if (type == "NOT") {
        gates.push_back(new Circle(Point(gate_padding_left+2*scale*gates.size(),gate_padding_top+scale*gates.size()),scale/2));
        gates[gates.size()-1].set_color(Color::blue);
    } else {
        cerr << "error: command not recognized\n";
    }
    
    input_lines.add(Point(gate_padding_left+2*scale*(gates.size()-1),gate_padding_top+scale/2+scale*(gates.size()-1)), Point(x_max()-padding_side,gate_padding_top+scale/2+scale*(gates.size()-1))); // we use gates.size()-1 because here, unlike in the cascading if-else block above, the new gate has already been added
    
    int button_height = scale;
    int button_width = scale;
    input_buttons.push_back(new Button(Point(x_max()-padding_side+button_width/3,padding_top+(2+gates.size())*scale-button_height/2),button_width,button_height,to_string(gates.size()+3),cb_click));
    attach(input_buttons[input_buttons.size()-1]);
    
    attach(gates[gates.size()-1]);
    //tt.add_column(gates[gates.size()-1]);
    
    redraw();
}

Vector<int> GUI_window::get_window_data() {
    Vector<int> data;
    data.push_back(x_max());
    data.push_back(y_max());
    data.push_back(scale);
    data.push_back(padding_side);
    data.push_back(padding_top);
    return data;
}