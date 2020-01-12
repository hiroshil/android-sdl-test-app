#include "Window.h"
#include <iostream>

using namespace std;

using namespace FlameSteelEngine::GameToolkit;

bool Window::getInitialized() {

    cout << "FlameSteelEngine::GameToolkit getInitialized() [INCORRECT]" << endl;

    return initialized;
};