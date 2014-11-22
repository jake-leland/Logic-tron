// Input.cpp

#include "Input.h"

// Window Data
// 0: width
// 1: height
// 2: scale
// 3: side padding
// 4: top padding


Input::Input(int pos, int win_width) :
Gate(pos),
input_line(Point(PADDING_SIDE,PADDING_TOP+(p-1)*SCALE), Point(win_width-PADDING_SIDE,PADDING_TOP+(p-1)*SCALE)),
input_label(Point(PADDING_SIDE-1.5*SCALE/2,PADDING_TOP+(p-1)*SCALE+SCALE/4),to_string(static_cast<char>(64+p)))
{
    input_line.set_color(Color::black);
    input_label.set_color(Color::black);
    
    if (p == 1) {
        table.push_back(0);
        table.push_back(0);
        table.push_back(0);
        table.push_back(0);
        table.push_back(1);
        table.push_back(1);
        table.push_back(1);
        table.push_back(1);
    } else if (p == 2) {
        table.push_back(0);
        table.push_back(0);
        table.push_back(1);
        table.push_back(1);
        table.push_back(0);
        table.push_back(0);
        table.push_back(1);
        table.push_back(1);
    } else if (p == 3) {
        table.push_back(0);
        table.push_back(1);
        table.push_back(0);
        table.push_back(1);
        table.push_back(0);
        table.push_back(1);
        table.push_back(0);
        table.push_back(1);
    } else {
        throw std::invalid_argument("Bad constructor to input class");
    }
    
    /*
    if (p == 1) {
        table = {0, 0, 0, 0, 1, 1, 1, 1};
    } else if (p == 2) {
        table = {0, 0, 1, 1, 0, 0, 1, 1};
    } else if (p == 3) {
        table = {0, 1, 0, 1, 0, 1, 0, 1};
    } else {
        throw std::invalid_argument("Bad constructor to input class");
    }
     */
    
    // for some reason, the above code doesn't compile in my IDE
    // I'll just need to remember to return it to the prettier form before we turn it in
}

void Input::draw_lines() const {
    input_line.draw();
    input_label.draw();
}