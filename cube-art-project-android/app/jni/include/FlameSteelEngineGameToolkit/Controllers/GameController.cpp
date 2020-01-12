/*
 * Controller.cpp
 *
 *  Created on: Jul 27, 2016
 *      Author: demensdeum
 */

#include "GameController.h"
#include <FlameSteelCore/Object.h>

#include <iostream>

using namespace std;

GameController::GameController()
{

    gameController = nullptr;
    controllerMessage = shared_ptr<Message>();
    listener = nullptr;
}

void GameController::beforeStart()
{

    if (ioSystem.get() == nullptr)
    {

        //cout << "Controller: cannot get ioSystem on controller switching. Is it even initialized? Exit";

        exit(1);

    }

    if (ioSystem->renderer.get() == nullptr)
    {

        //cout << "Controller: cannot get ioSystem *Renderer* on controller switching. Is it even initialized? Exit";

        exit(1);

    }

    renderer = ioSystem->renderer;
}

void GameController::step()
{

}

void GameController::beforeStop()
{

}

void GameController::receivedActionFromSender(int, Object *)
{

}

void GameController::controllerDidFinish(Controller *controller, shared_ptr<string> message)
{

    throw logic_error("unhandled empty controller did finish notify");

}

void GameController::notifyListenerAboutControllerDidFinish(GameController *gameController, shared_ptr<string> message)
{
    if (listener)
    {
        listener->controllerDidFinish(gameController, message);
    }
}

void GameController::setGameController(MainGameController* gameController)
{
    this->gameController = gameController;
}

void GameController::setControllerMessage(shared_ptr<Message> controllerMessage)
{
    this->controllerMessage = controllerMessage;
}

void GameController::clearMessage()
{
    this->controllerMessage = nullptr;
}

shared_ptr<Message> GameController::getControllerMessage()
{
    return this->controllerMessage;
}

MainGameController* GameController::getGameController()
{
    return this->gameController;
}

shared_ptr <FSEGTGameData> GameController::getGameData()
{
    return this->gameData;
}

void GameController::setGameData(shared_ptr<FSEGTGameData> gameData)
{
    this->gameData = gameData;
}

void GameController::handleControllerMessage()
{

}

void GameController::clearControllerMessage()
{
    this->controllerMessage = shared_ptr<Message>();
}

void GameController::setIOSystem(shared_ptr<FSEGTIOSystem> ioSystem)
{
    this->ioSystem = ioSystem;
    this->renderer = ioSystem->renderer;
}

GameController::~GameController()
{
    // TODO Auto-generated destructor stub
}