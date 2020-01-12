/*
 * FSEGTRenderer.h
 *
 *  Created on: Aug 6, 2016
 *      Author: demensdeum
 */

#ifndef FSEGTRENDERER_H_
#define FSEGTRENDERER_H_

#include <FlameSteelCommonTraits/Screenshot.h>
#include <FlameSteelCommonTraits/IOSystemParams.h>
#include <FlameSteelEngineGameToolkit/Data/FSEGTGameData.h>
#include <FlameSteelEngineGameToolkit/IO/IOSystems/FSEGTIOSystem.h>
#include <FlameSteelCore/Object.h>

#include <memory>

using namespace std;

class FSEGTRenderer : public Object, public FSEGTObjectContextDelegate
{
public:
    FSEGTRenderer();

    virtual void preInitialize();
    virtual void fillParams(shared_ptr<IOSystemParams> params);
    virtual void initializeWindow(shared_ptr<IOSystemParams> params);

    virtual void render(shared_ptr<FSEGTGameData> gameData);

    virtual void beforeStop();

    virtual void blankScreen();

    virtual void updateScreen();

    shared_ptr<FSEGTIOSystem> ioSystem;

    virtual ~FSEGTRenderer();

    virtual void objectsContextObjectAdded(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);

    virtual void addRenderID(int id);

    virtual void cleanRenderIDs();

    virtual shared_ptr<Screenshot> takeScreenshot() = 0;
};

#endif /* FSEGTRENDERER_H_ */
