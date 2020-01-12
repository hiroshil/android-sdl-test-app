#ifndef CUBEARTPROJECT_FIELD3D_H_
#define CUBEARTPROJECT_FIELD3D_H_

#include <memory>
#include <string>
#include <map>
#include <FlameSteelCore/Object.h>

using namespace std;

namespace CubeArtProject {

class Field3D {

public:
	void addCubeAtXYZ(shared_ptr<Object> cube, int x, int y, int z);
	void removeCubeAtXYZ(int x, int y, int z);
	shared_ptr<Object> cubeAtXYZ(int x, int y, int z);

private:
	map<string, shared_ptr<Object> > xyzMap;
	string xyzKey(int x, int y, int z);
};

};

#endif