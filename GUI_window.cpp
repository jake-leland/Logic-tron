// GUI_window.cpp

#include "Gate.h"
#include "Input.h"
#include "GUI_window.h"
#include "Gate_reader.h"
#include <FL/Fl_Button.H>
#include <string>

Line_stack::Line_stack() : Shape() {
    Shape::set_style(Line_style::solid);
    Shape::set_color(Color::black);
}

void Line_stack::set_color(Color c) {
    Shape::set_color(c);
    auto itbegin = v.begin();
    auto itend = v.end();
    for (auto it = itbegin; it != itend; ++it) {
	((*it))->set_color(c);
    }
}

void Line_stack::draw_lines() const {
    auto itbegin = v.begin();
    auto itend = v.end();
    for (auto it = itbegin; it != itend; ++it) {
	((*it))->draw();
    }
}

void Line_stack::add(Point p1, Point p2) {
    v.push_back(new Line(p1, p2));
    v.at(v.size() - 1)->set_color(color());
    v.at(v.size() - 1)->set_style(style());
}

void Line_stack::rm_line() {
    delete v.at(v.size() - 1);
    v.pop_back();
}

void Line_stack::clear(){
    int n = v.size();
    for(int i = 0; i < n; ++i) rm_line();
}


GUI_window::GUI_window(int w, int h, int s) : Window(w, h, "Logic-tron"),
	tt(), // initialize truth table window
	scale(s), // represents the number of pixels between input lines
	label_size(.7 * scale),
	padding_top(h / 20), // space between the top of the window and the uppermost input line
	padding_side(w / 25), // space between the side of the window and the input lines
	seperator(Point(0, .8 * y_max()), Point(x_max(), .8 * y_max())),
	input_lines(),
//Button initialization. Self explanitory
	add_AND(Point(x_max() / 2 - 250, y_max() - 100), 100, 50, "AND",
		[](Address, Address pw) {
		    reference_to<GUI_window>(pw).add_AND_gate(); }),
	add_OR(Point(x_max() / 2 - 50, y_max() - 100), 100, 50, "OR",
		[](Address, Address pw) {
		    reference_to<GUI_window>(pw).add_OR_gate(); }),
	add_NOT(Point(x_max() / 2 + 150, y_max() - 100), 100, 50, "NOT",
		[](Address, Address pw) {
		    reference_to<GUI_window>(pw).add_NOT_gate(); }),
	open(Point(x_max() - 75, y_max() - 100), 50, 25, "Open",
		[](Address, Address pw) {
		    reference_to<GUI_window>(pw).read_file(); }),
	save(Point(x_max() - 75, y_max() - 50), 50, 25, "Save",
		[](Address, Address pw) {
		    reference_to<GUI_window>(pw).save_file(); }),
//In-box for typing filename of file to read/write
	filename(Point(x_max() - 150, y_max() - 150), 100, 25, "filename"),
//Initialize three circuit inputs
	i1(1, x_max()),
	i2(2, x_max()),
	i3(3, x_max())/*,
	in1_text( new Text(Point(0,0),"") ),
	in2_text( new Text(Point(0,0),"") ) */ {
//Attach circuit inputs
    attach(i1);
    gates.push_back(&i1);
    tt.add_column(&i1);
    attach(i2);
    gates.push_back(&i2);
    tt.add_column(&i2);
    attach(i3);
    gates.push_back(&i3);
    tt.add_column(&i3);
//Attach other window features
    seperator.set_color(Color::black);
    seperator.set_style(Line_style::dash);
    attach(seperator);
    attach(add_AND);
    attach(add_OR);
    attach(add_NOT);
    attach(open);
    attach(save);
    attach(filename);
//Initialize the first three input buttons
    for (int i = 1; i < 4; ++i) {
	Point btnPoint(x_max() - padding_side + scale / 3,
		padding_top + (i - 1) * scale - scale / 2);
	input_buttons.push_back(new Button(
		btnPoint,
		scale, scale,
		std::to_string(i),
		cb_click));
	attach(*input_buttons[i - 1]);
    }
    input_lines.set_color(Color::black);
    attach(input_lines);

    redraw();
}

//Callback function - used only for input buttons. Gate adding buttons were initialized
//with a lambda function
void GUI_window::cb_click(Address b, Address pw)
{
    reference_to<GUI_window>(pw).click(b);
}

