#include "MaterialLibrary.h"

void MaterialLibrary::setMaterialForPath(shared_ptr<FSGLMaterial> material, shared_ptr<string> path)
{
    pathMaterialMap[*path] = material;
}

shared_ptr<FSGLMaterial> MaterialLibrary::materialForPath(shared_ptr<string> path)
{

    auto key = *path;

    if (pathMaterialMap.find(key) != pathMaterialMap.end())
    {
        return pathMaterialMap[key];
    }

    return shared_ptr<FSGLMaterial>();

}

void MaterialLibrary::clear()
{

    pathMaterialMap.clear();

}
