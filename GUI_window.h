// Logic_GUI.h

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace Graph_lib;

class GUI_window : Graph_lib::Window{
    Lines input_lines;
    Button add_AND;
    Button add_OR;
    Button add_NOT;
    //Vector_ref<Gate> gates; // future implementation with the Gate class
    Vector_ref<Circle> gates; // for now
    
public:
    GUI_window(int w = 1024, int h = 768);
    
    static void cb_click(Address, Address);
    void click(Address);
};