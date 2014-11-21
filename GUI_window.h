// GUI_window.h

#ifndef GUI_window_h
#define GUI_window_h

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "Gate.h"

using namespace Graph_lib;
extern int SCALE;
extern int PADDING_TOP;
extern int PADDING_SIDE;
extern int GATE_PADDING_TOP;
extern int GATE_PADDING_SIDE;

class GUI_window : Graph_lib::Window{
    int scale;
    int label_size;
    int padding_top;
    int padding_side;
    Lines input_lines;
    Vector_ref<Text> input_labels;
    Button add_AND;
    Button add_OR;
    Button add_NOT;
    Vector_ref<Button> input_buttons;
    Vector_ref<Gate> gates; // future implementation with the Gate class
    //Vector_ref<Circle> gates; // for now
    Input IN1;
    Input IN2;
    Input IN3;
    int input1_to_next = -1;
    int input2_to_next = -1;
    
    
public:
    GUI_window(int w = 1024, int h = 768, int s = 20);
    
    static void cb_click(Address, Address);
    void click(Address);
    
   // void add_gate(String);
    void add_AND_gate();
    void add_OR_gate();
    void add_NOT_gate();
    void add_line(int i);
};

#endif