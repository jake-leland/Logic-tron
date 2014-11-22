// TT_window.cpp

#include "Gate.h"
#include "TT_window.h"
#include <FL/Fl_Button.H>


TT_window::TT_window(int w, int h) : Window(Point(1024,0), w, h, "Truth Table") {
    redraw();
}

void TT_window::add_column(Gate* g) {
    Vector<bool> table = g->getTable();
    String column;
    for(bool b : table) {
        String b_str(b?"1":"0"); // converts boolean to "0" or "1"
        column += b_str + "\n";
    }
    columns.push_back(new Out_box(Point(100+15*(columns.size()),100),0,0,column));
    attach(columns[columns.size()-1]);
    redraw();
}