#include "CubeBuilder.h"
#include <sstream>
#include <FlameSteelCore/FSCUtils.h>
#include <FlameSteelEngineGameToolkit/Utils/Factory.h>

using namespace std;
using namespace CubeArtProject;
using namespace FlameSteelCore::Utils;
using namespace FlameSteelEngine::GameToolkit;

static const float CubeBuilderSize = 2;

shared_ptr<Object> CubeBuilder::makeCube(int gridX, int gridY, int gridZ) {

	float x = gridX;
	float y = gridY;
	float z = gridZ;

	auto cube = make_shared<Object>();
	serializedModel = Factory::makeSerializedModel();
	serializedModel->append(make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh"));

	putCeilAtXYZ(x, y, z);
	putLeftWallAtXYZ(x, y, z);
	putRightWallAtXYZ(x, y, z);
	putBackWallAtXYZ(x, y, z);
	putFrontWallAtXYZ(x, y, z);
	putFloorAtXYZ(x, y, z);

	serializedModel->append(make_shared<string>("\nMaterial - Texture path = <No Path>"));

	auto keyStream = stringstream();
	keyStream << x;
	keyStream << ",";
	keyStream << y;
	keyStream << ",";
	keyStream << z;

	auto key = keyStream.str();

	cube->setClassIdentifier(make_shared<string>("Cube"));
	cube->setInstanceIdentifier(make_shared<string>(key));

	cube->addComponent(serializedModel);

	auto surfaceMaterial = Factory::makeSurfaceMaterial(64, 64);
	auto surface = surfaceMaterial->material->surface;
	if (surface == nullptr) {
		throwRuntimeException(string("Surface inside of SurfaceMaterial is nullptr"));
	}

	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));

	cube->addComponent(surfaceMaterial);

	auto position = Factory::makePosition(x, y, z);
	cube->addComponent(position);

	auto rotation = Factory::makeRotation(0, 0, 0);
	cube->addComponent(rotation);

	auto scale = Factory::makeScale(1,1,1);
	cube->addComponent(scale);

	auto brightness = Factory::makeBrightness(1.0);
	cube->addComponent(brightness);

	return cube;

};

void CubeBuilder::putLeftWallAtXYZ(int gridX, int gridY, int gridZ) {

	if (serializedModel.get() == nullptr) {
		throwRuntimeException(string("Serialized model nil"));
	}
	
	auto dotsCount = serializedModel->dotsCount;

	float x = gridX;
	float y = gridY;
	float z = gridZ;

	float size = CubeBuilderSize;

	putDotAtXYZ(x, y, z, 0, 1);
	putDotAtXYZ(x, y + size, z, 0, 0);
	putDotAtXYZ(x, y + size, z + size, 1, 0);
	putDotAtXYZ(x, y, z + size, 1, 1);

	putIndexes(dotsCount + 2, dotsCount, dotsCount + 3);
	putIndexes(dotsCount, dotsCount + 2, dotsCount + 1);	

}

void CubeBuilder::putRightWallAtXYZ(int gridX, int gridY, int gridZ) {

	if (serializedModel.get() == nullptr) {
		throwRuntimeException(string("Serialized model nil"));
	}
	
	auto dotsCount = serializedModel->dotsCount;

	float x = gridX;
	float y = gridY;
	float z = gridZ;

	float size = CubeBuilderSize;

	putDotAtXYZ(x + size, y + size, z, 0, 1);
	putDotAtXYZ(x + size, y, z, 0, 0);
	putDotAtXYZ(x + size, y, z + size, 1, 0);
	putDotAtXYZ(x + size, y + size, z + size, 1, 1);

	putIndexes(dotsCount + 2, dotsCount, dotsCount + 3);
	putIndexes(dotsCount, dotsCount + 2, dotsCount + 1);	

}

void CubeBuilder::putFloorAtXYZ(int gridX, int gridY, int gridZ) {

	if (serializedModel.get() == nullptr) {
		throwRuntimeException(string("Serialized model nil"));
	}
	
	auto dotsCount = serializedModel->dotsCount;

	float x = gridX;
	float y = gridY;
	float z = gridZ;

	float size = CubeBuilderSize;

	putDotAtXYZ(x, y, z, 0, 1);
	putDotAtXYZ(x + size, y, z, 0, 0);
	putDotAtXYZ(x + size, y, z + size, 1, 0);
	putDotAtXYZ(x, y, z + size, 1, 1);

	putIndexes(dotsCount + 1, dotsCount + 2, dotsCount);
	putIndexes(dotsCount + 3, dotsCount, dotsCount + 2);
};

