#include "Factory.h"
#include <FlameSteelCore/SharedNotNullPointer.h>
#include <FlameSteelEngineGameToolkit/Data/Components/FSEGTFactory.h>

using namespace FlameSteelEngine::GameToolkit;

shared_ptr<FSEGTSerializedModel> Factory::makeSerializedModel() {
	auto serializedModel = FSEGTFactory::makeSerializedModelComponent(make_shared<string>());
	return serializedModel;
};

shared_ptr<SurfaceMaterial> Factory::makeSurfaceMaterial(int width, int height) {
	auto surfaceMaterial = FSEGTFactory::makeSurfaceMaterialComponent(width, height);
	return surfaceMaterial;
};

shared_ptr<FSEGTVector> Factory::makePosition(int x, int y, int z) {
	auto position = FSEGTFactory::makePositionComponent(x, y, z);
	return position;
};

shared_ptr<FSEGTVector> Factory::makeRotation(float rotationX, float rotationY, float rotationZ) {
	auto rotation = FSEGTFactory::makeRotationComponent(rotationX, rotationY, rotationZ);
	return rotation;
};

shared_ptr <FSEGTVector> Factory::makeScale(float width, float height, float depth) {
	auto scale = FSEGTFactory::makeScaleComponent(width, height, depth);
	return scale;
};

shared_ptr<FloatComponent> Factory::makeBrightness(float factor) {
	auto brightness = FSEGTFactory::makeBrightnessComponent(factor);
	return brightness;
}

NotNull<Object> Factory::makeObject(
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
	) {

	auto object = FSEGTFactory::makeOnSceneObject(
			                 classIdentifier,
			                 instanceIdentifier,
			                 shared_ptr<string>(),
			                 shared_ptr<string>(),
			                 shared_ptr<string>(),
			                 x, y, z,
			                 scaleX, scaleY, scaleZ,
			                 rotationX, rotationY, rotationZ,
		                 0);

	auto notNull = toNotNull(object);

	return notNull;
};