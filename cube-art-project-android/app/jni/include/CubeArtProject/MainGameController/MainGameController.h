#ifndef CUBEARTPROJECTMAINGAMECONTROLLER_H_
#define CUBEARTPROJECTMAINGAMECONTROLLER_H_

#include "State.h"
#include <FlameSteelCommonTraits/Screenshot.h>
#include <CubeArtProject/Controllers/EditorController.h>
#include <FlameSteelEngineGameToolkitFSGL/IO/IOSystem.h>
#include <FlameSteelEngineGameToolkitFSGL/IO/Window/Window.h>
#include <FlameSteelEngineGameToolkit/Controllers/MainGameController.h>

using namespace FlameSteelEngine::GameToolkit;
using namespace FlameSteelEngine::GameToolkit::FSGLFrontend;
using namespace CubeArtProject::MainGameControllerState;

namespace CubeArtProject {

class MainGameController {

public:
    void start();
    shared_ptr<Window> getWindow();
    void switchToEditorState();
    shared_ptr<Screenshot> takeScreenshot();

	void startGameLoop();
	void doStep();

	shared_ptr<FSEGTInputController> inputController;

private:
    shared_ptr<IOSystem> ioSystem;
    shared_ptr<Window> window;
    State state  =  started;

    shared_ptr<FlameSteelEngine::GameToolkit::MainGameController> mainGameController;
    shared_ptr<EditorController> editorController;
};
};

#endif
