#include <regex>
#include <string>

#include "Gate_reader.h"

/*
 * regex gate_pat
 * This member is constructed using the C++11 features of raw string literals
 * and initializing braces.
 * This regex type tells the class we expect the line to match the following pattern:
 *	Start with a number and a colon;
 *	Optionally any amount of whitespace;
 *	Opening parenthesis, followed by an alphabetical string, then a comma;
 *	A numeric string;
 *	Optionally, a comma and a second numeric string;
 *	Close parenthesis;
 * Example: 
 *	4:(AND,1,2)
 *	5:	(NOT,3)
 * 
 * Each line is checked to match this pattern, then the get_ functions set
 * the operand and inputs read. Should no error be thrown the data is pushed
 * onto the vectors. Once every line is read without error the vectors are ready to
 * be returned.
 */
regex Gate_Reader::gate_pat{R"(\d+:\s*\(([[:alpha:]]+),(\d+)(,(\d+))?\))"};

Gate_Reader::Gate_Reader(ifstream& is) : infile(is),ops(),in1(),in2() {
    infile.setf(ios_base::skipws);
}

void Gate_Reader::Open(String file){
    infile.open(file.c_str());
}

void Gate_Reader::get_operand(smatch& matches){
    string op = matches.str(1);
    cout << op << endl;
    if(op == "AND") nextOp = Operand::AND;
    else if(op == "OR") nextOp = Operand::OR;
    else if(op == "NOT") nextOp = Operand::NOT;
    else {throw syntax_error("Unknown operand");}
}

void Gate_Reader::get_positions(smatch& matches) {
    nextIn1 = stoi(matches.str(2));
    if(nextOp != Operand::NOT) {
	if(!matches[3].matched) throw new syntax_error("Second input needed.");
	else nextIn2 = stoi(matches.str(4));
    } else {
	if(matches[3].matched) throw new syntax_error("Too many inputs.");
	nextIn2 = -1;
    }
}

/* !!!!!!!!!! FUNCTION LENGTH !!!!!!!!!! */
void Gate_Reader::Read_file(){
    int lineno = 0;
    try{
	if(!infile.is_open()) throw runtime_error("File not opened");
	for(string line; std::getline(infile,line); infile.good()){
	    lineno++;
	    smatch matches;
	    if(regex_match(line,matches,gate_pat)){
		get_operand(matches);
		get_positions(matches);
		ops.push_back(nextOp);
		in1.push_back(nextIn1);
		in2.push_back(nextIn2);
	    } else {
		throw syntax_error(lineno);
	    }
	}
	if(infile.bad()) throw runtime_error("Error reading file");
    } catch(Gate_Reader::syntax_error& s){
	cerr << "Exception thrown reading line "<< lineno << ": " <<s.what();
    } catch(runtime_error& e) {
	cout << "Read_file exception: " << e.what();
	throw e;
    } catch (...) {
	throw;
    }
}