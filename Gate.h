// class.h

#include "std_lib_facilities_4.h"


enum class Operand{
    AND = 1, OR, NOT};

class Gate{
    Gate* i1=NULL;
    Gate* i2=NULL;
    Operand t;
    Vector<bool> v;
    int p;
    
public:
    class Invalid { };
    
    Gate(Gate* input1, Gate* input2, Operand type, int position);
    
    Gate(Gate* input1, Operand type, int position);
    
    Gate();
    
    Gate* input1() const {return i1;};
    Gate* input2() const {return i2;};
    Operand type() const {return t;};
    Vector<bool> getTable() const {return v;}
    int getPosition() const {return p};
    
    bool is_gate(Gate* i1, Gate* i2, Operand t);
    bool is_gate(Gate* i1, Operand t);
};

ostream& operator<<(ostream& os, const Gate& g);
istream& operator>>(istream& is, Gate& g);