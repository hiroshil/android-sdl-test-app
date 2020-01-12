#ifndef FSEGTMATERIALLIBRARY_H_
#define FSEGTMATERIALLIBRARY_H_

#include <map>
#include <memory>
#include <FlameSteelCommonTraits/Material.h>

using namespace std;

class MaterialLibrary
{

public:
    void setMaterialForPath(shared_ptr<FSGLMaterial> material, shared_ptr<string> path);

    shared_ptr<FSGLMaterial> materialForPath(shared_ptr<string> path);
    void clear();

private:
    map<string, shared_ptr<FSGLMaterial>> pathMaterialMap;

};

#endif
