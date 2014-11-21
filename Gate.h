// class.h

#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "Point.h"
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>


enum class Operand{
    AND = 1, OR, NOT};

class Gate : Shape {
    
    Vector_ref<Shape> v;
    Gate* i1=NULL;
    Gate* i2=NULL;
    Operand t;
    Vector<bool> v;
    int p;
    Vector
    
public:
    
    void draw_lines() const{ for(int i = 0; i< v.size(); ++i) {v[i].draw();} }
    
    class Invalid { };
    
    Gate(Gate* input1, Gate* input2, Operand type, int position);
    
    Gate(Gate* input1, Operand type, int position);
    
    Gate();
    
    Gate* input1() const {return i1;};
    Gate* input2() const {return i2;};
    Operand type() const {return t;};
    Vector<bool> getTable() const {return v;}
    int getPosition() const {return p;};
    
    bool is_gate(Gate* i1, Gate* i2, Operand t);
    bool is_gate(Gate* i1, Operand t);
};

ostream& operator<<(ostream& os, const Gate& g);
istream& operator>>(istream& is, Gate& g);