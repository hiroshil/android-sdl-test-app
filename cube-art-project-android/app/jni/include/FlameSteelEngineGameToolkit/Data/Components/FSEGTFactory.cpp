/*
 * FSEGTComponentsGenerator.cpp
 *
 *  Created on: Sep 4, 2016
 *      Author: demensdeum
 */

#include <FlameSteelEngineGameToolkit/Const/FSEGTConst.h>
#include <FlameSteelEngineGameToolkit/Data/Components/FSEGTFactory.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Sprite/FSEGTSprite.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Rectangle/FSEGTRectangle.h>
#include <FlameSteelCommonTraits/SerializedModel.h>

shared_ptr<FSEGTRectangle> FSEGTFactory::makeRectangle(int x, int y, int width, int height)
{

    auto rectangle = make_shared<FSEGTRectangle>(x, y, width, height);

    return rectangle;
}

shared_ptr <FSEGTModelReference> FSEGTFactory::makeModelReferenceComponent(shared_ptr<string> modelFilePath)
{

    auto component = make_shared<FSEGTModelReference>(modelFilePath);

    component->setClassIdentifier(make_shared<string>(FSEGTConstComponentsModel));
    component->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsModel));

    return component;
}

shared_ptr<BooleanComponent> FSEGTFactory::makeBooleanComponent()
{
    auto component = make_shared<BooleanComponent>();
    return component;
}

shared_ptr <Object> FSEGTFactory::makeOnScreenText(
    shared_ptr<string> text,
    float x, float y)
{
    if (x < 0 || y < 0 || x > 1 || y > 1)
    {
        throw logic_error("x and y should be in range 0.0-1.0 relative to screen size");
    }

    auto object = make_shared<Object>();

    object->setClassIdentifier(make_shared<string>(FSEGTConstObjectClassIdentifierOnScreenText));
    object->setInstanceIdentifier(make_shared<string>(FSEGTConstObjectClassIdentifierOnScreenText));

    auto textComponent = make_shared<FSEGTText>(text);
    auto screenPositionComponent = FSEGTFactory::makePositionComponent(x, y, 0);
    screenPositionComponent->setClassIdentifier(make_shared<string>(FSEGTConstComponentsRelativeScreenPosition));
    screenPositionComponent->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsRelativeScreenPosition));

    object->addComponent(textComponent);
    object->addComponent(screenPositionComponent);

    return object;
}

shared_ptr <Object> FSEGTFactory::makeOnSceneObject(
    shared_ptr<string> classIdentifier,
    shared_ptr<string> instanceIdentifier,
    shared_ptr<string> spriteFilePath,
    shared_ptr<string> modelFilePath,
    shared_ptr<string> serializedModel,
    float x, float y, float z,
    float width, float height, float depth,
    float rotationX, float rotationY, float rotationZ,
    int speed
)
{

    auto onSceneObject = make_shared<Object>();

    onSceneObject->setClassIdentifier(classIdentifier);
    onSceneObject->setInstanceIdentifier(instanceIdentifier);

    if (spriteFilePath.get() != nullptr)
    {

        auto spriteComponent = FSEGTFactory::makeSpriteComponent(spriteFilePath);

        spriteComponent->width = width;
        spriteComponent->height = height;

        onSceneObject->addComponent(spriteComponent);

    }

    if (modelFilePath.get() != nullptr)
    {

        auto modelComponent = FSEGTFactory::makeModelReferenceComponent(modelFilePath);

        onSceneObject->addComponent(modelComponent);
    }

    if (serializedModel.get() != nullptr)
    {

        auto serializedModelComponent = FSEGTFactory::makeSerializedModelComponent(serializedModel);
        onSceneObject->addComponent(serializedModelComponent);

    }

    onSceneObject->addComponent(FSEGTFactory::makePositionComponent(x, y, z));
    onSceneObject->addComponent(FSEGTFactory::makeScaleComponent(width, height, depth));
    onSceneObject->addComponent(FSEGTFactory::makeSpeedComponent(speed));
    onSceneObject->addComponent(FSEGTFactory::makeRotationComponent(rotationX, rotationY, rotationZ));
    onSceneObject->addComponent(FSEGTFactory::makeBrightnessComponent(1.0));

    return onSceneObject;
}

shared_ptr<FloatComponent> FSEGTFactory::makeBrightnessComponent(float brightness)
{

    auto brightnessComponent = make_shared<FloatComponent>();
    brightnessComponent->setClassIdentifier(make_shared<string>(FSEGTConstComponentsBrightness));
    brightnessComponent->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsBrightness));

    brightnessComponent->floatNumber = brightness;

    return brightnessComponent;
}

shared_ptr<FSEGTSerializedModel> FSEGTFactory::makeSerializedModelComponent(shared_ptr<string> serializedModel)
{

    auto serializedModelComponent = make_shared<FSEGTSerializedModel>(serializedModel);
    serializedModelComponent->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsSerializedModel));
    serializedModelComponent->setClassIdentifier(make_shared<string>(FSEGTConstComponentsSerializedModel));

    return serializedModelComponent;
}

shared_ptr <FSEGTVector> FSEGTFactory::makeScaleComponent(float width, float height, float depth)
{

    auto scaleComponent = make_shared<FSEGTVector>();
    scaleComponent->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsScale));
    scaleComponent->setClassIdentifier(make_shared<string>(FSEGTConstComponentsScale));

    scaleComponent->x = width;
    scaleComponent->y = height;
    scaleComponent->z = depth;

    return scaleComponent;
}

shared_ptr <FSEGTVector> FSEGTFactory::makePositionComponent(float x, float y, float z)
{

    auto positionComponent = make_shared<FSEGTVector>();
    positionComponent->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsPosition));
    positionComponent->setClassIdentifier(make_shared<string>(FSEGTConstComponentsPosition));

    positionComponent->x = x;
    positionComponent->y = y;
    positionComponent->z = z;

    return positionComponent;
}

shared_ptr <FSEGTVector> FSEGTFactory::makeRotationComponent(float rotationX, float rotationY, float rotationZ)
{

    auto component = make_shared<FSEGTVector>();
    component->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsRotation));
    component->setClassIdentifier(make_shared<string>(FSEGTConstComponentsRotation));

    component->x = rotationX;
    component->y = rotationY;
    component->z = rotationZ;

    return component;
}

shared_ptr <FSEGTVector> FSEGTFactory::makeSpeedComponent(int speed)
{
    auto component = make_shared<FSEGTVector>();

    component->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsSpeed));
    component->setClassIdentifier(make_shared<string>(FSEGTConstComponentsSpeed));

    component->x = speed;

    return component;

}

shared_ptr <FSEGTSprite> FSEGTFactory::makeSpriteComponent(shared_ptr<string> spriteFilePath)
{

    shared_ptr <FSEGTSprite> sprite(new FSEGTSprite(spriteFilePath));
    sprite->setInstanceIdentifier(make_shared<string>(FSEGTConstComponentsSprite));
    sprite->setClassIdentifier(make_shared<string>(FSEGTConstComponentsSprite));

    return sprite;
}

shared_ptr<SurfaceMaterial> FSEGTFactory::makeSurfaceMaterialComponent(int width, int height)
{

    auto surfaceMaterial = make_shared<SurfaceMaterial>(width, height);
    return surfaceMaterial;

}
