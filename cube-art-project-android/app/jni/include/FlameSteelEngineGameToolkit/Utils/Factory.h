#ifndef FLAMESTEELENGINEGAMETOOLKITFACTORY_H_
#define FLAMESTEELENGINEGAMETOOLKITFACTORY_H_

#include <memory>
#include <FlameSteelCore/Object.h>
#include <FlameSteelCore/SharedNotNullPointer.h>
#include <FlameSteelCommonTraits/SerializedModel.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Vector/FSEGTVector.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Float/FloatComponent.h>
#include <FlameSteelEngineGameToolkit/Data/Components/SurfaceMaterial/SurfaceMaterial.h>

using namespace std;
using namespace FlameSteelCore;
using namespace FlameSteelCore::Utils::Shortcuts;

namespace FlameSteelEngine {
namespace GameToolkit {

class Factory {

public:
	static shared_ptr<FSEGTSerializedModel> makeSerializedModel();
	static shared_ptr<SurfaceMaterial> makeSurfaceMaterial(int width, int height);
	static shared_ptr<FSEGTVector> makePosition(int x, int y, int z);
	static shared_ptr<FSEGTVector> makeRotation(float rotationX, float rotationY, float rotationZ);
	static shared_ptr <FSEGTVector> makeScale(float width, float height, float depth);
	static shared_ptr<FloatComponent> makeBrightness(float factor);
	static NotNull<Object> makeObject(
		shared_ptr<string> classIdentifier,
		shared_ptr<string> instanceIdentifier,
		float x,
		float y,
		float z,
		float scaleX,
		float scaleY,
		float scaleZ,
		float rotationX,
		float rotationY,
		float rotationZ
	);
};

};
};


#endif