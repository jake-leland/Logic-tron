// Logic-tron.cpp

#include "std_lib_facilities_4.h"

#include "Gate.h"
#include "GUI_window.h"

Vector<Gate*> gate_pointers;

int SCALE = 20;
int LABEL_SIZE = .7*SCALE;
int PADDING_TOP = 768/20;
int PADDING_SIDE = 1024/25;
int GATE_PADDING_TOP = PADDING_TOP + 2.5*SCALE;
int GATE_PADDING_SIDE = PADDING_SIDE + 2*SCALE;

/*
void save(String filename) {
    ofstream ofs(filename.c_str());
    // throw an error if the file is unable to be opened
    if (!ofs) error("can’t open output file ", filename);
 
    for (auto g : gate_pointers) {
        ofs << *g;
    }
 
    return;
}

void load(String filename) {
    ifstream ifs(filename.c_str());
    // throw an error if the file is unable to be opened
    if (!ifs) error("can’t open input file ", filename);
 
    while(!ifs.eof()) {
        Gate g;
        ifs >> g;
        if(ifs)
            gate_pointers.push_back(&g);
        else
            error("problem reading file");
    }
    
    return;
}
 */

int main() {
    try { // attempt the program
        if(H112 != 201401L)error("Error: incorrect std_lib_facilities_4.h version ", H112);
        
        GUI_window gui;
        
        return gui_main();
    } catch (Gate::Invalid) {
        cerr << "Invalid gate\n";
        keep_window_open();
        return 1;
    } catch (exception& e){ // catches out_of_range and runtime_error
        cerr << "error: " << e.what() << '\n';
        keep_window_open();
        return 2;
    } catch (...) { // catches everything else
        cerr << "Unknown error\n";
        keep_window_open();
        return 3;
    }
}