#ifndef CUBEBUILDTESTCUBEBUILDER_H_
#define CUBEBUILDTESTCUBEBUILDER_H_

#include <FlameSteelCore/Object.h>
#include <FlameSteelCommonTraits/SerializedModel.h>

namespace CubeArtProject {

class CubeBuilder {

public:
	shared_ptr<Object> makeCube(int gridX, int gridY, int gridZ);

private:
	shared_ptr<FSEGTSerializedModel> serializedModel;
	int dotsCount = 0;

	void putFloorAtXYZ(int x, int y, int z);
	void putCeilAtXYZ(int x, int y, int z);

	void putRightWallAtXYZ(int x, int y, int z);
	void putLeftWallAtXYZ(int x, int y, int z);

	void putBackWallAtXYZ(int x, int y, int z);
	void putFrontWallAtXYZ(int x, int y, int z);
	

	void putDotAtXYZ(float x, float y, float z, float u, float v);
	void putIndexes(int first, int second, int third);

};

};

#endif