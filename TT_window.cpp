// TT_window.cpp

#include "Gate.h"
#include "TT_window.h"
#include <FL/Fl_Button.H>


TT_window::TT_window(int w, int h) : Window(Point(1024,0), w, h, "Truth Table"),
l(Point(15,39),Point(590,39)) {
    l.set_color(Color::white);
    l.set_style(Line_style::dash);
    redraw();
    String s = "00000000";
    make_desired_table(s);
}

// function accepts a gate pointer, then retrieves the truth table information from that gate
// a new column is automatically added that displays this truth table
void TT_window::add_column(Gate* g) {
    
    rects.push_back(new Rectangle(Point(15+20*(rects.size()-1),15),20,190));
    rects[rects.size()-1]->set_color(Color::black);
    
    if(rects.size()%2 == 0) {
        rects[rects.size()-1]->set_fill_color(Color::blue);
    } else {
        rects[rects.size()-1]->set_fill_color(Color::dark_blue);
    }
    
    attach(*rects[rects.size()-1]); // background color
    headers.push_back(new Text(Point(21+20*(headers.size()-1),32),to_string(g->getPosition())));
    headers[headers.size()-1]->set_color(Color::white);
    attach(*headers[headers.size()-1]);
    
    columns.push_back(vector<Text*>());
    Vector<bool> table = g->getTable();
    
    for(bool b : table) {
        String b_str(b?"1":"0"); // converts boolean to "0" or "1"
        columns[columns.size()-1].push_back(new Text(Point(21+20*(columns.size()-2),56+20*columns[columns.size()-1].size()-1),b_str));
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

bool TT_window::match_truth_table(Gate* g){
    Vector<bool> table = g->getTable();
}

void TT_window::update_desired_table(String s){
    rects.push_back(new Rectangle(Point(550,15),40,190));
    rects[rects.size()-1]->set_color(Color::black);
    rects[rects.size()-1]->set_fill_color(Color::magenta);
    
    attach(*rects[rects.size()-1]); // background color
    headers.push_back(new Text(Point(555,32),"Goal"));
    headers[headers.size()-1]->set_color(Color::white);
    attach(*headers[headers.size()-1]);
    
	Vector<bool> table;
	for(int i = 0; i<s.size(); ++i) {
		String sub = s.substr(i,1);
		if(sub=="0") table.push_back(false);
		else table.push_back(true);
	}

	columns.push_back(vector<Text*>());
    for(bool b : table) {
        String b_str(b?"1":"0"); // converts boolean to "0" or "1"
        columns[columns.size()-1].push_back(new Text(Point(560,56+20*columns[columns.size()-1].size()),b_str));
        columns[columns.size()-1][columns[columns.size()-1].size()-1]->set_color(Color::white);
        attach(*columns[columns.size()-1][columns[columns.size()-1].size()-1]);
    }

}

TT_window::~TT_window(){
    for(Rectangle * r : rects){
	delete r;
    }
    for(Text * t : headers){
	delete t;
    }
    for( vector<Text*> v : columns){
	for( Text* t : v){
	    delete t;
	}
    }
}