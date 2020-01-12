/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLObject.cpp
 * Author: demensdeum
 *
 * Created on July 29, 2017, 11:45 AM
 */

#include "FSGLObject.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "../Vector/FSGLVector.h"

using namespace std;

enum
{
    FSGLObjectModelSerializationIndex,
    FSGLObjectScaleVectorSerializationIndex,
    FSGLObjectRotationVectorSerializationIndex,
    FSGLObjectPositionVectorSerializationIndex,
    FSGLObjectSerializationCount

};

FSGLObject::FSGLObject(shared_ptr<FSGLModel> model)
{

    scaleVector = make_shared<FSGLVector>(1.f, 1.f, 1.f);
    rotationVector = make_shared<FSGLVector>(0.f, 0.f, 0.f);
    positionVector = make_shared<FSGLVector>(0.f, 0.f, 0.f);

    this->model = model;

}

void FSGLObject::playAnimationWithName(shared_ptr<string> animationName)
{
    model->playAnimationWithName(animationName);
}

glm::mat4 FSGLObject::matrix()
{
    auto matrix = glm::mat4(1.0);

    matrix = glm::translate(matrix, glm::vec3(positionVector->x, positionVector->y, positionVector->z));

    matrix = glm::rotate(matrix, rotationVector->x, glm::vec3(1.f, 0.f, 0.f));
    matrix = glm::rotate(matrix, rotationVector->y, glm::vec3(0.f, 1.f, 0.f));
    matrix = glm::rotate(matrix, rotationVector->z, glm::vec3(0.f, 0.f, 1.f));

    matrix = glm::scale(matrix, glm::vec3(scaleVector->x, scaleVector->y, scaleVector->z));

    return matrix;
}

shared_ptr<string> FSGLObject::serializeIntoString()
{

    stringstream serializedData;

    serializedData << model->serializeIntoString()->c_str() << endl;
    serializedData << scaleVector->serializeIntoString()->c_str() << endl;
    serializedData << rotationVector->serializeIntoString()->c_str() << endl;
    serializedData << positionVector->serializeIntoString()->c_str() << endl;

    auto stringContainer = make_shared<string>(serializedData.str());

    return stringContainer;
}

shared_ptr<FSGLObject> FSGLObject::deserializeFromString(shared_ptr<string> serializedData, shared_ptr<MaterialLibrary> materialLibrary)
{

    auto outputObject = make_shared<FSGLObject>();

    string serializedDataString = *serializedData.get();

    //cout << serializedDataString.c_str() << endl;

    std::istringstream input;
    input.str(serializedDataString.c_str());

    for (auto i = 0; i < FSGLObjectSerializationCount; i++)
    {

        string line;
        std::getline(input, line);

        auto rawLine = line.c_str();
        auto lineContainer = make_shared<string>(rawLine);

        //cout << "FSGLObject: line " << rawLine << endl;

        switch (i)
        {

        case FSGLObjectModelSerializationIndex:
        {
            auto deserializedModel = FSGLModel().deserializeFromString(lineContainer, materialLibrary);
            outputObject->model = static_pointer_cast<FSGLModel>(deserializedModel);
        }
        break;

        case FSGLObjectScaleVectorSerializationIndex:
        {
            auto deserializedVector = FSGLVector().deserializeFromString(lineContainer);
            outputObject->scaleVector = static_pointer_cast<FSGLVector>(deserializedVector);
        }
        break;

        case FSGLObjectRotationVectorSerializationIndex:
        {
            auto deserializedVector = FSGLVector().deserializeFromString(lineContainer);
            outputObject->rotationVector = static_pointer_cast<FSGLVector>(deserializedVector);
        }
        break;

        case FSGLObjectPositionVectorSerializationIndex:
        {
            auto deserializedVector = FSGLVector().deserializeFromString(lineContainer);
            outputObject->positionVector = static_pointer_cast<FSGLVector>(deserializedVector);
        }
        break;

        }
    }

    return outputObject;
}

shared_ptr<FSGLObject> FSGLObject::deserializeFromFile(shared_ptr<string> path)
{
    return make_shared<FSGLObject>();
}

void FSGLObject::postRenderUpdate()
{
    model->postRenderUpdate();
}

FSGLObject::~FSGLObject()
{

    //cout << "FSGLObject destructed" << endl;

}
