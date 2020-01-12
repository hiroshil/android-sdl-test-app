#ifndef FSEGTFREECAMERACONTROLLERDEFINED
#define FSEGTFREECAMERACONTROLLERDEFINED

#include <memory>
#include <FlameSteelEngineGameToolkit/IO/Input/FSEGTInputController.h>
#include <FlameSteelCore/Object.h>
#include <FlameSteelCore/Controller.h>

class FSEGTFreeCameraControllerDelegate;

using namespace std;
using namespace FlameSteelCore;

class FSEGTFreeCameraController: public Controller, public enable_shared_from_this<FSEGTFreeCameraController>
{

public:
    FSEGTFreeCameraController(shared_ptr<FSEGTInputController> inputController, shared_ptr<Object> camera);

    void step();

    weak_ptr<FSEGTFreeCameraControllerDelegate> delegate;

private:
    shared_ptr<FSEGTInputController> inputController;
    shared_ptr<Object> camera;
};

#endif