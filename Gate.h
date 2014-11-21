// class.h

#ifndef Gate_h
#define Gate_h

#include "std_lib_facilities_4.h"
#include "Graph.h"

using namespace Graph_lib;

extern int SCALE;
extern int PADDING_SIDE;
extern int PADDING_TOP;

enum class Operand{
    NONE = 0, AND, OR, NOT};

class Gate : public Shape{
protected:
    Gate* i1=NULL;
    Gate* i2=NULL;
    Operand t;
    Vector<bool> v;
    int p;
    
public:
    class Invalid { };
    
    Gate(Gate* input1, Gate* input2, Operand type, int position);
    
    Gate(Gate* input1, Operand type, int position);
    
    Gate(int position);
    
    Gate* input1() const {return i1;};
    Gate* input2() const {return i2;};
    Operand type() const {return t;};
    Vector<bool> getTable() const {return v;}
    int getPosition() const {return p;};
    void draw_lines() const;
    bool is_gate(Gate* i1, Gate* i2, Operand t);
    bool is_gate(Gate* i1, Operand t);
};

class Input : public Gate {
public:
    Input( int pos );
    void draw_lines(){}
};


ostream& operator<<(ostream& os, const Gate& g);
istream& operator>>(istream& is, Gate& g);

#endif