// Input.h

#include "Graph.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;

class Input : public Shape {
    Vector<bool> table;
    int position;
    Line input_line;
    Text input_label;
    Text input_label_left;
    
public:
    Input(int, Vector<int>);
    
    Input();
    
    Vector<bool> getTable() const {return table;}
    int getPosition() const {return position;}
    
    void draw_lines() const;
};