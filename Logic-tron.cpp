// Logic-tron.cpp

#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"

#include "Gate.h"

void save() {
    return;
}

void load() {
    return;
}

int main() {
    try { // attempt the program
        if(H112 != 201401L)error("Error: incorrect std_lib_facilities_4.h version ", H112);
        
        Vector_ref<Gate> gates;
        
        return 0;
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