void GUI_window::click(Address b)
{
    Fl_Button* button = &reference_to<Fl_Button>(b);
    String button_label = button->label();
    
    if(isdigit(button_label[0])) {
//	detach(*in1_text);
//	delete in1_text;
//	detach(*in2_text);
//	delete in2_text;
//	if(input1_to_next > 0) gates[input1_to_next-1].in_text.set_label("2");
//	if(input2_to_next > 0) {
//	    gates[input2_to_next-1].in_text.set_label("");
//	}
        input2_to_next = input1_to_next;
        input1_to_next = stoi(button_label);
//	gates[input1_to_next-1].in_text.set_label("1");
//	in1_text = new Text(
//		Point(x_max() - padding_side + 4*scale/3, 
//		padding_top +input1_to_next*scale - scale/2),"1");
//	in2_text = new Text(
//		Point(x_max() - padding_side + 4*scale/3,
//		padding_top +input2_to_next*scale - scale/2), "2");
//	if(input2_to_next > 0) attach(*in2_text);
//	attach(*in1_text);
	
    } else {
        cerr << "error: no action set for button\n";
    }
}

void GUI_window::add_line(int i) {
    input_lines.add(
	    Point(GATE_PADDING_SIDE + 2 * SCALE * (i - 4), GATE_PADDING_TOP + SCALE / 2 + SCALE * (i - 4)),
	    Point(x_max() - PADDING_SIDE, GATE_PADDING_TOP + SCALE / 2 + SCALE * (i - 4)));
    input_buttons.push_back(new Button(
	    Point(x_max() - PADDING_SIDE + SCALE / 3,
	    PADDING_TOP + (i - 1) * SCALE - SCALE / 2),
	    SCALE,
	    SCALE,
	    to_string(i),
	    cb_click));

    attach(*input_buttons[input_buttons.size() - 1]);
}

void GUI_window::add_AND_gate() {
    int n = gates.size(); //Position of gate being added

    if ((input1_to_next == -1) || (input2_to_next == -1)) {
	cerr << "Insufficient gates chosen to add AND gate." << endl;

    } else {
	gates.push_back(new Gate(
		gates[input1_to_next - 1],
		gates[input2_to_next - 1],
		Operand::AND,
		n + 1));
	gates[n]->set_color(Color::black);
	attach(*gates[n]);
	tt.add_column(gates[n]);
	add_line(n + 1);

//	gates[input1_to_next-1].in_text.set_label("");
//	gates[input2_to_next-1].in_text.set_label("");
//	detach(gates[input1_to_next -1].in_text);
//	detach(gates[input2_to_next -1].in_text);
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
                                 gates[input1_to_next-1],
                                 gates[input2_to_next-1],
                                 Operand::OR,
                                 n+1));
        gates[n]->set_color(Color::black);
        attach(*gates[n]);
        tt.add_column(gates[n]);
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
                                 gates[input1_to_next-1],
                                 Operand::NOT,
                                 n+1));
        gates[n]->set_color(Color::black);
        attach(*gates[n]);
        tt.add_column(gates[n]);
        add_line(n+1);
        
        input1_to_next = -1;
        input2_to_next = -1;
        redraw();
    }
}

void GUI_window::read_file() {
    try {
	std::ifstream is(filename.get_string() , std::ifstream::in);
	Gate_Reader reader(is);
	reader.Read_file();
	vector<Operand> ops = reader.Operand_tokens();
	vector<int> ins1 = reader.Input1_tokens();
	vector<int> ins2 = reader.Input2_tokens();
	clear_board();
	for (int i = 0; i < ops.size(); ++i) {
	    input1_to_next = ins1[i];
	    input2_to_next = ins2[i];
	    Operand op = ops[i];
	    switch (op) {
		case Operand::AND:
		    add_AND_gate();
		    break;
		case Operand::OR:
		    add_OR_gate();
		    break;
		case Operand::NOT:
		    add_NOT_gate();
		    break;
		default:
		    break;
	    }
	}
	is.close();
    }    catch (...) {
	std::cerr << "Error occurred reading file";
    }
}

void GUI_window::save_file(){
    string file = filename.get_string();
    if(file == "") return;
    std::ofstream os(file, std::ofstream::out);
    for(int i = 3; i < gates.size(); ++i){
	os << *gates[i] << endl;
    }
    os.close();
}

void GUI_window::clear_board(){
    //delete current constructed gates. don't delete inputs
    for( int i = 3; i < gates.size(); ++i){
	detach(*gates[i]);
	delete gates[i];
    }
    gates.clear();
    gates.push_back(&i1);
    attach(*gates[0]);
    gates.push_back(&i2);
    attach(*gates[1]);
    gates.push_back(&i3);
    attach(*gates[2]);
    redraw();
    
    input_lines.clear();
    int n = input_buttons.size();
    for(int i = n-1; i > 2; --i){
	rm_btn();
	tt.rm_column();
    }
}

void GUI_window::rm_btn(){
    int n = input_buttons.size() - 1;
    detach(*input_buttons[n]);
    delete input_buttons[n];
    input_buttons.pop_back();
}

void GUI_window::rm_line(){
    input_lines.rm_line();
}
GUI_window::~GUI_window(){
    
}