#include <regex>
#include <string>

#include "Gate_reader.h"

regex Gate_Reader::gate_pat{R"(([[:alpha:]])+\((\d+)(,(\d+))?\))"};

Gate_Reader::Gate_Reader(ifstream& is) : infile(is),ops(),in1(),in2() {
    infile.setf(ios_base::skipws);
}

void Gate_Reader::Open(String file){
    infile.open(file.c_str());
}

void Gate_Reader::get_operand(smatch& matches){
    string op = matches.str(1);
    if(op == "AND") nextOp = Operand::AND;
    else if(op == "OR") nextOp = Operand::OR;
    else if(op == "NOT") nextOp = Operand::NOT;
    else {throw new syntax_error("Unknown operand");}
}

void Gate_Reader::get_positions(smatch& matches) {
    nextIn1 = stoi(matches.str(2));
    if(nextOp != Operand::AND) {
	if(!matches[3].matched) throw new syntax_error("Second input needed.");
	else nextIn2 = stoi(matches.str(4));
    } else {
	if(matches[3].matched) throw new syntax_error("Too many inputs.");
    }
}


void Gate_Reader::Read_file(){
    int lineno = 0;
    try{
	
	for(string line; getline(infile,line); infile.good()){
	    lineno++;
	    smatch matches;
	    if(regex_match(line,matches,gate_pat)){
		get_operand(matches);
		get_positions(matches);
		
	    } else {
		throw new syntax_error(lineno);
	    }
	}
	if(infile.bad()) throw runtime_error("Error reading file");
    } catch(Gate_Reader::syntax_error& s){
	cerr << "Exception thrown reading line "<< lineno << ": " <<s.what();
    } catch(runtime_error& e) {
	throw e;
    }
}