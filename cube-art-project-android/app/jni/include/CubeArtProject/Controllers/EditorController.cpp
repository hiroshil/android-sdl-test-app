#include "EditorController.h"
#include <iostream>
#include <FlameSteelCore/FSCUtils.h>
#include <CubeArtProject/Utils/CubeBuilder.h>
#include <unistd.h>
#include <FlameSteelEngineGameToolkit/Utils/Factory.h>
#include <FlameSteelEngineGameToolkit/Utils/FSEGTUtils.h>


using namespace CubeArtProject;
using namespace FlameSteelCore::Utils;

void EditorController::step() {

	if (isInitialized == false) {
		camera = Factory::makeObject(
			make_shared<string>("camera"),
			make_shared<string>("camera"),
			0,0,0,
			1,1,1,
			0,0,0
		);
		objectsContext->addObject(camera.sharedPointer());

		freeCameraControlsController = make<FreeCameraControlsController>(camera, toNotNull(ioSystem->inputController), shared_from_this());
		inputController = toNotNull(ioSystem->inputController);

		auto cubeBuilder = make<CubeBuilder>();
		cursorCube = toNotNull(cubeBuilder->makeCube(0, 0, 0));

		objectsContext->addObject(cursorCube.sharedPointer());

		isInitialized = true;
	}

	auto cubeCursorPosition = freeCameraControlsController->cubeCursorPositionVector();
	auto cubePositionVector = FSEGTUtils::getObjectPosition(cursorCube.sharedPointer());
	cubePositionVector->x = cubeCursorPosition->x;
	cubePositionVector->y = cubeCursorPosition->y;
	cubePositionVector->z = cubeCursorPosition->z;
	objectsContext->updateObject(cursorCube.sharedPointer());

    //cout << "EditorController step" << endl;

	inputController->pollKey();

	if (ioSystem->inputController.get() == nullptr) {
		throwRuntimeException(string("ioSystem->inputController.get() == nullptr"));
	}

	if (ioSystem->inputController->useKeyPressed == true) {
		cout << "Use key pressed" << endl;

		removeOrAddCubeAt(cubePositionVector->x, cubePositionVector->y, cubePositionVector->z);

		ioSystem->inputController->useKeyPressed = false;
	}

	if (renderer.get() == nullptr) {
		throwRuntimeException(string("renderer == nullptr"));
	}
    renderer->render(gameData);

	freeCameraControlsController->step();
};

void EditorController::freeCameraControlsControllerDidFinish(shared_ptr<FreeCameraControlsController> freeCameraControlsController) {
	objectsContext->updateObject(camera.sharedPointer());
};

void EditorController::removeOrAddCubeAt(int x, int y, int z) {

	cout << "removeOrAddCubeAtFront()" << endl;

	if (objectsContext.get() == nullptr) {
		throwRuntimeException(string("objectsContext is null"));
	}

	cout << "EditorController::removeOrAddCubeAtFront()" << endl; 

	auto cube = field3D->cubeAtXYZ(x, y, z);

	if (cube.get() != nullptr) {
		field3D->removeCubeAtXYZ(x, y, z);
		objectsContext->removeObject(cube);
		cout << "objectsContext->removeObject(cube);" << endl;
	}
	else {
		auto cubeBuilder = make_shared<CubeBuilder>();
		auto cube = cubeBuilder->makeCube(0, 0, 0);
		field3D->addCubeAtXYZ(cube, x, y, z);

		FSEGTUtils::getObjectPosition(cube)->x = x;
		FSEGTUtils::getObjectPosition(cube)->y = y;
		FSEGTUtils::getObjectPosition(cube)->z = z;

		objectsContext->addObject(cube);
		cout << "objectsContext->addObject(cube);" << endl;
	}	
};