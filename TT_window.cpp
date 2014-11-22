// TT_window.cpp

#include "Gate.h"
#include "TT_window.h"
#include <FL/Fl_Button.H>


TT_window::TT_window(int w, int h) : Window(Point(1024,0), w, h, "Truth Table"),
l(Point(15,39),Point(535,39)) {
    l.set_color(Color::white);
    l.set_style(Line_style::dash);
    redraw();
}

void TT_window::add_column(Gate* g) {
    rects.push_back(new Rectangle(Point(15+20*rects.size(),15),20,190));
    rects[rects.size()-1].set_color(Color::black);
    if(rects.size()%2 == 0) {
        rects[rects.size()-1].set_fill_color(Color::blue);
    } else {
        rects[rects.size()-1].set_fill_color(Color::dark_blue);
    }
    attach(rects[rects.size()-1]);
    
    headers.push_back(new Text(Point(21+20*headers.size(),32),to_string(g->getPosition())));
    headers[headers.size()-1].set_color(Color::white);
    attach(headers[headers.size()-1]);
    
    Vector<bool> table = g->getTable();
    columns.push_back(new Vector_ref<Text>);
    
    for(bool b : table) {
        String b_str(b?"1":"0"); // converts boolean to "0" or "1"
        columns[columns.size()-1].push_back(new Text(Point(21+20*(columns.size()-1),56+20*columns[columns.size()-1].size()),b_str));
        columns[columns.size()-1][columns[columns.size()-1].size()-1].set_color(Color::white);
        attach(columns[columns.size()-1][columns[columns.size()-1].size()-1]);
    }
    
    attach(l);
    redraw();
}