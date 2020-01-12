#include "MainGameController.h"
#include <FlameSteelCore/FSCUtils.h>

#include <iostream>

using namespace std;
using namespace CubeArtProject;
using namespace FlameSteelCore::Utils;

void CubeArtProject::MainGameController::start() {

    cout << "MainGameController::start()" << endl;

    mainGameController = make_shared<FlameSteelEngine::GameToolkit::MainGameController>();
    editorController = make_shared<EditorController>();

    mainGameController->setControllerForState(editorController, editor);

    ioSystem = make_shared<IOSystem>();
    ioSystem->initialize();
    window = ioSystem->getWindow();

    mainGameController->setIOSystem(ioSystem->getFSGLIOSystem());
	inputController = ioSystem->getFSGLIOSystem()->inputController;

};

shared_ptr<Window> CubeArtProject::MainGameController::getWindow() {

    if (window.get() == nullptr) {
        cout << "MainGameController::getWindow() == nullptr" << endl;
    }
    else {
        cout << "MainGameController::getWindow() != nullptr" << endl;
    }

    return window;

};

void CubeArtProject::MainGameController::startGameLoop() {
	mainGameController->startGameLoop();
}

void CubeArtProject::MainGameController::switchToEditorState() {
    if (state == editor) {
        return;
    }
    state = editor;
    mainGameController->initializeGameFromState(editor);
};

void CubeArtProject::MainGameController::doStep() {
    if (mainGameController.get() != nullptr) {
        mainGameController->step();
    }
    else {
        throwRuntimeException(string("MainGameController exception - FlameSteelEngine::GameToolkit::MainGameController is null, not initialized?"));
    }
};

shared_ptr<Screenshot> CubeArtProject::MainGameController::takeScreenshot() {
    auto screenshot = ioSystem->takeScreenshot();
    return screenshot;
};
