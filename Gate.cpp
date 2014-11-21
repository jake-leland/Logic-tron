//  Gate.cpp

#include "Gate.h"
#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "Point.h"
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>

Gate::Gate(Gate* input1, Gate* input2, Operand type, int position)
: i1(input1), i2(input2), t(type), p(position){
    
    if (!is_gate(i1,i2,t)) throw Invalid();
    
    Vector<bool> v1 = input1->getTable();
    Vector<bool> v2 = input2->getTable();
    Vector<bool> vFinal;
    
    if(type==Operand::AND){
        for(int i=0; i<v1.size(); ++i) vFinal.push_back(v1.at(i)&&v2.at(i));
        /*    To be filled in with actual shapes
        v.push_back(new fl_arc(100.0, 100.0, 50.0, 0.0, 180.0) );
        v.push_back(new Line());
        v.push_back(new Circle(Point(x+(r/4),y-(r/4)),r/8));
         */
        
    }
    
    else{
        for(int i=0; i<v1.size(); ++i) vFinal.push_back(v1.at(i)||v2.at(i));
        /*   To be filled in with actual shapes
         v.push_back(new fl_arc(100.0, 100.0, 50.0, 0.0, 180.0) );
         v.push_back(new Line());
         v.push_back(new Circle(Point(x+(r/4),y-(r/4)),r/8));
         */
    }
    
    v=vFinal;
    
}

Gate::Gate(Gate* input1, Operand type, int position)
: i1(input1), t(type), p(position){
    
    if (!is_gate(i1,t)) throw Invalid();
    
    Vector<bool> v1 = input1->getTable();
    for(bool e: v1) v.push_back(!e);
    
    /*   To be filled in with actual shapes
     v.push_back(new fl_arc(100.0, 100.0, 50.0, 0.0, 180.0) );
     v.push_back(new Line());
     v.push_back(new Circle(Point(x+(r/4),y-(r/4)),r/8));
     */
    
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

ostream& operator<<(ostream& os, const Gate& g){
    
    string t;
    switch(g.type()){
        case Operand::AND : t="AND"; break;
        case Operand::OR : t="OR"; break;
        default: t = "NOT";
    }
    
    if(g.type() == Operand::NOT){
        os << g.getPosition() << ": (" << t << "," << g.input1()->getPosition() << ")";
    }
    else{
        os << g.getPosition() << ": (" << t <<","<< g.input1()->getPosition() << "," << g.input2()->getPosition() <<")";
    }
    
    return os;
}

istream& operator>>(istream& is, Gate& g){
    //read in
    return is;
}

