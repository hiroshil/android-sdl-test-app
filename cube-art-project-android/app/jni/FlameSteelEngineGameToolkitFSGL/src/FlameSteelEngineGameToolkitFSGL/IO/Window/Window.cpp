#include "Window.h"
#include <iostream>

using namespace std;
using namespace FlameSteelEngine::GameToolkit::FSGLFrontend;

bool Window::getInitialized() {

    cout << "FlameSteelEngineGameToolkitFSGL window getInitialized" << endl;

    bool initialized = window != nullptr;
    return initialized;
};
