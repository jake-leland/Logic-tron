// class.h
#ifndef Gate_h
#define Gate_h

#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "Point.h"
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
using namespace Graph_lib;
extern int X_MAX;
extern int SCALE;
extern int PADDING_TOP;
extern int PADDING_SIDE;
extern int GATE_PADDING_TOP;
extern int GATE_PADDING_SIDE;

enum class Operand{
    NONE = 0, AND, OR, NOT
};

class Gate : public Shape {
    friend class GUI_window;	//just in case
protected:
    Vector_ref<Shape> shapes;
    Gate* i1=NULL;
    Gate* i2=NULL;
    Operand t;
    Vector<bool> table;
    int p;
    Text * in_text;
    
public:
    
    void draw_lines() const;
    
    class Invalid { };
    
    Gate(Gate* input1, Gate* input2, Operand type, int position);
    
    Gate(Gate* input1, Operand type, int position);
    
    Gate(int position);
    
    Gate* input1() const {return i1;};
    Gate* input2() const {return i2;};
    Operand type() const {return t;};
    Vector<bool> getTable() const {return table;}
    int getPosition() const {return p;};
    
    bool is_gate(Gate* i1, Gate* i2, Operand t);
    bool is_gate(Gate* i1, Operand t);
};

ostream& operator<<(ostream& os, const Gate& g);
istream& operator>>(istream& is, Gate& g);

#endif