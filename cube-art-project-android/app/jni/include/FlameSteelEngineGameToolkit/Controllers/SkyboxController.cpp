#include "SkyboxController.h"

using namespace FlameSteelEngine::GameToolkit;

SkyboxController::SkyboxController(shared_ptr<Object> viewer, shared_ptr<Object> skybox, weak_ptr<SkyboxControllerDelegate> delegate)
{

    this->skybox = skybox;
    this->delegate = delegate;

    viewerPosition = FSEGTUtils::getObjectPosition(viewer);
    skyboxPosition = FSEGTUtils::getObjectPosition(skybox);

};

void SkyboxController::step()
{

    skyboxPosition->populate(viewerPosition);
    skyboxPosition->x -= 0.5;
    skyboxPosition->y -= 0.5;
    skyboxPosition->z -= 0.5;

    auto lockedDelegate = delegate.lock();

    if (lockedDelegate.get() != nullptr)
    {

        lockedDelegate->skyboxControllerDidUpdateSkybox(shared_from_this(), skybox);

    }

};