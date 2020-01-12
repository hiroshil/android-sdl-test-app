#ifndef FLAMESTEELENGINEGAMETOOLKITFSGL_WINDOW_H_
#define FLAMESTEELENGINEGAMETOOLKITFSGL_WINDOW_H_

#include <SDL2/SDL.h>

namespace FlameSteelEngine {
namespace GameToolkit {
namespace FSGLFrontend {

class Window {

public:
    bool getInitialized();
    SDL_Window *window = nullptr;

};
};
};
};

#endif