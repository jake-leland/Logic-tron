// Input.h
#ifndef Input_h
#define Input_h
#include "Gate.h"
#include "Graph.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;
extern int SCALE;
extern int PADDING_TOP;
extern int PADDING_SIDE;

/* Input class - A specialization of gate that is initialized with the GUI window
 * We expect only three to be initialized per window
 */
class Input : public Gate {
    //Vector<bool> table; Inherited from gate
    //int position; Inherited from gate
    Line input_line;
    Text input_label;
    
public:
    Input(int, int);
    Input();
    
    //Vector<bool> getTable() const {return table;} Inherited from gate
    //int getPosition() const {return p;} Inherited from gate
    
    void draw_lines() const;
};
#endif