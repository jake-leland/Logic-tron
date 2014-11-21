// GUI_window.h

#ifndef GUI_window_h
#define GUI_window_h

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
<<<<<<< HEAD
#include "Gate.h"
=======
#include "TT_window.h"
>>>>>>> FETCH_HEAD

using namespace Graph_lib;
extern int SCALE;
extern int PADDING_TOP;
extern int PADDING_SIDE;
extern int GATE_PADDING_TOP;
extern int GATE_PADDING_SIDE;

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
<<<<<<< HEAD
    Vector_ref<Gate> gates; // future implementation with the Gate class
    //Vector_ref<Circle> gates; // for now
    Input IN1;
    Input IN2;
    Input IN3;
    int input1_to_next = -1;
    int input2_to_next = -1;
    
=======
    Vector_ref<Gate> gates1; // future implementation with the Gate class
    Vector_ref<Circle> gates; // for now
    Input i1;
    Input i2;
    Input i3;
>>>>>>> FETCH_HEAD
    
public:
    GUI_window(int w = 1024, int h = 768, int s = 20);
    
    static void cb_click(Address, Address);
    void click(Address);
    
<<<<<<< HEAD
   // void add_gate(String);
    void add_AND_gate();
    void add_OR_gate();
    void add_NOT_gate();
    void add_line(int i);
};

#endif
=======
    void add_gate(String);
    
    Vector<int> get_window_data();
    // Returns a vector of window data
    // Certain properties of the window are stored at specific indices of this vector
    // 0: width
    // 1: height
    // 2: scale
    // 3: side padding
    // 4: top padding
};
>>>>>>> FETCH_HEAD
