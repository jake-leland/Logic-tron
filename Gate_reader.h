//Gate_reader.h

#ifndef GATE_READER_H
#define	GATE_READER_H

#include <fstream>
#include <regex>
#include "Gate.h"
using namespace std;

// Gate_Reader class: Responsible for parsing a given input file into lists
// of operands and inputs, which the GUI window can read off to construct
// the sequence of gates to be loaded.
// Gate_Reader uses the C++11 header <regex> for regular expression
// functionality, that is the STL functions to parse strings.
class Gate_Reader {
    
private:
    static regex gate_pat;  //The pattern of input to be matched from files
    ifstream& infile;	//The input stream of the file to be read
    
    Operand nextOp; //Keeps track of operand read on current line
    int nextIn1;    //Input 1 read on current line
    int nextIn2;    //Input 2 read on current line
    
    vector<Operand> ops;    //Sequence of operantions
    vector<int> in1;	//Input 1 sequence
    vector<int> in2;	//Input 2 sequence
    
    //Functions to set operand and inputs from the current line match
    void get_operand(smatch& matches);
    void get_positions(smatch& matches);
    
    //Class for throwing syntax errors
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

#endif

