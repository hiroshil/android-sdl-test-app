#include "FSGLCore.h"
#include <iostream>
#include <FSGL/Data/Camera/FSGLCamera.h>
#include <FSGL/Renderer/OGLNewAgeRenderer/OGLNewAgeRenderer.h>

FSGLCore::FSGLCore()
{

    renderer = make_shared<OGLNewAgeRenderer>();

}

FSGLCore::~FSGLCore()
{

}

shared_ptr<FSGLCamera> FSGLCore::camera()
{
    return renderer->camera;
}

void FSGLCore::preInitialize()
{
    renderer->preInitialize();
}

void FSGLCore::fillParams(shared_ptr<IOSystemParams> params)
{
    renderer->fillParams(params);
}

SDL_Window* FSGLCore::initializeWindow(shared_ptr<IOSystemParams> params)
{
    return renderer->initializeWindow(params);
}

void FSGLCore::addObject(shared_ptr<FSGLObject> object)
{

    if (object.get() == nullptr)
    {
        throw logic_error("Can't add null object");
    }

    auto id = object->id;

    idObjectMap[id] = object;

    renderer->addObject(object);
}

void FSGLCore::removeObject(shared_ptr<FSGLObject> object)
{

    auto id = object->id;
    idObjectMap.erase(id);

    renderer->removeObject(object);

    cout << "Remove object with ID: " << id << endl;
}

void FSGLCore::removeAllObjects()
{

    for (auto iterator : idObjectMap)
    {
        renderer->removeObject(iterator.second);
    }

    idObjectMap.clear();
}

shared_ptr<FSGLObject> FSGLCore::getObjectWithID(string id)
{
    return idObjectMap[id];
}

void FSGLCore::render()
{
    renderer->render();
}

void FSGLCore::stop()
{
    renderer->stop();
}

shared_ptr<Screenshot> FSGLCore::takeScreenshot() {
    return renderer->takeScreenshot();
}