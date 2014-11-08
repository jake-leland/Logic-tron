// class.h

#include "std_lib_facilities_4.h"


enum class Operand{
    AND = 1, OR, NOT};

class Gate{
    int i1;
    int i2;
    Operand t;
    
public:
    class Invalid { };
    
    Gate(int input1, int input2, Operand type);
    
    Gate(int input1, Operand type);
    
    Gate();
    
    int input1() const {return i1;};
    int input2() const {return i2;};
    Operand type() const {return t;};
    
    bool is_gate(int i1, int i2, Operand t);
};

ostream& operator<<(ostream& os, const Gate& g);
istream& operator>>(istream& is, Gate& g);