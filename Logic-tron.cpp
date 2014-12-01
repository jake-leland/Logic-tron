// Logic-tron.cpp

#include "std_lib_facilities_4.h"

#include "Gate.h"
#include "GUI_window.h"

Vector<Gate*> gate_pointers;

int X_MAX = 1024;
int SCALE = 20;
int LABEL_SIZE = .7*SCALE;
int PADDING_TOP = 768/20;
int PADDING_SIDE = 1024/25;
int GATE_PADDING_TOP = PADDING_TOP + 2.5*SCALE;
int GATE_PADDING_SIDE = PADDING_SIDE + 2*SCALE;

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