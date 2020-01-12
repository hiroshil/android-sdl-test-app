/*
 * FSEGTIOSystem.h
 *
 *  Created on: Aug 21, 2016
 *      Author: demensdeum
 */

#ifndef FSEGTIOSYSTEM_H_
#define FSEGTIOSYSTEM_H_

#include <FlameSteelCore/Object.h>

#include <FlameSteelCore/ResourcesManager.h>
#include <FlameSteelCommonTraits/IOSystemParams.h>
#include <FlameSteelEngineGameToolkit/IO/Input/FSEGTInputController.h>
#include <FlameSteelEngineGameToolkit/Controllers/FSEGTObjectContextDelegate.h>

#include <memory>

using namespace std;

class FSEGTRenderer;
class FSEGTAudioPlayer;
class FSEGTInputController;

class FSEGTIOSystem: public Object,
    public FSEGTObjectContextDelegate,
    public enable_shared_from_this<FSEGTIOSystem>
{
public:
    FSEGTIOSystem();

    virtual void preInitialize();
    virtual void fillParams(shared_ptr<IOSystemParams> params = nullptr);
    virtual void initialize(shared_ptr<IOSystemParams> params = nullptr);

    virtual void clearCache();

    virtual ~FSEGTIOSystem();

    shared_ptr<ResourcesManager> resourcesManager;

    shared_ptr<IOSystemParams> params;
    shared_ptr<FSEGTRenderer> renderer;
    shared_ptr<FSEGTInputController> inputController;
    shared_ptr<FSEGTAudioPlayer> audioPlayer;

    virtual void stop();
};

#endif /* FSEGTIOSYSTEM_H_ */
