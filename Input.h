// Input.h
#ifndef Input_h
#define Input_h
#include "Gate.h"
#include "Graph.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;

class Input : public Gate {
    //Vector<bool> table; Inherited from gate
    //int position; Inherited from gate
    Line input_line;
    Text input_label;
    Text input_label_left;
    
public:
    Input(int, Vector<int>);
    Input();
    
    //Vector<bool> getTable() const {return table;} Inherited from gate
    //int getPosition() const {return p;} Inherited from gate
    
    void draw_lines() const;
};
#endif