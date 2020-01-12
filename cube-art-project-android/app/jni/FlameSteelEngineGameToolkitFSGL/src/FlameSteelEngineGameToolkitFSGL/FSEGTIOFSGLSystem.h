/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEGTIOFSGLSystem.h
 * Author: demensdeum
 *
 * Created on August 5, 2017, 6:25 PM
 */

#ifndef FSEGTIOFSGLSYSTEM_H
#define FSEGTIOFSGLSYSTEM_H

#include <SDL2/SDL.h>
#include <FlameSteelCommonTraits/Screenshot.h>
#include <FlameSteelCommonTraits/IOSystemParams.h>
#include <FlameSteelEngineGameToolkitFSGL/Renderers/FSEGTIOFSGLSystemRenderer.h>
#include <FlameSteelEngineGameToolkit/IO/IOSystems/FSEGTIOSystem.h>
#include <memory>

class FSEGTIOFSGLSystem: public FSEGTIOSystem {
public:
    FSEGTIOFSGLSystem();
    FSEGTIOFSGLSystem(const FSEGTIOFSGLSystem& orig);
    virtual ~FSEGTIOFSGLSystem();

    virtual void preInitialize();
    virtual void fillParams(shared_ptr<IOSystemParams> params);
    virtual void initialize(shared_ptr<IOSystemParams> params);

    virtual void objectsContextObjectAdded(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);
    virtual void objectsContextObjectUpdate(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);
    virtual void objectsContextAllObjectsRemoved(shared_ptr<FSEGTObjectsContext> context);
    virtual void objectsContextObjectRemoved(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);

    shared_ptr<Screenshot> takeScreenshot();

    shared_ptr<MaterialLibrary> materialLibrary = make_shared<MaterialLibrary>();

    SDL_Window *window;

private:
    shared_ptr<FSEGTIOFSGLSystemRenderer> fsglRenderer;
};

#endif /* FSEGTIOFSGLSYSTEM_H */

