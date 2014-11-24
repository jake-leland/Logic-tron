
#ifndef GATE_READER_H
#define	GATE_READER_H

#include <fstream>
#include <regex>
#include "Gate.h"
using namespace std;

class Gate_Reader {
private:
    static regex gate_pat;
    ifstream& infile;
    
    Operand nextOp;
    int nextIn1;
    int nextIn2;
    
    vector<Operand> ops;
    vector<int> in1;
    vector<int> in2;
    
    void expect(char c);
    void get_operand(smatch& matches);
    void get_positions(smatch& matches);
    
    class syntax_error {
	string whatstr;
    public:
	string what(){ return whatstr;};
	syntax_error(string what_msg):  whatstr(what_msg) {} 
	syntax_error(int line) : 
		whatstr("Syntax error in line "+to_string(line)+"."){}
    };
public:
    Gate_Reader (ifstream& is);
    void Open(string file);
    void Read_file();
    vector<Operand> Operand_tokens() { return ops;}
    vector<int> Input1_tokens() { return in1; }
    vector<int> Input2_tokens() {return in2; }
    
};

#endif	/* GATE_READER_H */

