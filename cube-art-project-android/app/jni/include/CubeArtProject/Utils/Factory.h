#ifndef CUBEARTPROJECTFACTORY_H_
#define CUBEARTPROJECTFACTORY_H_

#include <FlameSteelCommonTraits/Path.h>
#include <FlameSteelCommonTraits/Screenshot.h>

using namespace FlameSteelCommonTraits;

namespace CubeArtProject {

class Factory {

public:
	static shared_ptr<Image> imageFromPath(shared_ptr<Path> path);
	static shared_ptr<Screenshot> screenshotFromPath(shared_ptr<Path> path);

};

};


#endif