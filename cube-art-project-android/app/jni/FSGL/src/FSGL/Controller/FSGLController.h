/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEOGLController.h
 * Author: demensdeum
 *
 * Created on July 8, 2017, 10:37 AM
 */

#ifndef FSEOGLCONTROLLER_H
#define FSEOGLCONTROLLER_H

#include <FlameSteelCommonTraits/Screenshot.h>
#include <FlameSteelCommonTraits/IOSystemParams.h>
#include <FSGL/Data/Model/FSGLModel.h>
#include <FSGL/Data/Camera/FSGLCamera.h>
#include <FSGL/Core/FSGLCore.h>
#include <memory>

using namespace std;

class FSGLController
{

public:
    FSGLController();
    FSGLController(const FSGLController& orig);
    virtual ~FSGLController();

    void preInitialize();
    void fillParams(shared_ptr<IOSystemParams> params);
    SDL_Window* initializeWindow(shared_ptr<IOSystemParams> params);

    void addObject(shared_ptr<FSGLObject> object);

    shared_ptr<FSGLObject> getObjectWithID(string id);

    void removeAllObjects();

    void removeObject(shared_ptr<FSGLObject> object);

    void render();

    void stop();

    void setCameraX(float x);
    void setCameraY(float y);
    void setCameraZ(float z);

    void setCameraRotationX(float x);
    void setCameraRotationY(float y);
    void setCameraRotationZ(float z);

    shared_ptr<Screenshot> takeScreenshot();

private:

	float testCameraRotation = 0;

    unique_ptr<FSGLCore> core;
};

#endif /* FSEOGLCONTROLLER_H */

