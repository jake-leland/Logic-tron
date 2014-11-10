// Logic_GUI.h

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"

using namespace Graph_lib;

class GUI_window : Graph_lib::Window{
public:
    GUI_window(int w = 1024, int h = 768);
    
    void add_gate();
};