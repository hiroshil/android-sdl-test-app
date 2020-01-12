#ifndef FLAMESTEELENGINEGAMETOOLKITFSGL_IOSYSTEM_H_
#define FLAMESTEELENGINEGAMETOOLKITFSGL_IOSYSTEM_H_

#include <memory>
#include <FlameSteelCommonTraits/Screenshot.h>
#include <FlameSteelEngineGameToolkitFSGL/IO/Window/Window.h>
#include <FlameSteelEngineGameToolkitFSGL/FSEGTIOFSGLSystem.h>


using namespace FSGL;
using namespace std;
using namespace FlameSteelEngine::GameToolkit::FSGLFrontend;

namespace FlameSteelEngine {
namespace GameToolkit {
namespace FSGLFrontend {

class IOSystem {

public:
    void initialize();
    shared_ptr<Window> getWindow();
    shared_ptr<FSEGTIOFSGLSystem> getFSGLIOSystem();
    shared_ptr<Screenshot> takeScreenshot();

private:
    shared_ptr<Window> window;
    shared_ptr<FSEGTIOFSGLSystem> ioSystem;

};

};
};
};
#endif