// Input.cpp

#include "Input.h"


Input::Input(int pos, int win_width) :
	Gate(pos),
	input_line(Point(PADDING_SIDE,PADDING_TOP+(p-1)*SCALE), 
		Point(win_width-PADDING_SIDE,PADDING_TOP+(p-1)*SCALE)),
	input_label(Point(PADDING_SIDE-1.5*SCALE/2,PADDING_TOP+(p-1)*SCALE+SCALE/4),
		to_string(static_cast<char>(64+p)))
{
    input_line.set_color(Color::black);
    input_label.set_color(Color::black);
    
    if (p == 1) {
        table = {0, 0, 0, 0, 1, 1, 1, 1};
    } else if (p == 2) {
        table = {0, 0, 1, 1, 0, 0, 1, 1};
    } else if (p == 3) {
        table = {0, 1, 0, 1, 0, 1, 0, 1};
    } else {
        throw std::invalid_argument("Bad constructor to input class");
    }
}

void Input::draw_lines() const {
    input_line.draw();
    input_label.draw();
}