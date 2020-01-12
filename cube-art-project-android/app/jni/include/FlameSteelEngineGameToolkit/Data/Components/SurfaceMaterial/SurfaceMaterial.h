#ifndef FSEGTSURFACEMATERIAL_H_
#define FSEGTSURFACEMATERIAL_H_

#include <FlameSteelCore/Object.h>
#include <SDL2/SDL.h>
#include <FlameSteelCommonTraits/Material.h>

using namespace FlameSteelCore;

namespace FlameSteelEngine
{
namespace GameToolkit
{

class SurfaceMaterial: public Object
{

public:
    SurfaceMaterial(shared_ptr<FSGLMaterial> material);
    SurfaceMaterial(int width, int height);

    shared_ptr<FSGLMaterial> material;

    ~SurfaceMaterial();

};

};
};

#endif
