#ifndef CUBEARTPROJECTFREECAMERACONTROLSCONTROLLERDELEGATE_H_
#define CUBEARTPROJECTFREECAMERACONTROLSCONTROLLERDELEGATE_H_\

#include <memory>

using namespace std;

namespace CubeArtProject {

class FreeCameraControlsController;

class FreeCameraControlsControllerDelegate {
public:
	virtual void freeCameraControlsControllerDidFinish(shared_ptr<FreeCameraControlsController> freeCameraControlsController) = 0;
};

};

#endif