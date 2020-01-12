#include <iostream>
#include <memory>
#include <CubeArtProject/CubeArtProject.h>
#include <FlameSteelCommonTraits/Path.h>
#include <FlameSteelCommonTraits/Color.h>

using namespace std;
using namespace CubeArtProject;
using namespace FlameSteelCommonTraits;

int main(int argc, char* args[]) {

	try
	{
        auto testName = string("Cube build remove test");

        cout << "FSGL_OBJECT_ID: " << FSGL_OBJECT_ID << endl;

        auto controller = make_shared<CubeArtProject::MainGameController>();
        controller->start();
        auto window = controller->getWindow();

        if (window.get() == nullptr) {
            cout << testName << " failed - window is not initialized - error 1" << endl;
            return 1;
        }

        if (window->getInitialized() != true) {
            cout << testName << " failed - window is not initialized - error 2" << endl;
            return 2;
        }

	controller->switchToEditorState();

	auto inputController = controller->inputController;

	if (inputController.get() == nullptr) {
		cout << testName << " failed - input controller is null - error 4" << endl;
		return 4;
	}

	controller->startGameLoop();

    //while (true) {
	//for (int i = 0; i < 2000; i++) {
		//controller->doStep();
	//}

        cout << testName << " succeded" << endl;

        return 0;

    }
    catch (const std::exception &exc)
    {
        cout << exc.what() << endl;
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception." << std::endl;
    }

    return 1;
} 
