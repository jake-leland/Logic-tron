// GUI_window.cpp

#include "Gate.h"
#include "Input.h"
#include "GUI_window.h"
#include <FL/Fl_Button.H>
#include <string>



GUI_window::GUI_window(int w, int h, int s) : Window(w, h, "Logic-tron"),
tt(),
scale(s), // represents the number of pixels between input lines
label_size(.7*scale),
padding_top(h/20), // space between the top of the window and the uppermost input line
padding_side(w/25), // space between the side of the window and the input lines
seperator(Point(0,.8*y_max()),Point(x_max(),.8*y_max())),
	//changed button callbacks to lambda functions to respective voids - HMB
	add_AND(Point(x_max()/2-250,y_max()-100), 100, 50, "AND", 
		[](Address, Address pw){ reference_to<GUI_window>(pw).add_AND_gate(); }),	
	add_OR(Point(x_max()/2-50,y_max()-100), 100, 50, "OR", 
		[](Address, Address pw){ reference_to<GUI_window>(pw).add_OR_gate(); }),
	add_NOT(Point(x_max()/2+150,y_max()-100), 100, 50, "NOT", 
		[](Address, Address pw){ reference_to<GUI_window>(pw).add_NOT_gate(); }),
i1(1,get_window_data()),
i2(2,get_window_data()),
i3(3,get_window_data()) {
    
    attach(i1); gates.push_back(i1);
    attach(i2); gates.push_back(i2);
    attach(i3); gates.push_back(i3);
    
  
    
    seperator.set_color(Color::black);
    seperator.set_style(Line_style::dash);
    attach(seperator);
    attach(add_AND);
    attach(add_OR);
    attach(add_NOT);
    
    for(int i = 1; i < 4; ++i){
	Point btnPoint( x_max() - padding_side + scale/3,
		padding_top + (i-1)*scale - scale/2);
	input_buttons.push_back( new Button( 
 		btnPoint, 
 		scale, scale,
 		std::to_string(i),
 		cb_click ) );
	attach(input_buttons[i-1]);
    }
    input_lines.set_color(Color::black);
    attach(input_lines);
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
    
//    if (button_label == "AND" or button_label == "OR" or button_label == "NOT") {
//        add_gate(button_label);
//    } else if (isdigit(stoi(button_label))) { // stoi(String) converts a string into an integer
//        // future implementation
//    } else {
//        cerr << "error: no action set for button\n";
//    }
    
    if(isdigit(button_label[0])) {
	input2_to_next = input1_to_next;
	input1_to_next = stoi(button_label);
    } else {
	cerr << "error: no action set for button\n";
    }
}

void GUI_window::add_line(int i){
    input_lines.add(
	    Point(GATE_PADDING_SIDE+2*SCALE*(i-4), GATE_PADDING_TOP+SCALE/2+SCALE*(i-4)),
	    Point(x_max()-PADDING_SIDE,GATE_PADDING_TOP+SCALE/2+SCALE*(i-4)));
    input_buttons.push_back(new Button(
	    Point(x_max()-PADDING_SIDE+SCALE/3,
		    PADDING_TOP+(i-1)*SCALE-SCALE/2),
	    SCALE,
	    SCALE,
	    to_string(i),
	    cb_click));
    
    attach(input_buttons[input_buttons.size()-1]);
}

//void GUI_window::add_gate(String type) {
//    int gate_padding_top = padding_top + 2.5*scale; // includes padding_top, and the padding needed to start below the initial three input lines
//    int gate_padding_left = padding_side + 2*scale; // includes padding_left, and the padding needed to start indented from the initial three input lines
//    
//    if (type == "AND") {
//        gates.push_back(new Circle(Point(gate_padding_left+2*scale*gates.size(),gate_padding_top+scale*gates.size()),scale/2));
//        gates[gates.size()-1].set_color(Color::red);
//        attach(gates[gates.size()-1]);
//    } else if (type == "OR") {
//        gates.push_back(new Circle(Point(gate_padding_left+2*scale*gates.size(),gate_padding_top+scale*gates.size()),scale/2));
//        gates[gates.size()-1].set_color(Color::green);
//        attach(gates[gates.size()-1]);
//    } else if (type == "NOT") {
//        gates.push_back(new Circle(Point(gate_padding_left+2*scale*gates.size(),gate_padding_top+scale*gates.size()),scale/2));
//        gates[gates.size()-1].set_color(Color::blue);
//        attach(gates[gates.size()-1]);
//    } else {
//        cerr << "error: command not recognized\n";
//    }
//    
//    input_lines.add(Point(gate_padding_left+2*scale*(gates.size()-1),gate_padding_top+scale/2+scale*(gates.size()-1)), Point(x_max()-padding_side,gate_padding_top+scale/2+scale*(gates.size()-1))); // we use gates.size()-1 because here, unlike in the cascading if-else block above, the new gate has already been added
//    
//    int button_height = scale;
//    int button_width = scale;
//    input_buttons.push_back(new Button(Point(x_max()-padding_side+button_width/3,padding_top+(2+gates.size())*scale-button_height/2),button_width,button_height,to_string(gates.size()+3),cb_click));
//    attach(input_buttons[input_buttons.size()-1]);
//    
//    redraw();
//}


void GUI_window::add_AND_gate() {
    int n = gates.size();   //Position of gate being added
    
    if( (input1_to_next == -1 ) || (input2_to_next == -1)){
	cerr << "Insufficient gates chosen to add AND gate." << endl;

    } else {
	gates.push_back(new Gate(
		&gates[input1_to_next-1],
		&gates[input2_to_next-1],
		Operand::AND,
		n+1));
	gates[n].set_color(Color::black);
	attach(gates[n]);
	add_line(n+1);
	
	input1_to_next = -1;
	input2_to_next = -1;
	redraw();
    }
}
void GUI_window::add_OR_gate(){
    int n = gates.size();   //Position of gate being added
    
    if( (input1_to_next == -1 ) || (input2_to_next == -1)){
	cerr << "Insufficient gates chosen to add OR gate." << endl;
    } else {
	gates.push_back(new Gate(
		&gates[input1_to_next-1],
		&gates[input2_to_next-1],
		Operand::OR,
		n+1));
	gates[n].set_color(Color::black);
	attach(gates[n]);
	add_line(n+1);
	
	input1_to_next = -1;
	input2_to_next = -1;
	redraw();
    }
}
void GUI_window::add_NOT_gate(){
    int n = gates.size();   //Position of gate being added
    
    if(input1_to_next == -1){
	cerr << "Insufficient gates chosen to add NOT gate." << endl;
    } else {
	gates.push_back(new Gate(
		&gates[input1_to_next-1],
		Operand::NOT,
		n+1));
	gates[n].set_color(Color::black);
	attach(gates[n]);
	add_line(n+1);
	
	input1_to_next = -1;
	input2_to_next = -1;
	redraw();
    }
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

