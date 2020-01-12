#include "SurfaceMaterial.h"
#include <iostream>

using namespace std;

using namespace FlameSteelEngine::GameToolkit;

SurfaceMaterial::SurfaceMaterial(shared_ptr<FSGLMaterial> material)
{

    this->material = material;

}

SurfaceMaterial::SurfaceMaterial(int width, int height)
{

    setInstanceIdentifier(make_shared<string>("Surface Material"));
    setClassIdentifier(make_shared<string>("Surface Material"));

    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    auto surface = SDL_CreateRGBSurface(0, width, height, 24,
                                        rmask, gmask, bmask, amask);

    if (surface == nullptr)
    {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }

    SDL_PixelFormat *pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface *resultSurface = SDL_ConvertSurface(surface, pixelFormat, 0);
    SDL_FreeSurface(surface);
    SDL_FreeFormat(pixelFormat);

    material = make_shared<FSGLMaterial>(resultSurface);
    material->surface = resultSurface;

}

SurfaceMaterial::~SurfaceMaterial()
{

    //cout << "Surface Materal destructed" << endl;

}
