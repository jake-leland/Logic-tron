// class.h

#include "std_lib_facilities_4.h"

class Gate{
    int i1;
    int i2;
    String t;
    
public:
    class Invalid { };
    
    Gate(int input1, int input2, String type);
    
    int input1() const {return i1;};
    int input2() const {return i2;};
    String type() const {return t;};
    
    bool is_gate(int i1, int i2, String t);
};

ostream& operator<<(ostream& os, const Gate& g);
istream& operator>>(istream& is, Gate& g);