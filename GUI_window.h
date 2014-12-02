// GUI_window.h

#ifndef GUI_window_h
#define GUI_window_h

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "Gate.h"
#include "Input.h"
#include "TT_window.h"


using namespace Graph_lib;
extern int SCALE;
extern int PADDING_TOP;
extern int PADDING_SIDE;
extern int GATE_PADDING_TOP;
extern int GATE_PADDING_SIDE;

//Need a new class that is not only a collection of lines, but also
//has the ability to remove lines
class Line_stack : public Shape{
    vector<Line*> v;
public:
    Line_stack();
    void set_color(Color c);

    void draw_lines() const;
    
    void add(Point p1, Point p2);
    void clear();
    void rm_line(); 
};

// The GUI_window is where the bulk of the interaction happens
// This window contains the circuit diagram and all of the toolbars/buttons with which the user can interact
class GUI_window : Graph_lib::Window{
    TT_window tt;
    int scale;
    int label_size;
    int padding_top;
    int padding_side;
    
    Line_stack input_lines;
    Line seperator;
    
    Button add_AND;
    Button add_OR;
    Button add_NOT;
    Button open;
    Button save;
    
    In_box filename;
    vector<Button*> input_buttons;
    vector<Gate *> gates;
    
    Text instr;
    int input1_to_next = -1;
    int input2_to_next = -1;
    Input i1;
    Input i2;
    Input i3;
    
    void clear_board();
    void rm_btn();
    void rm_line();
    void rm_gate();
public:
    GUI_window(int w = 1024, int h = 768, int s = 20);
    
    static void cb_click(Address, Address);
    void click(Address);
    
    void add_AND_gate();
    void add_OR_gate();
    void add_NOT_gate();
    void add_line(int i);
    
    void add_gate(String);
    void read_file();
    void save_file();
    virtual ~GUI_window();
};
#endif
