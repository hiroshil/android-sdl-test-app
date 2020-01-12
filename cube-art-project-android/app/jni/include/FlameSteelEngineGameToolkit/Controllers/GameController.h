/*
 * Controller.h
 *
 *  Created on: Jul 27, 2016
 *      Author: demensdeum
 */

#ifndef FSEGTCONTROLLER_H_
#define FSEGTCONTROLLER_H_

namespace FlameSteelEngine
{
namespace GameToolkit
{
class MainGameController;
}
}

#include <FlameSteelEngineGameToolkit/Controllers/FSEGTObjectsContext.h>
#include <FlameSteelEngineGameToolkit/IO/Renderers/FSEGTRenderer.h>
#include <FlameSteelEngineGameToolkit/Data/FSEGTGameData.h>
#include <FlameSteelCore/Controller.h>
#include <FlameSteelCore/Message.h>
#include <memory>

using namespace std;
using namespace FlameSteelCore;
using namespace FlameSteelEngine::GameToolkit;

namespace FlameSteelEngine
{
namespace GameToolkit
{

class GameController: public Controller
{
public:
    GameController();
    virtual ~GameController();

    virtual void beforeStart();
    virtual void step();
    virtual void beforeStop();

    void setGameController(MainGameController *gameController);
    MainGameController* getGameController();

    shared_ptr<FSEGTGameData> getGameData();
    virtual void setGameData(shared_ptr<FSEGTGameData> gameData);

    void setControllerMessage(shared_ptr<Message> controllerMessage);

    void setIOSystem(shared_ptr<FSEGTIOSystem> ioSystem);

    // listener
    GameController *listener;
    virtual void controllerDidFinish(Controller *controller, shared_ptr<string> message);

    virtual void receivedActionFromSender(int action, Object *sender);

    shared_ptr<Message> getControllerMessage();
    void clearMessage();

protected:

    virtual void notifyListenerAboutControllerDidFinish(GameController *controller, shared_ptr<string> message = nullptr);

    shared_ptr<FSEGTIOSystem> ioSystem;

    shared_ptr<FSEGTRenderer> renderer;

    shared_ptr<FSEGTGameData> gameData;
    MainGameController* gameController;
    shared_ptr<Message> controllerMessage;

    virtual void handleControllerMessage();
    virtual void clearControllerMessage();

public:

    shared_ptr<FSEGTObjectsContext> objectsContext;

};

}
}

#endif /* FSEGTCONTROLLER_H_ */
