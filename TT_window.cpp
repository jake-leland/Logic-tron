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

// function accepts a gate pointer, then retrieves the truth table information from that gate
// a new column is automatically added that displays this truth table
void TT_window::add_column(Gate* g) {
    rects.push_back(new Rectangle(Point(15+20*rects.size(),15),20,190));
    rects[rects.size()-1]->set_color(Color::black);
    if(rects.size()%2 == 0) {
        rects[rects.size()-1]->set_fill_color(Color::blue);
    } else {
        rects[rects.size()-1]->set_fill_color(Color::dark_blue);
    }
    attach(*rects[rects.size()-1]); // background color
    headers.push_back(new Text(Point(21+20*headers.size(),32),to_string(g->getPosition())));
    headers[headers.size()-1]->set_color(Color::white);
    attach(*headers[headers.size()-1]);
    
    columns.push_back(vector<Text*>());
    Vector<bool> table = g->getTable();
    for(bool b : table) {
        String b_str(b?"1":"0"); // converts boolean to "0" or "1"
        columns[columns.size()-1].push_back(new Text(Point(21+20*(columns.size()-1),56+20*columns[columns.size()-1].size()),b_str));
        columns[columns.size()-1][columns[columns.size()-1].size()-1]->set_color(Color::white);
        attach(*columns[columns.size()-1][columns[columns.size()-1].size()-1]);
    }
    attach(l); // dotted line seperating the header text from the table contents
    redraw();
}

// removes the most recently added column
// as if popping off of a stack
void TT_window::rm_column(){
    int n = rects.size() - 1;
    detach(*rects[n]);
    delete rects[n];
    rects.pop_back();
    
    n = headers.size() - 1;
    detach(*headers[n]);
    delete headers[n];
    headers.pop_back();
    
    n = columns.size() - 1;
    int m = columns[n].size() -1;
    auto itbegin = columns[n].begin();
    auto itend = columns[n].end();
    for(auto it = itbegin; it != itend; ++it){
	detach(*(*it));
	delete (*it);
    }
    columns.pop_back();
}