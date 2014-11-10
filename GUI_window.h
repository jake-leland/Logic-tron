// Logic_GUI.h

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace Graph_lib;

class GUI_window : Graph_lib::Window{
    bool updating;
    
public:
    GUI_window(int w = 1024, int h = 768);
    
    static void cb_add_AND_click(Address b, Address pw);
    void add_AND_click();
    static void cb_add_OR_click(Address b, Address pw);
    void add_OR_click();
    static void cb_add_NOT_click(Address b, Address pw);
    void add_NOT_click();
    
    void keep_open();
    void update();
};