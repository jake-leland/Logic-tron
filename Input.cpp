// Input.cpp

#include "Input.h"


Input::Input(int pos, int win_width) :
	Gate(pos),  //cosnstruct as gate will null ptrs for inputs
	input_line(Point(PADDING_SIDE,PADDING_TOP+(p-1)*SCALE), 
		Point(win_width-PADDING_SIDE,PADDING_TOP+(p-1)*SCALE)), //Draw input line
	input_label(Point(PADDING_SIDE-1.5*SCALE/2,PADDING_TOP+(p-1)*SCALE+SCALE/4),
		to_string(static_cast<char>(64+p))) //Draw label for input (a,b,c))
{
    input_line.set_color(Color::black);
    input_label.set_color(Color::black);
    //Set initial logic values for inputs
    if (p == 1) {
        table = {0, 0, 0, 0, 1, 1, 1, 1};
    } else if (p == 2) {
        table = {0, 0, 1, 1, 0, 0, 1, 1};
    } else if (p == 3) {
        table = {0, 1, 0, 1, 0, 1, 0, 1};
    } else {
	//Only three inputs are expected to be made
        throw std::invalid_argument("Bad constructor to input class");
    }
}

void Input::draw_lines() const {
    input_line.draw();
    input_label.draw();
}