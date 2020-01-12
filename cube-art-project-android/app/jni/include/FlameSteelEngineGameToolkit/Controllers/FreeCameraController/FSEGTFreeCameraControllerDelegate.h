#ifndef FSEGTFREECAMERACONTROLLERDELEGATEDEFINED
#define FSEGTFREECAMERACONTROLLERDELEGATEDEFINED

#include <memory>

using namespace std;

namespace FlameSteelCore
{
class Object;
};

using namespace FlameSteelCore;

class FSEGTFreeCameraController;

class FSEGTFreeCameraControllerDelegate
{

public:
    virtual void freeCameraControllerDidUpdateCamera(shared_ptr<FSEGTFreeCameraController> freeCameraController, shared_ptr<Object> camera);

};

#endif