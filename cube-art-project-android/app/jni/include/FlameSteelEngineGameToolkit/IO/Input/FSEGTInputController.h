/*
 * FSEGTInputController.h
 *
 *  Created on: Aug 7, 2016
 *      Author: demensdeum
 */

#ifndef FSEGTINPUTCONTROLLER_H_
#define FSEGTINPUTCONTROLLER_H_

#include <FlameSteelEngineGameToolkit/Data/Components/Touch/FSEGTTouch.h>
#include <FlameSteelCore/Objects.h>
#include <vector>
#include <memory>

using namespace std;
using namespace FlameSteelCore;

class FSEGTIOSystem;

class FSEGTInputController: public Object
{
public:
    FSEGTInputController();

    virtual bool isJumpKeyPressed();
    virtual bool isCrouchKeyPressed();
    
    virtual bool isLeftKeyPressed();
    virtual bool isRightKeyPressed();
    virtual bool isUpKeyPressed();
    virtual bool isDownKeyPressed();

    virtual bool isRotateLeftKeyPressed();
    virtual bool isRotateRightKeyPressed();

    virtual bool isUseKeyPressed();
    virtual bool isShootKeyPressed();
    virtual bool isExitKeyPressed();

    virtual void pollKey();
    virtual void clearKeys();

    virtual int getPointerXdiff();
    virtual int getPointerYdiff();

    shared_ptr<FSEGTIOSystem> ioSystem;
    shared_ptr<Objects> touches;

    virtual ~FSEGTInputController();

public:
    bool jumpKeyPressed = false;
    bool crouchKeyPressed = false;
    
    bool leftKeyPressed = false;
    bool rightKeyPressed = false;
    bool downKeyPressed = false;
    bool upKeyPressed = false;
    bool exitKeyPressed = false;

    bool useKeyPressed = false;
    bool shootKeyPressed = false;

    bool rotateLeftKeyPressed = false;
    bool rotateRightKeyPressed = false;

    void addTouch(shared_ptr<FSEGTTouch> touch);
    void removeTouch(shared_ptr<FSEGTTouch> touch);

    void clearTouches();

    int pointerXdiff = 0;
    int pointerYdiff = 0;
};

#endif /* FSEGTINPUTCONTROLLER_H_ */
