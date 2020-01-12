/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLNodeAnimation.cpp
 * Author: demensdeum
 *
 * Created on November 5, 2017, 2:32 PM
 */

#include "FSGLNodeAnimation.h"

#define GLM_ENABLE_EXPERIMENTAL 1

#include <sstream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <FSGL/Data/Node/FSGLNode.h>
#include <FSGL/Data/Animation/FSGLAnimation.h>

#include <iostream>

FSGLNodeAnimation::FSGLNodeAnimation()
{

}

FSGLNodeAnimation::FSGLNodeAnimation(const FSGLNodeAnimation& )
{
}

FSGLNodeAnimation::~FSGLNodeAnimation()
{
}

shared_ptr<FSGLVector> FSGLNodeAnimation::positionVectorFor(shared_ptr<FSGLAnimation> currentAnimation)
{

    auto ticks = currentAnimation->ticks();

    auto previousPosition = shared_ptr<FSGLVectorKeyframe>();
    auto nextPosition = shared_ptr<FSGLVectorKeyframe>();

    for (auto i = 0; i < positions.size(); i++)
    {
        auto position = positions[i];
        auto time = position->time;

        cout << "position->time " << time << endl;
        cout << "ticks " << ticks << endl;

        if (time < ticks)
        {
            previousPosition = position;
        }
        else
        {
            nextPosition = position;
            break;
        }
    }

    if (previousPosition.get() != nullptr && nextPosition.get() != nullptr)
    {
        cout << "Found all data for interpolation" << endl;

        auto outputVector = make_shared<FSGLVector>();

        auto previousPositionVector = previousPosition->vector;
        auto nextPositionVector = nextPosition->vector;

        auto proportion = float(ticks) / float(nextPosition->time);

        cout << "proportion: " << proportion << endl;

        auto xDiff = nextPositionVector->x - previousPositionVector->x;
        auto yDiff = nextPositionVector->y - previousPositionVector->y;
        auto zDiff = nextPositionVector->z - previousPositionVector->z;

        outputVector->x = previousPositionVector->x + (xDiff * proportion);
        outputVector->y = previousPositionVector->y + (yDiff * proportion);
        outputVector->z = previousPositionVector->z + (zDiff * proportion);

        return outputVector;
    }
    else
    {
        cout << "Can't find all data for interpolation" << endl;
    }

    return positions[0]->vector;

}

shared_ptr<FSGLQuaternion> FSGLNodeAnimation::rotationFor(shared_ptr<FSGLAnimation> currentAnimation)
{

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;

    if (node.get() == nullptr)
    {
        cout << "node.get() == nullptr" << endl;
        exit(1);
    }

    if (node->transformationMatrix.get() == nullptr)
    {
        cout << "node->transformationMatrix.get() == nullptr" << endl;
        exit(1);
    }

    glm::decompose(node->transformationMatrix->matrix, scale, rotation, translation, skew, perspective);

    auto outputQuaternion = make_shared<FSGLQuaternion>();

    outputQuaternion->x = rotation.x;
    outputQuaternion->y = rotation.y;
    outputQuaternion->z = rotation.z;
    outputQuaternion->w = rotation.w;

    return outputQuaternion;

}

shared_ptr<string> FSGLNodeAnimation::serializeIntoString(int identation)
{
    stringstream serializedData;

    for (auto i = 0; i < identation; i++)
    {
        serializedData << "\t";
    }

    serializedData << "Node Animation - " << *name << endl;

    if (positions.size() > 0)
    {

        for (auto i = 0; i < identation; i++)
        {
            serializedData << "\t";
        }

        serializedData << "Position Keyframes" << endl;
        for (auto position : positions)
        {
            serializedData << position->serializeIntoString(identation + 1)->c_str() << endl;
        }

        for (auto i = 0; i < identation; i++)
        {
            serializedData << "\t";
        }
        serializedData << "Scaling Keyframes" << endl;
        for (auto scaling : scalings)
        {
            serializedData << scaling->serializeIntoString(identation + 1)->c_str() << endl;
        }


        for (auto i = 0; i < identation; i++)
        {
            serializedData << "\t";
        }
        serializedData << "Rotation Keyframes" << endl;
        for (auto rotation : rotations)
        {
            serializedData << rotation->serializeIntoString(identation + 1)->c_str() << endl;
        }
    }

    auto stringContainer = make_shared<string>(serializedData.str());
    return stringContainer;
}