void CubeBuilder::putCeilAtXYZ(int gridX, int gridY, int gridZ) {

	if (serializedModel.get() == nullptr) {
		throwRuntimeException(string("Serialized model nil"));
	}
	
	auto dotsCount = serializedModel->dotsCount;

	float x = gridX;
	float y = gridY;
	float z = gridZ;

	float size = CubeBuilderSize;

	putDotAtXYZ(x, y + size, z, 0, 1);
	putDotAtXYZ(x + size, y + size, z, 0, 0);
	putDotAtXYZ(x + size, y + size, z + size, 1, 0);
	putDotAtXYZ(x, y + size, z + size, 1, 1);

	putIndexes(dotsCount + 2, dotsCount, dotsCount + 3);
	putIndexes(dotsCount, dotsCount + 2, dotsCount + 1);
};

void CubeBuilder::putBackWallAtXYZ(int gridX, int gridY, int gridZ) {

	if (serializedModel.get() == nullptr) {
		throwRuntimeException(string("Serialized model nil"));
	}
	
	auto dotsCount = serializedModel->dotsCount;

	float x = gridX;
	float y = gridY;
	float z = gridZ;

	float size = CubeBuilderSize;

	putDotAtXYZ(x, y + size, z + size, 0, 1);
	putDotAtXYZ(x + size, y + size, z + size, 0, 0);
	putDotAtXYZ(x + size, y, z + size, 1, 0);
	putDotAtXYZ(x, y, z + size, 1, 1);

	putIndexes(dotsCount + 2, dotsCount, dotsCount + 3);
	putIndexes(dotsCount, dotsCount + 2, dotsCount + 1);

};

void CubeBuilder::putFrontWallAtXYZ(int gridX, int gridY, int gridZ) {

	if (serializedModel.get() == nullptr) {
		throwRuntimeException(string("Serialized model nil"));
	}
	
	auto dotsCount = serializedModel->dotsCount;

	float x = gridX;
	float y = gridY;
	float z = gridZ;

	float size = CubeBuilderSize;

	putDotAtXYZ(x, y, z, 0, 1);
	putDotAtXYZ(x + size, y, z, 0, 0);

	putDotAtXYZ(x + size, y +  size, z, 1, 0);
	putDotAtXYZ(x, y + size, z, 1, 1);

	putIndexes(dotsCount + 2, dotsCount, dotsCount + 3);
	putIndexes(dotsCount, dotsCount + 2, dotsCount + 1);

};

void CubeBuilder::putDotAtXYZ(float x, float y, float z, float u, float v) {
	if (serializedModel.get() == nullptr) {
		throwRuntimeException(string("Serialized model nil"));
	}

	serializedModel->append(make_shared<string>(string("\nVertex - x = ")));
	serializedModel->append(make_shared<string>(to_string(x)));

	serializedModel->append(make_shared<string>(string(", y = ")));
	serializedModel->append(make_shared<string>(to_string(y)));

	serializedModel->append(make_shared<string>(string(", z = ")));
	serializedModel->append(make_shared<string>(to_string(z)));

	serializedModel->append(make_shared<string>(string(", u = ")));
	serializedModel->append(make_shared<string>(to_string(u)));

	serializedModel->append(make_shared<string>(string(", v = ")));
	serializedModel->append(make_shared<string>(to_string(v)));

	serializedModel->dotsCount += 1;	
};

void CubeBuilder::putIndexes(int first, int second, int third) {

	if (serializedModel.get() == nullptr) {
		throwRuntimeException(string("Serialized model nil"));
	}

	auto indexesStream = stringstream();
	indexesStream << string("\nIndex = ");
	indexesStream << first;
	indexesStream << ", ";
	indexesStream << second;
	indexesStream << ", ";
	indexesStream << third;

	auto indexes = indexesStream.str();

	serializedModel->append(make_shared<string>(indexes));
};