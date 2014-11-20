// TT_window.h

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace Graph_lib;

class TT_window : Graph_lib::Window{
    Vector_ref<Out_box> columns;
public:
    TT_window(int w = 640, int h = 480);

    void add_column(Gate);
};