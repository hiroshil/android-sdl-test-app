#include "IOSystem.h"
#include <iostream>
#include <FlameSteelCommonTraits/IOSystemParams.h>

using namespace std;

using namespace FlameSteelEngine::GameToolkit::FSGLFrontend;

void IOSystem::initialize() {

    cout << "IOSystem::initialize()" << endl;

    ioSystem = make_shared<FSEGTIOFSGLSystem>();

    auto ioSystemParams = make_shared<IOSystemParams>();

    ioSystemParams->width = 1024;
    ioSystemParams->height = 576;
    ioSystemParams->windowed = true;
    ioSystemParams->title = make_shared<string>("FlameSteelEngineGameToolkitFSGL");

    ioSystem->preInitialize();
    ioSystem->initialize(ioSystemParams);

    window = make_shared<Window>();
    window->window = ioSystem->window;

};

shared_ptr<FSEGTIOFSGLSystem> IOSystem::getFSGLIOSystem() {
    return ioSystem;
};

shared_ptr<Window> IOSystem::getWindow() {
    return window;
};

shared_ptr<Screenshot> IOSystem::takeScreenshot() {
    return ioSystem->takeScreenshot();
}