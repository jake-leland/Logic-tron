//  Gate.cpp

#include "Gate.h"
#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "Point.h"
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>


Gate::Gate(Gate* input1, Gate* input2, Operand type, int position):
	i1(input1), i2(input2), t(type), p(position)
	{
    
    if (!is_gate(i1,i2,t)) throw Invalid();
    
    Vector<bool> v1 = input1->getTable();
    Vector<bool> v2 = input2->getTable();
    Vector<bool> vFinal;

    if(type==Operand::AND){
        for(int i=0; i<v1.size(); ++i) vFinal.push_back(v1.at(i)&&v2.at(i));}
    else{
        for(int i=0; i<v1.size(); ++i) vFinal.push_back(v1.at(i)||v2.at(i));}
    
    table=vFinal;
}

Gate::Gate(Gate* input1, Operand type, int position)
: i1(input1), t(type), p(position){
    
    if (!is_gate(i1,t)) throw Invalid();
    
    Vector<bool> v1 = input1->getTable();
    for(bool e: v1) table.push_back(!e);
}

Gate::Gate(int position) : i1(NULL), i2(NULL), t(Operand::NONE), p(position){
}

bool Gate::is_gate(Gate* i1, Gate* i2, Operand t){
    if ((t != Operand::AND) and (t != Operand::OR) and (t != Operand::NOT))
        return false;
    return true;
}

bool Gate::is_gate(Gate* i1, Operand t){
    if ((t != Operand::AND) and (t != Operand::OR) and (t != Operand::NOT))
        return false;
    return true;
}


void Gate::draw_lines() const{
    if(t == Operand::NONE) return;
    
    Point ul(GATE_PADDING_SIDE + 2*SCALE*(p-4) - .4*SCALE,
             GATE_PADDING_TOP+SCALE*(p-4) -0.3*SCALE);
    
    fl_color(color().as_int());
    
    //Draw gate symbol
    if(t==Operand::AND){
        draw_AND_gate();
    } else if (t==Operand::OR){
        draw_OR_gate();
    } else if (t==Operand::NOT){
        draw_NOT_gate();
    }
    
    //Draw lines to input lines
    int iny1 = GATE_PADDING_TOP + SCALE*((i1->p)-3) - .5*SCALE;
    int iny2 = 0;
    if(i2) iny2 = GATE_PADDING_TOP + SCALE*((i2->p)-3) - .5*SCALE;
    if(t == Operand::NOT){
        draw_one_line();
    } else {
        draw_two_lines();
    }
    fl_line(ul.x+(.8*SCALE)/2,ul.y+(.6*SCALE),ul.x+(.8*SCALE)/2,GATE_PADDING_TOP+SCALE/2+SCALE*(p-4));

}

void Gate::draw_OR_gate(){
    fl_arc(ul.x,ul.y-(.6*SCALE)/2,.8*SCALE,.9*SCALE,180,360);
    fl_arc(ul.x,ul.y-(.6*SCALE)/2,.8*SCALE,.6*SCALE,180,360);
    fl_line(ul.x+(.8*SCALE)/4,ul.y,ul.x+(.8*SCALE)/4,ul.y+(.6*SCALE)/3);
    fl_line(ul.x+3*(.8*SCALE)/4,ul.y,ul.x+3*(.8*SCALE)/4,ul.y+(.6*SCALE)/3);
}
void Gate::draw_NOT_gate(){
    fl_line(ul.x,ul.y,ul.x+(.8*SCALE),ul.y);
    fl_line(ul.x+(.8*SCALE),ul.y,ul.x+(.8*SCALE)/2,ul.y+(.6*SCALE));
    fl_line(ul.x+(.8*SCALE)/2,ul.y+(.6*SCALE),ul.x,ul.y);
    fl_circle(ul.x+(.8*SCALE)/2,ul.y+(.6*SCALE), SCALE/10);
}
void Gate::draw_AND_gate(){
    fl_arc(ul.x,ul.y,.8*SCALE,.6*SCALE,180,360);
    fl_line(ul.x,ul.y+(.6*SCALE)/2,ul.x,ul.y);
    fl_line(ul.x,ul.y,ul.x+(.8*SCALE),ul.y);
    fl_line(ul.x+(.8*SCALE),ul.y,ul.x+(.8*SCALE),ul.y+(.6*SCALE)/2);
    
}

void Gate::draw_one_line(){
    fl_line(ul.x+(.8*SCALE)/2s, ul.y, ul.x+(.8*SCALE)/2, iny1);
    fl_circle(ul.x+(.8*SCALE)/2, iny1, 1);
}
void Gate::draw_two_lines(){
    fl_line(ul.x+(.8*SCALE)/4,ul.y,ul.x+(.8*SCALE)/4, iny1);
    fl_circle(ul.x+(.8*SCALE)/4, iny1, 1);
    fl_line(ul.x+3*(.8*SCALE)/4,ul.y,ul.x+3*(.8*SCALE)/4, iny2);
    fl_circle(ul.x+3*(.8*SCALE)/4, iny2, 1);
}

ostream& operator<<(ostream& os, const Gate& g){
    
    string t;
    //check which type of gate
    switch(g.type()){
        case Operand::AND : t="AND"; break;
        case Operand::OR : t="OR"; break;
        default: t = "NOT";
    }
    
    //read in gate
    if(g.type() == Operand::NOT){
        os << g.getPosition() << ": (" << t << "," << g.input1()->getPosition() << ")";
    }
    else{
        os << g.getPosition() << ": (" << t <<","<< g.input1()->getPosition() << "," << g.input2()->getPosition() <<")";
    }
    
    return os;
}