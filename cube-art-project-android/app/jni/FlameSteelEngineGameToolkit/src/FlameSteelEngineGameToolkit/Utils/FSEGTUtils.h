/*
 * FSEGTUtils.h
 *
 *  Created on: Sep 11, 2016
 *      Author: demensdeum
 */

#ifndef UTILS_FSEGTUTILS_H_
#define UTILS_FSEGTUTILS_H_

#include <FlameSteelEngineGameToolkit/Data/Components/Float/FloatComponent.h>
#include <FlameSteelCore/Object.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Vector/FSEGTVector.h>
#include <FlameSteelEngineGameToolkit/Data/Components/SurfaceMaterial/SurfaceMaterial.h>
#include <string.h>

class FSEGTText;
class FSEGTSerializedModel;

using namespace FlameSteelEngine::GameToolkit;

class FSEGTUtils
{
public:
    FSEGTUtils();

    static int getFramesCount(shared_ptr<Object> object);
    static int getCurrentFrame(shared_ptr<Object> object);
    static void updateObjectAnimationTick(shared_ptr<Object> object);

    static void setAttackActionComponentForObject(shared_ptr<Object> object);
    static void setSpeedForObject(int speed, shared_ptr<Object> object);

    static shared_ptr<FSEGTVector> getObjectPosition(shared_ptr<Object> object);
    static shared_ptr<FSEGTVector> getObjectScale(shared_ptr<Object> object);
    static shared_ptr<FSEGTVector> getObjectRotation(shared_ptr<Object> object);
    static shared_ptr<FSEGTVector> getObjectRelativeScreenPosition(shared_ptr<Object> object);
    static shared_ptr<FloatComponent> getObjectBrightness(shared_ptr<Object> object);
    static shared_ptr<SurfaceMaterial> getObjectSurfaceMaterial(shared_ptr<Object> object);

    static void hideObject(shared_ptr<Object> object);
    static void unhideObject(shared_ptr<Object> object);

    static void moveObject(shared_ptr<Object> object);
    static void movePositionVectorByRotationAndSpeed(shared_ptr<Object> positionComponent, shared_ptr<Object> eulerComponent, shared_ptr<Object> speedComponent);

    static shared_ptr<FSEGTText> getText(shared_ptr<Object> object);

    static shared_ptr<string> getSpritePath(shared_ptr<Object> object);
    static shared_ptr<string> getModelFilePathForObject(shared_ptr<Object> object);

    static shared_ptr<string> platformPath(const char *relativePath);

    static shared_ptr<FSEGTSerializedModel> getSerializedModel(shared_ptr<Object> object);

    static bool contains3D(shared_ptr<Object> object);

    static bool isOnScreenObject(shared_ptr<Object> object);
    static bool isSkyboxObject(shared_ptr<Object> object);

    virtual ~FSEGTUtils();
};

#endif /* UTILS_FSEGTUTILS_H_ */
