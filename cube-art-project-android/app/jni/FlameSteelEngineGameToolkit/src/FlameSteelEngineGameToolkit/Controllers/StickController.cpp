#include "StickController.h"

#include <iostream>
#include <memory>

using namespace std;

StickController::StickController(shared_ptr<FSEGTInputController> inputController)
{

    this->inputController = inputController;

}

void StickController::step()
{

    //cout << "Stick controller step" << endl;

    auto touches = inputController->touches;

    bool viewTouchFound = false;
    bool moveTouchFound = false;

    if (touches->size() > 0)
    {

        for (auto i = 0; i < touches->size(); i++)
        {

            auto touch = static_pointer_cast<FSEGTTouch>(inputController->touches->objectAtIndex(i));

            if (touch->x < 512)
            {

                moveTouchFound = true;

                if (moveTouchUUID.get() == nullptr)
                {

                    moveTouchUUID = touch->getInstanceIdentifier();

                    moveTouchStartX = touch->x;
                    moveTouchStartY = touch->y;

                    moveStick = make_shared<FSEGTStick>(touch->x, touch->y);

                }
                else if (moveTouchUUID->compare(*touch->getInstanceIdentifier()) == 0)
                {

                    auto stickX = touch->x - moveTouchStartX;
                    auto stickY = touch->y - moveTouchStartY;

                    moveStick->x = stickX;
                    moveStick->y = stickY;

                    //cout << stickX << ";" << stickY << endl;
                }

            }
            else
            {

                viewTouchFound = true;

                if (viewTouchUUID.get() == nullptr)
                {
                    viewTouchUUID = touch->getInstanceIdentifier();

                    viewTouchStartX = touch->x;
                    viewTouchStartY = touch->y;

                    viewStick = make_shared<FSEGTStick>(touch->x, touch->y);

                }
                else if (viewTouchUUID->compare(*touch->getInstanceIdentifier()) == 0)
                {

                    auto stickX = touch->x - viewTouchStartX;
                    auto stickY = touch->y - viewTouchStartY;

                    viewStick->x = stickX;
                    viewStick->y = stickY;

                    //cout << stickX << ";" << stickY << endl;
                }

            }

        }

    }

    if (!viewTouchFound && viewTouchUUID.get() != nullptr)
    {

        //cout << "Cleared view touch" << endl;
        viewTouchUUID = nullptr;
        viewStick = nullptr;

    }

    if (!moveTouchFound && moveTouchUUID.get() != nullptr)
    {

        //cout << "Cleared move touch" << endl;
        moveTouchUUID = nullptr;
        moveStick = nullptr;

    }

}