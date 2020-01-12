#ifndef FSGL_RENDERER_H_
#define FSGL_RENDERER_H_

#include <memory>
#include <FlameSteelCommonTraits/IOSystemParams.h>
#include <FlameSteelCommonTraits/Screenshot.h>

using namespace std;
class FSGLObject;
class FSGLCamera;
class FSEGTIOGenericSystemParams;

struct SDL_Window;

namespace FSGL
{

class Renderer
{

public:
    Renderer();
    virtual ~Renderer();

    virtual void preInitialize();
    virtual void fillParams(shared_ptr<IOSystemParams> params);
    virtual SDL_Window* initializeWindow(shared_ptr<IOSystemParams> params);

    virtual void addObject(shared_ptr<FSGLObject> object) = 0;
    virtual void removeObject(shared_ptr<FSGLObject> object) = 0;

    virtual void render() = 0;

    virtual void stop() = 0;

    shared_ptr<FSGLCamera> camera;

    virtual shared_ptr<Screenshot> takeScreenshot() = 0;

    SDL_Window *window;
};
};

#endif