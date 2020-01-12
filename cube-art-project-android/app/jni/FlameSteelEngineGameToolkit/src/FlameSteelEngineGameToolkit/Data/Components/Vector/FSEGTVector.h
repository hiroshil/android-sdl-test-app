/*
 * FSEGTVector.h
 *
 *  Created on: Aug 4, 2016
 *      Author: demensdeum
 */

#ifndef FSEGTVECTOR_H_
#define FSEGTVECTOR_H_

#include <FlameSteelCore/Object.h>
#include <glm/glm.hpp>

using namespace FlameSteelCore;

class FSESerializable;

class FSEGTVector : public Object
{

public:
    float x;
    float y;
    float z;

    int getTileX();
    int getTileY();

	glm::vec3 vec3();

    shared_ptr<FSEGTVector> copy();
    void populate(shared_ptr<FSEGTVector> vector);
    static shared_ptr<FSEGTVector> vectorXYZ(float x, float y, float z);
};

#endif /* FSEGTVECTOR_H_ */
