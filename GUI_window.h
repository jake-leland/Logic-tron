// GUI_window.h

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "TT_window.h"

using namespace Graph_lib;

class GUI_window : Graph_lib::Window{
    TT_window tt;
    int scale;
    int label_size;
    int padding_top;
    int padding_side;
    Lines input_lines;
    Vector_ref<Text> input_labels;
    Line seperator;
    Button add_AND;
    Button add_OR;
    Button add_NOT;
    Vector_ref<Button> input_buttons;
    //Vector_ref<Gate> gates; // future implementation with the Gate class
    Vector_ref<Circle> gates; // for now
    
public:
    GUI_window(int w = 1024, int h = 768, int s = 20);
    
    static void cb_click(Address, Address);
    void click(Address);
    
    void add_gate(String);
};