// TT_window.h

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace Graph_lib;

// The TT_window displays the columns of the truth table that correspond with the gates in the GUI_window
class TT_window : Graph_lib::Window{
    vector<Rectangle*> rects;
    vector<Text*> headers;
    vector< vector<Text*> > columns;
    vector<bool> desiredTable;
    Line l;
public:
    TT_window(int w = 700, int h = 300);

    void add_column(Gate*);
    void rm_column();
    bool match_truth_table(Gate*);
    void update_desired_table(String s);
    ~TT_window();
};