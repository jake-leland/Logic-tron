// Input.cpp

#include "Input.h"

// Window Data
// 0: width
// 1: height
// 2: scale
// 3: side padding
// 4: top padding

Input::Input(int pos, Vector<int> win_data) :
position(pos),
input_line(Point(win_data[3],win_data[4]+(position-1)*win_data[2]), Point(win_data[0]-win_data[3],win_data[4]+(position-1)*win_data[2])),
input_label(Point(win_data[0]-win_data[3]+win_data[2]/4,win_data[4]+(position-1)*win_data[2]+win_data[2]/4),to_string(position)),
input_label_left(Point(win_data[3]-1.5*win_data[2]/2,win_data[4]+(position-1)*win_data[2]+win_data[2]/4),to_string(static_cast<char>(64+position)))
{
    input_line.set_color(Color::black);
    input_label_left.set_color(Color::black);
    input_label.set_color(Color::black);
    
    /*
    if (position == 1) {
        table.push_back(0);
        table.push_back(0);
        table.push_back(0);
        table.push_back(0);
        table.push_back(1);
        table.push_back(1);
        table.push_back(1);
        table.push_back(1);
    } else if (position == 2) {
        table.push_back(0);
        table.push_back(0);
        table.push_back(1);
        table.push_back(1);
        table.push_back(0);
        table.push_back(0);
        table.push_back(1);
        table.push_back(1);
    } else if (position == 3) {
        table.push_back(0);
        table.push_back(1);
        table.push_back(0);
        table.push_back(1);
        table.push_back(0);
        table.push_back(1);
        table.push_back(0);
        table.push_back(1);
    } else {
        cerr << "error: invalid position";
    }
     */
}

void Input::draw_lines() const {
    input_line.draw();
    input_label.draw();
    input_label_left.draw();
}