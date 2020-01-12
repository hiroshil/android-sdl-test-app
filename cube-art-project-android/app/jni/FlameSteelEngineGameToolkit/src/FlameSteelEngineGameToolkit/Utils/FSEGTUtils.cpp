/*
 * FSEGTUtils.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: demensdeum
 */

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>

#ifndef _WIN32

#include <unistd.h>

#endif

#include <FlameSteelCore/FSCUtils.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Text/FSEGTText.h>
#include <FlameSteelEngineGameToolkit/Utils/FSEGTUtils.h>
#include <FlameSteelEngineGameToolkit/Const/FSEGTConst.h>
#include <FlameSteelEngineGameToolkit/Data/Components/FSEGTFactory.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Vector/FSEGTVector.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Sprite/FSEGTSprite.h>
#include <FlameSteelEngineGameToolkit/Data/Components/ModelReference/FSEGTModelReference.h>
#include <FlameSteelCommonTraits/SerializedModel.h>

using namespace std;
using namespace FlameSteelCore::Utils;

FSEGTUtils::FSEGTUtils()
{
    // TODO Auto-generated constructor stub

}

bool FSEGTUtils::isOnScreenObject(shared_ptr<Object> object)
{
    return object->containsComponentWithIdentifier(make_shared<string>(FSEGTConstComponentsFlag2D)) ||
           object->containsComponentWithIdentifier(make_shared<string>(FSEGTConstComponentsFlag2D));
}

bool FSEGTUtils::isSkyboxObject(shared_ptr<Object> object)
{
    return object->containsComponentWithIdentifier(make_shared<string>(FSEGTConstComponentsFlagSkybox)) ||
           object->containsComponentWithIdentifier(make_shared<string>(FSEGTConstComponentsFlagSkybox));
}

bool FSEGTUtils::contains3D(shared_ptr<Object> object)
{

	auto contains3D = object->containsComponentWithIdentifier(make_shared<string>(FSEGTConstComponentsModel)) ||
           object->containsComponentWithIdentifier(make_shared<string>(FSEGTConstComponentsSerializedModel));

	//cout << "contains3D: " << contains3D << endl;

    return contains3D;

}

int FSEGTUtils::getCurrentFrame(shared_ptr<Object> object)
{

    auto spriteComponentSharedPointer = object->getComponent(make_shared<string>(FSEGTConstComponentsSprite));

    auto spriteComponent = (FSEGTSprite *) spriteComponentSharedPointer.get();

    if (spriteComponent == nullptr)
    {

        return 0;
    }

    return spriteComponent->frameIndex;
}

int FSEGTUtils::getFramesCount(shared_ptr<Object> object)
{

    auto spriteComponentSharedPointer = object->getComponent(make_shared<string>(FSEGTConstComponentsSprite));

    auto spriteComponent = (FSEGTSprite *) spriteComponentSharedPointer.get();

    if (spriteComponent == nullptr)
    {

        return 0;
    }

    return spriteComponent->framesCount;
}

shared_ptr<FloatComponent> FSEGTUtils::getObjectBrightness(shared_ptr<Object> object)
{

    auto brightnessComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsBrightness));

    return  static_pointer_cast<FloatComponent>(brightnessComponent);

}

shared_ptr<FSEGTVector> FSEGTUtils::getObjectRelativeScreenPosition(shared_ptr<Object> object)
{

    auto relativeScreenPositionComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsRelativeScreenPosition));

    return static_pointer_cast<FSEGTVector>(relativeScreenPositionComponent);

}

shared_ptr<FSEGTSerializedModel> FSEGTUtils::getSerializedModel(shared_ptr<Object> object)
{

    auto serializedModelComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsSerializedModel));

    return static_pointer_cast<FSEGTSerializedModel>(serializedModelComponent);

}

void FSEGTUtils::updateObjectAnimationTick(shared_ptr<Object> object)
{

    auto spriteComponentSharedPointer = object->getComponent(make_shared<string>(FSEGTConstComponentsSprite));

    auto spriteComponent = (FSEGTSprite *) spriteComponentSharedPointer.get();

    if (spriteComponent != nullptr)
    {

        spriteComponent->updateAnimationTick();
    }
}

shared_ptr<string> FSEGTUtils::getModelFilePathForObject(shared_ptr<Object> object)
{

    auto modelComponentSharedPointer = object->getComponent(make_shared<string>(FSEGTConstComponentsModel));

    auto modelComponent = (FSEGTModelReference*) modelComponentSharedPointer.get();

    if (modelComponentSharedPointer == nullptr)
    {

        return shared_ptr<string>();
    }

    if (modelComponent == nullptr)
    {

        return shared_ptr<string>();
    }

    return modelComponent->modelFilePath;
}

