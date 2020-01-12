#include "Field3D.h"
#include <sstream>

using namespace std;
using namespace CubeArtProject;

shared_ptr<Object> Field3D::cubeAtXYZ(int x, int y, int z) {

	auto key = xyzKey(x, y, z);

	if (xyzMap.find(key) == xyzMap.end()) {
		return shared_ptr<Object>();
	}

	return xyzMap[key];

};

void Field3D::removeCubeAtXYZ(int x, int y, int z) {
	auto key = xyzKey(x, y, z);
	xyzMap.erase(key);	
};

void Field3D::addCubeAtXYZ(shared_ptr<Object> cube, int x, int y, int z) {
	auto key = xyzKey(x, y, z);
	xyzMap[key] = cube;
};

string Field3D::xyzKey(int x, int y, int z) {
	ostringstream stringStream;
	stringStream << x << ";" << y << ";" << z;
	string key = stringStream.str();
	return key;
}