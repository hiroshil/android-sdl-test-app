/*
 * FSEGTComponentsGenerator.h
 *
 *  Created on: Sep 4, 2016
 *      Author: demensdeum
 */

#ifndef DATA_COMPONENTS_FSEGTCOMPONENTSGENERATOR_H_
#define DATA_COMPONENTS_FSEGTCOMPONENTSGENERATOR_H_

#include <FlameSteelCore/Object.h>
#include <memory>
#include <string>

#include <FlameSteelEngineGameToolkit/Data/Components/Rectangle/FSEGTRectangle.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Boolean/BooleanComponent.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Float/FloatComponent.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Vector/FSEGTVector.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Sprite/FSEGTSprite.h>
#include <FlameSteelEngineGameToolkit/Data/Components/ModelReference/FSEGTModelReference.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Text/FSEGTText.h>
#include <FlameSteelEngineGameToolkit/Data/Components/SurfaceMaterial/SurfaceMaterial.h>

using namespace FlameSteelEngine::GameToolkit;

class FSEGTSerializedModel;

using namespace std;

class FSEGTFactory: public Object
{
public:

    // object

    static shared_ptr <Object> makeOnSceneObject(
        shared_ptr<string> classIdentifier,
        shared_ptr<string> instanceIdentifier,
        shared_ptr<string> spriteFilePath,
        shared_ptr<string> modelFilePath,
        shared_ptr<string> serializedModel,
        float x,
        float y,
        float z,
        float width,
        float height,
        float depth,
        float rotationX,
        float rotationY,
        float rotationZ,
        int speed
    );

    static shared_ptr <Object> makeOnScreenText(
        shared_ptr<string> text,
        float x, float y);

    // components

    static shared_ptr<BooleanComponent> makeBooleanComponent();
    static shared_ptr <FSEGTVector> makePositionComponent(float x = 0, float y = 0, float z = 0);
    static shared_ptr <FSEGTVector> makeRotationComponent(float rotationX, float rotationY, float rotationZ);
    static shared_ptr <FSEGTVector> makeSpeedComponent(int speed);
    static shared_ptr <FSEGTSprite> makeSpriteComponent(shared_ptr<string> spriteFilePath);
    static shared_ptr <FSEGTModelReference>  makeModelReferenceComponent(shared_ptr<string> modelFilePath);
    static shared_ptr <FSEGTVector> makeScaleComponent(float width, float height, float depth);
    static shared_ptr<FSEGTSerializedModel> makeSerializedModelComponent(shared_ptr<string> serializedModel);
    static shared_ptr<FloatComponent> makeBrightnessComponent(float brightness);
    static shared_ptr<SurfaceMaterial> makeSurfaceMaterialComponent(int width, int height);
    static shared_ptr<FSEGTRectangle> makeRectangle(int x, int y, int width, int height);
};

#endif /* DATA_COMPONENTS_FSEGTCOMPONENTSGENERATOR_H_ */
