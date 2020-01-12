#ifndef FSEGTSTICKCONTROLLER_H_
#define FSEGTSTICKCONTROLLER_H_

#include <FlameSteelEngineGameToolkit/Data/Components/Stick/FSEGTStick.h>
#include <FlameSteelEngineGameToolkit/IO/Input/FSEGTInputController.h>
#include <memory>

using namespace std;

class StickController
{

public:
    StickController(shared_ptr<FSEGTInputController> inputController);

    shared_ptr<Objects> sticks;

    void step();

    shared_ptr<FSEGTStick> moveStick;
    shared_ptr<FSEGTStick> viewStick;

private:
    shared_ptr<FSEGTInputController> inputController;

    shared_ptr<string> viewTouchUUID;
    int viewTouchStartX = 0;
    int viewTouchStartY = 0;

    shared_ptr<string> moveTouchUUID;
    int moveTouchStartX = 0;
    int moveTouchStartY = 0;

};

#endif