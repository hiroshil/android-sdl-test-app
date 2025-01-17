/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLResourceLoader.h
 * Author: demensdeum
 *
 * Created on July 9, 2017, 10:16 AM
 */

#ifndef FSGLRESOURCELOADER_H
#define FSGLRESOURCELOADER_H

#include "../Resource/FSGLResource.h"
#include <FSGL/Data/MaterialLibrary/MaterialLibrary.h>

#include <string>
#include <memory>

using namespace std;

class FSEGTSerializedModel;
class FSGLModel;

class FSGLResourceLoader
{

public:
    FSGLResourceLoader();
    FSGLResourceLoader(const FSGLResourceLoader& orig);
    virtual ~FSGLResourceLoader();

    static shared_ptr<FSGLResource> loadResource(shared_ptr<string> resourcePath, shared_ptr<MaterialLibrary> materialLibrary);
    static shared_ptr<FSGLModel> deserializeModel(shared_ptr<FSEGTSerializedModel> serializedModel, shared_ptr<MaterialLibrary> materialLibrary);

private:

};

#endif /* FSGLRESOURCELOADER_H */

