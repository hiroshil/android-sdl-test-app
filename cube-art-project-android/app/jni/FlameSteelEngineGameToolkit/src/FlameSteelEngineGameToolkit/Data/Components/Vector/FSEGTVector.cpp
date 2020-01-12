#include "FSEGTVector.h"

#include <FlameSteelEngineGameToolkit/Const/FSEGTConst.h>
#include <math.h>

int FSEGTVector::getTileX()
{
    int tileX = this->x / GameMapTileSize;
    return tileX;
}

int FSEGTVector::getTileY()
{
    int tileY = this->y / GameMapTileSize;
    return tileY;
}

shared_ptr<FSEGTVector> FSEGTVector::vectorXYZ(float x, float y, float z)
{

    shared_ptr<FSEGTVector> vector(new FSEGTVector);

    vector->x = x;
    vector->y = y;
    vector->z = z;

    return vector;
}

shared_ptr<FSEGTVector> FSEGTVector::copy()
{

    auto copied = make_shared<FSEGTVector>();

    copied->x = this->x;
    copied->y = this->y;
    copied->z = this->z;

    copied->setInstanceIdentifier(this->getInstanceIdentifier());
    copied->setClassIdentifier(this->getClassIdentifier());

    return copied;
}

void FSEGTVector::populate(shared_ptr<FSEGTVector> vector)
{
    x = vector->x;
    y = vector->y;
    z = vector->z;
}

glm::vec3 FSEGTVector::vec3() {
	auto vector = glm::vec3(x,y,z);
	return vector;
}