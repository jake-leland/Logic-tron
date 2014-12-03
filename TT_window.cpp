// TT_window.cpp

#include <FL/Fl_Button.H>
#include "Gate.h"
#include "TT_window.h"


TT_window::TT_window(int w, int h) : 
	Window(Point(1024,0), w, h, "Truth Table"),
	desired_rect(Point(550,15),40,190),
	desired_header(Point(555,32),"Goal"),
	l(Point(15,39),Point(590,39)),
	desired_in( Point(150, y_max()-50),150,25,"Desired Table" ),
	set_goal( Point(300, y_max()-50),50,25, "Set",
		[](Address, Address pw) {
		    reference_to<TT_window>(pw).set_goal_cb(); } )
{
    desired_rect.set_color(Color::black);
    desired_rect.set_fill_color(Color::magenta);
    desired_header.set_color(Color::white);
    attach(desired_rect);
    attach(desired_header);
    attach(desired_in);
    attach(set_goal);
    l.set_color(Color::white);
    l.set_style(Line_style::dash);
    redraw();
    String s = "00000000";
    update_desired_table(s);
}

// function accepts a gate pointer, then retrieves the truth table information from that gate
// a new column is automatically added that displays this truth table
void TT_window::add_column(Gate* g) {
    
    rects.push_back(new Rectangle(Point(15+20*(rects.size()),15),20,190));
    rects[rects.size()-1]->set_color(Color::black);
    
    if(rects.size()%2 == 0) {
        rects[rects.size()-1]->set_fill_color(Color::blue);
    } else {
        rects[rects.size()-1]->set_fill_color(Color::dark_blue);
    }
    
    attach(*rects[rects.size()-1]); // background color
    headers.push_back(new Text(Point(21+20*(headers.size()),32),to_string(g->getPosition())));
    headers[headers.size()-1]->set_color(Color::white);
    attach(*headers[headers.size()-1]);
    
    columns.push_back(vector<Text*>());
    Vector<bool> table = g->getTable();
    
    for(bool b : table) {
        String b_str(b?"1":"0"); // converts boolean to "0" or "1"
        columns[columns.size()-1].push_back(new Text(Point(21+20*(columns.size()-1),56+20*columns[columns.size()-1].size()-1),b_str));
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
    redraw();
}

bool TT_window::match_truth_table(Gate* g){
    Vector<bool> table = g->getTable();
}
void TT_window::set_goal_cb(){
    std::regex p{R"([01]{8})"};
    smatch matches;
    string in = desired_in.get_string();
    if(regex_match(in, matches, p)){
	update_desired_table(in);
	cout << "Regex match " << in << endl;
    }
}
void TT_window::update_desired_table(String s){
    Vector<bool> table;
    for(int i = 0; i<s.size(); ++i) {
	String sub = s.substr(i,1);
	if(sub=="0") table.push_back(false);
	else table.push_back(true);
    }
    for(Text* t : desired_column){
	detach(*t);
	delete t;
    }
    desired_column.clear();
    
    for(bool b : table) {
        String b_str(b?"1":"0"); // converts boolean to "0" or "1"
        desired_column.push_back(new Text(Point(560,56+20*desired_column.size()),b_str));
        desired_column.back()->set_color(Color::white);
        attach(*(desired_column.back()));
    }
    redraw();

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