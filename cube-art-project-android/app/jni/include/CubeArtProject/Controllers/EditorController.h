#ifndef CUBEARTPROJECTEDITORCONTROLLER_H_
#define CUBEARTPROJECTEDITORCONTROLLER_H_

#include <memory>
#include <CubeArtProject/Models/Field3D.h>
#include <FlameSteelEngineGameToolkit/Controllers/GameController.h>
#include <CubeArtProject/Utils/FreeCameraControlsController/FreeCameraControlsController.h>

using namespace std;

namespace CubeArtProject {

class EditorController: public GameController, public enable_shared_from_this<EditorController>, public FreeCameraControlsControllerDelegate {

public:
	virtual void step();
	virtual void freeCameraControlsControllerDidFinish(shared_ptr<FreeCameraControlsController> freeCameraControlsController);

private:
	void removeOrAddCubeAt(int x, int y, int z);

	NotNull<Object> cursorCube;

	shared_ptr<Field3D> field3D = make_shared<Field3D>();
	NotNull<FreeCameraControlsController> freeCameraControls;
	NotNull<Object> camera;
	NotNull<FreeCameraControlsController> freeCameraControlsController;
	NotNull<InputController> inputController;

	bool isInitialized = false;

};
};


#endif