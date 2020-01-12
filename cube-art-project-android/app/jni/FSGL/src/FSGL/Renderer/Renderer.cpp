#include "Renderer.h"
#include <FSGL/Data/Camera/FSGLCamera.h>

using namespace FSGL;

Renderer::Renderer()
{
    camera = make_shared<FSGLCamera>();
}

Renderer::~Renderer()
{

}

void Renderer::preInitialize()
{

};

void Renderer::fillParams(shared_ptr<IOSystemParams> params)
{

};

SDL_Window* Renderer::initializeWindow(shared_ptr<IOSystemParams> params)
{
    return nullptr;
};