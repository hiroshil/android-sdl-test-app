/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEOGLModel.h
 * Author: demensdeum
 *
 * Created on July 8, 2017, 10:39 AM
 */

#ifndef FSEOGLMODEL_H
#define FSEOGLMODEL_H

#include <memory>

#include <FSGL/Data/Node/FSGLNode.h>
#include "../Resource/FSGLResource.h"
#include <FlameSteelCommonTraits/Material.h>
#include "../Mesh/FSGLMesh.h"
#include "../Serializable/FSGLSerializable.h"
#include "../Animation/FSGLAnimation.h"
#include <FSGL/Data/MaterialLibrary/MaterialLibrary.h>

#include <vector>

using namespace std;

class FSGLModel: public FSGLResource
{

public:
    FSGLModel();
    virtual ~FSGLModel();

    void playAnimationWithName(shared_ptr<string> animationName);

    map<string, shared_ptr<FSGLAnimation> > animations;
    vector< shared_ptr<FSGLMesh> > meshes;

    virtual shared_ptr<string> serializeIntoString();
    virtual shared_ptr<FSGLModel> deserializeFromString(shared_ptr<string> serializedData, shared_ptr<MaterialLibrary> materialLibrary);

    void postRenderUpdate();

    bool isValid();

    shared_ptr<FSGLNode> rootNode;
    shared_ptr<FSGLAnimation> currentAnimation;

private:

};

#endif /* FSEOGLMODEL_H */

