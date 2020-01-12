/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLObject.h
 * Author: demensdeum
 *
 * Created on July 29, 2017, 11:45 AM
 */

#ifndef FSGLOBJECT_H
#define FSGLOBJECT_H

#include "../Model/FSGLModel.h"
#include "../Vector/FSGLVector.h"

#include <glm/glm.hpp>

#include "../Serializable/FSGLSerializable.h"

#include "../Matrix/FSGLMatrix.h"

#include <memory>

using namespace std;

class FSGLAnimation;

class FSGLObject
{
public:
    FSGLObject(shared_ptr<FSGLModel> model);
    FSGLObject() : FSGLObject(shared_ptr<FSGLModel>()) {};
    virtual ~FSGLObject();

    string id;

    shared_ptr<FSGLModel> model;

    shared_ptr<FSGLVector> scaleVector;
    shared_ptr<FSGLVector> rotationVector;
    shared_ptr<FSGLVector> positionVector;

    float brightness = 1.0;
    int layer = 0;

    bool overlapObject = false;

    virtual glm::mat4 matrix();

    virtual shared_ptr<string> serializeIntoString();
    virtual shared_ptr<FSGLObject> deserializeFromString(shared_ptr<string> serializedData, shared_ptr<MaterialLibrary> materialLibrary);

    virtual shared_ptr<FSGLObject> deserializeFromFile(shared_ptr<string> path);

    void updateAnimationTransformations();

    void applyAnimation(shared_ptr<string> animationName, double animationOffset);

    void postRenderUpdate();
    void playAnimationWithName(shared_ptr<string> animationName);

};

#endif /* FSGLOBJECT_H */

