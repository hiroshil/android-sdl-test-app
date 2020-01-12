/*
 * FSEGTInputController.cpp
 *
 *  Created on: Aug 7, 2016
 *      Author: demensdeum
 */

#include "FSEGTInputController.h"

FSEGTInputController::FSEGTInputController()
{
    this->jumpKeyPressed = false;
    this->crouchKeyPressed = false;    
    
    this->ioSystem = nullptr;
    this->leftKeyPressed = false;
    this->rightKeyPressed = false;
    this->downKeyPressed = false;
    this->upKeyPressed = false;
    this->useKeyPressed = false;

    this->rotateLeftKeyPressed = false;
    this->rotateRightKeyPressed = false;

    this->exitKeyPressed = false;
    this->shootKeyPressed = false;

    touches = make_shared<Objects>();

}

void FSEGTInputController::clearTouches()
{

    touches->removeAllObjects();

}

bool FSEGTInputController::isRotateLeftKeyPressed()
{

    return this->rotateLeftKeyPressed;

}

bool FSEGTInputController::isRotateRightKeyPressed()
{

    return this->rotateRightKeyPressed;

}

void FSEGTInputController::pollKey()
{

}

void FSEGTInputController::clearKeys()
{
    this->jumpKeyPressed = false;
    this->crouchKeyPressed = false;
    
    this->leftKeyPressed = false;
    this->rightKeyPressed = false;
    this->downKeyPressed = false;
    this->upKeyPressed = false;
    this->useKeyPressed = false;

    this->rotateLeftKeyPressed = false;
    this->rotateRightKeyPressed = false;

    this->exitKeyPressed = false;
    this->shootKeyPressed = false;
}

bool FSEGTInputController::isJumpKeyPressed() {
    return this->jumpKeyPressed;
}

bool FSEGTInputController::isCrouchKeyPressed() {
    return this->crouchKeyPressed;
}


bool FSEGTInputController::isExitKeyPressed()
{
    return this->exitKeyPressed;
}

bool FSEGTInputController::isLeftKeyPressed()
{
    return this->leftKeyPressed;
}

bool FSEGTInputController::isRightKeyPressed()
{
    return this->rightKeyPressed;
}

bool FSEGTInputController::isUpKeyPressed()
{
    return this->upKeyPressed;
}

bool FSEGTInputController::isDownKeyPressed()
{
    return this->downKeyPressed;
}

bool FSEGTInputController::isShootKeyPressed()
{
    return this->shootKeyPressed;
}

bool FSEGTInputController::isUseKeyPressed()
{
    return this->useKeyPressed;
}

int FSEGTInputController::getPointerXdiff()
{

    return pointerXdiff;
}

int FSEGTInputController::getPointerYdiff()
{

    return pointerYdiff;
}

FSEGTInputController::~FSEGTInputController()
{
    // TODO Auto-generated destructor stub
}
