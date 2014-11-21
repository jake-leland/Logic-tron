//  Gate.cpp

#include "Gate.h"
#include "std_lib_facilities_4.h"
#include <FL/Fl.H>

Gate::Gate(int position) : i1(NULL), i2(NULL), t(Operand::NONE), p(position){
    
}

Gate::Gate(Gate* input1, Gate* input2, Operand type, int position)
: i1(input1), i2(input2), t(type), p(position){
    
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

Gate::Gate(Gate* input1, Operand type, int position)
: i1(input1), t(type), p(position){
    
    if (!is_gate(i1,t)) throw Invalid();
    
    Vector<bool> v1 = input1->getTable();
    for(bool e: v1) v.push_back(!e);
    
}

bool Gate::is_gate(Gate* i1, Gate* i2, Operand t){
    if ((t != Operand::NONE) and (t != Operand::AND) and (t != Operand::OR) and (t != Operand::NOT))
        return false;
    return true;
    // also check to see if inputs are valid
}

bool Gate::is_gate(Gate* i1, Operand t){
    if ((t != Operand::NONE) and (t != Operand::AND) and (t != Operand::OR) and (t != Operand::NOT))
        return false;
    return true;
    // also check to see if inputs are valid
}

void Gate::draw_lines() const{
    if(t == Operand::NONE) return;
    
    int gate_padding_top = PADDING_TOP+ 2.5*SCALE; 
    int gate_padding_left = PADDING_SIDE + 2*SCALE; 
    
    Point ul(gate_padding_left + 2*SCALE*(p-3) - .5*SCALE, 
	    gate_padding_top+SCALE*(p-3) -0.5*SCALE);
    
    fl_color(color().as_int());
    //Draw gate symbol
    if(t==Operand::AND){
	fl_arc(ul.x,ul.y,SCALE,SCALE,180,360);
	fl_line(ul.x,ul.y+SCALE/2,ul.x,ul.y);
	fl_line(ul.x,ul.y,ul.x+SCALE,ul.y);
	fl_line(ul.x+SCALE,ul.y,ul.x+SCALE,ul.y+SCALE/2);
    } else if (t==Operand::OR){
	//Need something fancy for OR gate symbol
	fl_arc(ul.x,ul.y,SCALE,SCALE,0,360);
    } else if (t==Operand::NOT){
	fl_line(ul.x,ul.y,ul.x+SCALE,ul.y);
	fl_line(ul.x+SCALE,ul.y,ul.x+SCALE/2,ul.y+SCALE);
	fl_line(ul.x+SCALE/2,ul.y+SCALE,ul.x,ul.y);
	fl_arc(ul.x+SCALE/2-1,ul.y+SCALE-1,4,4,0,360);
    }
    //Draw lines to input lines
    int iny1 = gate_padding_top + SCALE*((i1->p)-2) - .5*SCALE;
    int iny2 = 0;
    if(i2) iny2 = gate_padding_top + SCALE*((i2->p)-2) - .5*SCALE;
    if(t == Operand::NOT){
	fl_line(ul.x+SCALE/2, ul.y, ul.x+SCALE/2, iny1);
    } else {
	fl_line(ul.x+SCALE/4,ul.y,ul.x+SCALE/4, iny1);
	fl_line(ul.x+3*SCALE/4,ul.y,ul.x+3*SCALE/4, iny2);
    }
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


Input::Input(int position) : Gate(position) {
    if(p == 0){
	v = {0,0,0,0,1,1,1,1};
    } else if (p == 1) {
	v = {0,0,1,1,0,0,1,1};
    } else if (p == 2) {
	v = {0,1,0,1,0,1,0,1};
    } else {
	throw std::invalid_argument("Bad constructor to input class");
    }
}

