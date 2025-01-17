/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEOGLController.cpp
 * Author: demensdeum
 *
 * Created on July 8, 2017, 10:37 AM
 */

#include "FSGLController.h"

#include <iostream>
#include <FSGL/Data/ResourcesLoader/FSGLResourceLoader.h>

FSGLController::FSGLController()
{

    core = make_unique<FSGLCore>();

}

FSGLController::FSGLController(const FSGLController& )
{
}

void FSGLController::preInitialize()
{
    core->preInitialize();
}

void FSGLController::fillParams(shared_ptr<IOSystemParams> params)
{
    core->fillParams(params);
}

SDL_Window* FSGLController::initializeWindow(shared_ptr<IOSystemParams> params)
{
    return core->initializeWindow(params);
}

void FSGLController::addObject(shared_ptr<FSGLObject> object)
{

    //cout << "core add object" << endl;

    core->addObject(object);
}

void FSGLController::removeObject(shared_ptr<FSGLObject> object)
{

    core->removeObject(object);

}

void FSGLController::render()
{

    core->render();

}

void FSGLController::stop()
{

    core->stop();

}

void FSGLController::removeAllObjects()
{

    core->removeAllObjects();

}

shared_ptr<FSGLObject> FSGLController::getObjectWithID(string id)
{

    return core->getObjectWithID(id);

}

void FSGLController::setCameraX(float x)
{

    core->camera()->positionVector->x = x;

}

void FSGLController::setCameraY(float y)
{

    core->camera()->positionVector->y = y;
}

void FSGLController::setCameraZ(float z)
{

    core->camera()->positionVector->z = z;

}

void FSGLController::setCameraRotationX(float x)
{

    core->camera()->rotationVector->x = x;

}

void FSGLController::setCameraRotationY(float y)
{

    core->camera()->rotationVector->y = y;

}

void FSGLController::setCameraRotationZ(float z)
{

    core->camera()->rotationVector->z = z;

}

shared_ptr<Screenshot> FSGLController::takeScreenshot() {
    return core->takeScreenshot();
}

FSGLController::~FSGLController()
{
}
