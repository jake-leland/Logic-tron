//  Gate.cpp

#include "Gate.h"

Gate::Gate(int input1, int input2, Operand type)
: i1(input1), i2(input2), t(type){
    if (!is_gate(i1,i2,t)) throw Invalid();
}

bool Gate::is_gate(int i1, int i2, Operand t){
    if ((t != Operand::AND) and (t != Operand::OR) and (t != Operand::NOT))
        return false;
    return true;
    // also check to see if inputs are valid
}

/*ostream& operator<<(ostream& os, const Gate& g)
{
    return os << '(' << g.input1()
    << ',' << g.input2()
    << ',' << g.type()
    << ')';
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Gate& g)
{
    int i1, i2;
    Operand t;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> i1 >> ch2 >> i2 >> ch3 >> t;
    ch4 = t.at(t.size()-1);
    t = t.substr(0,t.size()-1);
    if (!is) return is;
    if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') { // oops: format error
        is.clear(ios_base::failbit);                    // set the fail bit
        return is;
    }
    g = Gate(i1,i2,t);     // update dd
    return is;
}
*/
