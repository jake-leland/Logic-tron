//  Gate.cpp

#include "Gate.h"
#include "std_lib_facilities_4.h"

Gate::Gate(Gate* input1, Gate* input2, Operand type)
: i1(input1), i2(input2), t(type){
    
    if (!is_gate(i1,i2,t)) throw Invalid();
    
    Vector<bool> v1 = input1->getTable();
    Vector<bool> v2 = input2->getTable();
    Vector<bool> vFinal;
    
    if(type==Operand::AND){
        for(int i=0; i<v1.size(); ++i) vFinal.push_back(v1.at(i)&&v2.at(i));
        
    }
    
    else{
        for(int i=0; i<v1.size(); ++i) vFinal.push_back(v1.at(i)||v2.at(i));
    }
    
    v=vFinal;
    
}

Gate::Gate(Gate* input1, Operand type)
: i1(input1), t(type){
    
    if (!is_gate(i1,t)) throw Invalid();
    
    Vector<bool> v1 = input1->getTable();
    for(bool e: v1) v.push_back(!e);
    
}

bool Gate::is_gate(Gate* i1, Gate* i2, Operand t){
    if ((t != Operand::AND) and (t != Operand::OR) and (t != Operand::NOT))
        return false;
    return true;
    // also check to see if inputs are valid
}

bool Gate::is_gate(Gate* i1, Operand t){
    if ((t != Operand::AND) and (t != Operand::OR) and (t != Operand::NOT))
        return false;
    return true;
    // also check to see if inputs are valid
}
