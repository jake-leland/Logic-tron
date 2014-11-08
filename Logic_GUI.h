// Logic_GUI.h

#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"

class Logic_GUI {
    int win_w;
    int win_h;
    Simple_window win;
    
public:
    Logic_GUI(int w = 1024, int h = 768);
    
    void add_gate();
};