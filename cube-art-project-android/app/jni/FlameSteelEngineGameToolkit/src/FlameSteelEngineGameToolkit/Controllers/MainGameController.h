/*
 * MainGameController.h
 *
 *  Created on: Jul 27, 2016
 *      Author: demensdeum
 */

#ifndef FSEGTGAMECONTROLLER_H_
#define FSEGTGAMECONTROLLER_H_

#include <memory>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <FlameSteelCore/Message.h>
#include <FlameSteelCore/ResourcesLoader.h>
#include <FlameSteelCore/ResourcesManager.h>
#include <FlameSteelEngineGameToolkit/Data/FSEGTGameData.h>
#include <FlameSteelEngineGameToolkit/Controllers/GameController.h>

using namespace std;

namespace FlameSteelEngine
{
namespace GameToolkit
{

class MainGameController : public GameController, public enable_shared_from_this<MainGameController>
{
public:
    MainGameController();
    virtual ~MainGameController();

    void setControllerForState(shared_ptr<GameController> controller, int state);

    void setGameControllerMessage(shared_ptr<Message> message);
    virtual void step();

    void gameLoop();
    void initializeGameFromState(int state);

    void setIOSystem(shared_ptr<FSEGTIOSystem> ioSystem);
    void switchToState(int state);

	void startGameLoop();

protected:
    shared_ptr<ResourcesLoader> resourcesLoader;
    shared_ptr<ResourcesManager> resourcesManager;

    int state;

    void setIsRunning(bool isRunning);
    virtual void handleGameControllerMessage(shared_ptr<Message> message);

private:
    map<int, shared_ptr<GameController> > stateToControllerMap;
    shared_ptr<Message> gameControllerMessage;

    shared_ptr<GameController> currentController;
    void setCurrentController(shared_ptr<GameController> newCurrentController);

    void pollGameControllerMessage();
    bool isRunning;
    bool printedSelf;

    std::chrono::system_clock::time_point previousFrameTime;

};


}
}

#ifdef __EMSCRIPTEN__

// oh god I don't like javascript for some ugly decisions like those

static MainGameController *GLOBAL_fsegt_emscripten_gameController;
void GLOBAL_fsegt_emscripten_gameLoop();
#endif

#endif /* FSEGTGAMECONTROLLER_H_ */