shared_ptr<string> FSEGTUtils::platformPath(const char *relativePath)
{

    // oh yeah, this is pain

#ifdef _WIN32
    // oh come on Microsoft, it's 2017, make this goddamn realpath function, srsly

    char absolutePath[_MAX_PATH + 1];

    _fullpath(absolutePath, relativePath, _MAX_PATH);

    const char *imagePath = absolutePath;
#else
#ifdef  __EMSCRIPTEN__

    // give path as is to emscripten

    const char *imagePath = relativePath;
#else
    // resolve to absolutePath for other platforms, assume nix

    char currentPath[PATH_MAX + 1];

    if (getcwd(currentPath, sizeof (currentPath)) != nullptr)
    {

        printf("FSEGTUtils: Current path %s\n", currentPath);

    }

    char absolutePath[PATH_MAX + 1] = {0};

    char relativePathBuffer[PATH_MAX + 1] = {0};
    strcpy(relativePathBuffer, relativePath);

    if (!realpath(relativePathBuffer, absolutePath))
    {

        string errorString = "Cannot resolve path: ";
        errorString += absolutePath;

        throwRuntimeException(errorString);
    }

    char *imagePath = absolutePath;
#endif
#endif
    shared_ptr<string> platformPath(new string(imagePath));

    return platformPath;
}

shared_ptr<FSEGTText> FSEGTUtils::getText(shared_ptr<Object> object)
{

    auto textSharedPointer = object->getComponent(make_shared<string>(FSEGTConstComponentsText));

    return static_pointer_cast<FSEGTText>(textSharedPointer);
}

shared_ptr<FSEGTVector> FSEGTUtils::getObjectPosition(shared_ptr<Object> object)
{
    auto positionComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsPosition));
    return static_pointer_cast<FSEGTVector>(positionComponent);

}

shared_ptr<SurfaceMaterial> FSEGTUtils::getObjectSurfaceMaterial(shared_ptr<Object> object)
{

    auto surfaceMaterial = object->getComponent(make_shared<string>("Surface Material"));

    return static_pointer_cast<SurfaceMaterial>(surfaceMaterial);
}

shared_ptr<FSEGTVector> FSEGTUtils::getObjectRotation(shared_ptr<Object> object)
{

    auto rotationComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsRotation));

    return static_pointer_cast<FSEGTVector>(rotationComponent);
}

shared_ptr<FSEGTVector> FSEGTUtils::getObjectScale(shared_ptr<Object> object)
{

    auto scaleComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsScale));

    return static_pointer_cast<FSEGTVector>(scaleComponent);

}

void FSEGTUtils::hideObject(shared_ptr<Object> object)
{

    if (!object->getComponent(make_shared<string>(FSEGTConstComponentsDeleted)))
    {

        shared_ptr<Object> deletedComponent(new Object);
        deletedComponent->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsDeleted));
        deletedComponent->setClassIdentifier(make_shared<string>(FSEGTConstComponentsDeleted));
        object->addComponent(deletedComponent);
        printf("deleted component added\n");

    }
}

void FSEGTUtils::unhideObject(shared_ptr<Object> object)
{

    object->removeComponent(make_shared<string>(FSEGTConstComponentsDeleted));

}

void FSEGTUtils::movePositionVectorByRotationAndSpeed(shared_ptr<Object> positionComponent, shared_ptr<Object> eulerComponent, shared_ptr<Object> speedComponent)
{

    if (positionComponent && eulerComponent && speedComponent)
    {

        FSEGTVector *position = (FSEGTVector *) positionComponent.get();
        FSEGTVector *eulerVector = (FSEGTVector *) eulerComponent.get();
        FSEGTVector *speed = (FSEGTVector *) speedComponent.get();

        float degreeAngle = eulerVector->y;
        degreeAngle = -degreeAngle; //invert
        float radiansAngle = degreeAngle;

        float xDiff = cos(radiansAngle) * speed->x;
        float yDiff = sin(radiansAngle) * speed->x;

        position->x += xDiff;
        position->y += yDiff;

    }

}

void FSEGTUtils::moveObject(shared_ptr<Object> object)
{

    shared_ptr<Object> positionComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsPosition));
    shared_ptr<Object> eulerComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsRotation));
    shared_ptr<Object> speedComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsSpeed));

    if (positionComponent && eulerComponent && speedComponent)
    {

        FSEGTUtils::movePositionVectorByRotationAndSpeed(positionComponent, eulerComponent, speedComponent);
    }

}

void FSEGTUtils::setSpeedForObject(int speed, shared_ptr<Object> object)
{
    shared_ptr<Object> speedComponent = object->getComponent(make_shared<string>(FSEGTConstComponentsSpeed));

    if (!speedComponent)
    {
        shared_ptr<FSEGTVector> newSpeedComponent(new FSEGTVector);
        newSpeedComponent->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsSpeed));
        newSpeedComponent->setClassIdentifier(make_shared<string>(FSEGTConstComponentsSpeed));

        object->addComponent(newSpeedComponent);

        speedComponent = newSpeedComponent;
    }

    FSEGTVector *speedVector = (FSEGTVector *) speedComponent.get();
    speedVector->x = speed;
}

void FSEGTUtils::setAttackActionComponentForObject(shared_ptr<Object> )
{

    throw logic_error("FSEGTUtils::setAttackActionComponentForObject unimplemented");

}

shared_ptr<string> FSEGTUtils::getSpritePath(shared_ptr<Object> object)
{

    auto spriteComponentSharedPointer = object->getComponent(make_shared<string>(FSEGTConstComponentsSprite));

    auto spriteComponent = (FSEGTSprite *) spriteComponentSharedPointer.get();

    if (spriteComponent == nullptr)
    {

        return nullptr;
    }

    return spriteComponent->spriteFilePath;
}

FSEGTUtils::~FSEGTUtils()
{
    // TODO Auto-generated destructor stub
}
