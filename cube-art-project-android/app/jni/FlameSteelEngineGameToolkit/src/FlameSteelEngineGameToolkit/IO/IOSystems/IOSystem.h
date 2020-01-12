#ifndef FLAMESTEELENGINEGAMETOOLKITIOSYSTEM_H_
#define FLAMESTEELENGINEGAMETOOLKITIOSYSTEM_H_

#include <memory>
#include <FlameSteelCommonTraits/Screenshot.h>
#include <FlameSteelEngineGameToolkit/IO/Window/Window.h>

using namespace std;
using namespace FlameSteelEngine::GameToolkit;

namespace FlameSteelEngine {
namespace GameToolkit {

class IOSystem {

public:
    shared_ptr<IOSystem> initialize();
    shared_ptr<Window> getWindow();

private:
    shared_ptr<Window> window;

};
};
};
#endif