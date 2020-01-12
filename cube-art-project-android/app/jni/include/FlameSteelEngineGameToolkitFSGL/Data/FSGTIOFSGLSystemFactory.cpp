/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGTIOFSGLSystemFactory.cpp
 * Author: demensdeum
 *
 * Created on August 5, 2017, 7:28 PM
 */

#include <FlameSteelCore/FSCUtils.h>
#include "FSGTIOFSGLSystemFactory.h"
#include <FlameSteelEngineGameToolkit/Const/FSEGTConst.h>

#include <FSGL/Data/ResourcesLoader/FSGLResourceLoader.h>

#include <FlameSteelEngineGameToolkit/Utils/FSEGTUtils.h>
#include <FlameSteelCommonTraits/SerializedModel.h>
#include <FSGL/Data/MaterialLibrary/MaterialLibrary.h>

#include <sstream>

using namespace FlameSteelCore::Utils;
using namespace FlameSteelEngine::GameToolkit::SceneLayer;

FSGTIOFSGLSystemFactory::FSGTIOFSGLSystemFactory() {
}

FSGTIOFSGLSystemFactory::FSGTIOFSGLSystemFactory(const FSGTIOFSGLSystemFactory& ) {
}

shared_ptr<FSGLObject> FSGTIOFSGLSystemFactory::graphicsObjectFrom(shared_ptr<Object> object, shared_ptr<MaterialLibrary> materialLibrary) {

    auto model = shared_ptr<FSGLModel>();

    auto modelFilePath = shared_ptr<string>();

    if (object->containsComponentWithIdentifier(make_shared<string>(FSEGTConstComponentsModel)))
    {
        modelFilePath = FSEGTUtils::getModelFilePathForObject(object);
    }

    auto serializedModel = shared_ptr<FSEGTSerializedModel>();

    if (object->containsComponentWithIdentifier(make_shared<string>(FSEGTConstComponentsSerializedModel)))
    {
        serializedModel = FSEGTUtils::getSerializedModel(object);
    }

    if (modelFilePath.get() != nullptr) {

        stringstream stream;

        stream << modelFilePath->c_str();

        auto preparedModelFilePath = FSEGTUtils::platformPath(stream.str().c_str());

        model = static_pointer_cast<FSGLModel>(FSGLResourceLoader::loadResource(preparedModelFilePath, materialLibrary));

    }
    else if (serializedModel.get() != nullptr) {

        model = FSGLResourceLoader::deserializeModel(serializedModel, materialLibrary);

    }

    if (model.get() == nullptr) {

        throwRuntimeException(string("Can't load model for some reason"));

    }

	if (model->meshes.size() < 1) {
	        throwRuntimeException(string("No meshes in model"));
	}

    auto graphicsObject = make_shared<FSGLObject>(model);

    auto position = FSEGTUtils::getObjectPosition(object);

    graphicsObject->id = object->uuid;

    graphicsObject->positionVector->x = position->x;
    graphicsObject->positionVector->y = position->y;
    graphicsObject->positionVector->z = position->z;

    auto rotation = FSEGTUtils::getObjectRotation(object);

    graphicsObject->rotationVector->x = rotation->x;
    graphicsObject->rotationVector->y = rotation->y;
    graphicsObject->rotationVector->z = rotation->z;

    auto scale = FSEGTUtils::getObjectScale(object);

    graphicsObject->scaleVector->x = scale->x;
    graphicsObject->scaleVector->y = scale->y;
    graphicsObject->scaleVector->z = scale->z;

    auto brightness = FSEGTUtils::getObjectBrightness(object);

    graphicsObject->brightness = brightness->floatNumber;

    auto layer = Scene;

    if (FSEGTUtils::isOnScreenObject(object)) {
        layer = Screen;
    }
    else if (FSEGTUtils::isSkyboxObject(object)) {
        layer = Skybox;
    }

    graphicsObject->layer = layer;

    if (object->containsComponentWithIdentifier(make_shared<string>("Surface Material"))) {

        auto surfaceMaterial = FSEGTUtils::getObjectSurfaceMaterial(object);

        if (surfaceMaterial.get() != nullptr) {
            auto model = graphicsObject->model;
            if (model->meshes.size() == 1) {
                auto mesh = model->meshes[0];
                mesh->material  = surfaceMaterial->material;
            }
            else {
			auto errorString = string("Can't add surface material, because fsgl object must contain exactly 1 mesh; now meshes count:");
			errorString += to_string(model->meshes.size());
                	throwRuntimeException(errorString);
            }
        }

    }

    if (model->currentAnimation.get() != nullptr) {
        model->playAnimationWithName(model->currentAnimation->name);
    }

    return graphicsObject;
}

FSGTIOFSGLSystemFactory::~FSGTIOFSGLSystemFactory() {
}
