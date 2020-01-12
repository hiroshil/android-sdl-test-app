#ifndef DEATHMASKGAMESKYBOXCONTROLLER_H_
#define DEATHMASKGAMESKYBOXCONTROLLER_H_

#include <memory>
#include <FlameSteelCore/Object.h>
#include <FlameSteelEngineGameToolkit/Utils/FSEGTUtils.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Vector/FSEGTVector.h>

using namespace std;
using namespace FlameSteelCore;

namespace FlameSteelEngine
{
namespace GameToolkit
{

class SkyboxController;

class SkyboxControllerDelegate
{

public:
    virtual void skyboxControllerDidUpdateSkybox(shared_ptr<SkyboxController> skyboxController, shared_ptr<Object> skybox) = 0;

};

class SkyboxController: public enable_shared_from_this<SkyboxController>
{

public:
    SkyboxController(shared_ptr<Object> viewer, shared_ptr<Object> skybox, weak_ptr<SkyboxControllerDelegate> delegate);
    void step();

    weak_ptr<SkyboxControllerDelegate> delegate;

private:
    shared_ptr<Object> skybox;

    shared_ptr<FSEGTVector> viewerPosition;
    shared_ptr<FSEGTVector> skyboxPosition;

};
};
};

#endif