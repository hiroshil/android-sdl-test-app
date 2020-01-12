/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLMesh.cpp
 * Author: demensdeum
 *
 * Created on August 1, 2017, 11:02 PM
 */

#include <glm/detail/type_vec.hpp>

#include "FSGLMesh.h"

#include "../Object/FSGLObject.h"
#include <FSGL/Data/Bone/FSGLBone.h>
#include <FSGL/Data/AnimationTransformationMatrix/AnimationTransformationMatrix.h>

#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>


FSGLMesh::FSGLMesh()
{
}

int FSGLMesh::glVertexCount()
{
    vector<string> vertexFieldsDescription =
    {

        "x",
        "y",
        "z",
        "u",
        "v",
        "bone0index",
        "bone0weight",
        "bone1index",
        "bone1weight",
        "bone2index",
        "bone2weight",
        "bone3index",
        "bone3weight"

    };
    return int(vertexFieldsDescription.size());
}

GLsizei FSGLMesh::glVertexSize()
{
    return sizeof(GLfloat) * glVertexCount();
}

void FSGLMesh::populateAnimationTransformationMatrices()
{

    animationTransformationMatrices.clear();

    auto animationTransformationMatrix = make_shared<AnimationTransformationMatrix>();
    animationTransformationMatrix->index = 0;
    animationTransformationMatrix->name = make_shared<string>("Unit Matrix");
    animationTransformationMatrix->matrix = make_shared<FSGLMatrix>();

    animationTransformationMatrices.push_back(animationTransformationMatrix);

    for (auto bone : bones)
    {

        if (bone->name.get() == nullptr)
        {
            throw runtime_error("Bone name is null");
        }
        auto boneName = bone->name->c_str();

        auto animationTransformationMatrix = make_shared<AnimationTransformationMatrix>();
        animationTransformationMatrix->index = animationTransformationMatrices.size();
        animationTransformationMatrix->name = make_shared<string>(boneName);
        animationTransformationMatrix->matrix = make_shared<FSGLMatrix>();
        animationTransformationMatrix->vertexWeights = bone->vertexWeights;

        for (auto vertexWeight : animationTransformationMatrix->vertexWeights)
        {
            auto vertexID = vertexWeight->vertexID;
            auto weight = vertexWeight->weight;
            auto vertexObject = this->verticesObjects[vertexID];
            vertexObject->setWeigthForMatrixAtIndex(weight, animationTransformationMatrices.size());
        }

        animationTransformationMatrices.push_back(animationTransformationMatrix);
    }

    cout << "Populated animation transformation matrices vector, size: " << animationTransformationMatrices.size() << endl;
}

shared_ptr<AnimationTransformationMatrix> FSGLMesh::animationTransformationMatrixWithName(shared_ptr<string> name)
{

    for (auto animationTransformationMatrix : animationTransformationMatrices)
    {
        if (*(animationTransformationMatrix->name.get()) == *(name.get()) )
        {
            return animationTransformationMatrix;
        }
    }

    string errorName = "No such animation transformation matrix with name ";
    errorName += *(name.get());

    throw runtime_error(errorName);

    return shared_ptr<AnimationTransformationMatrix>();
}

void FSGLMesh::updateGlData()
{

    glVertices = new GLfloat[verticesObjects.size() * glVertexCount()];

    //cout << "verticesObjects.size() " << verticesObjects.size() << endl;

    auto count = glVertexCount();

    for (unsigned int i = 0; i < verticesObjects.size() * count; i += count)
    {

        auto vertexObject = verticesObjects[i / count];

        // x, y, z, u, v, bone0index, bone0weight, bone1index, bone1weight, bone2index, bone2weight, bone3index, bone3weight

        // x, y, z

        glVertices[i] = vertexObject->position->x;
        glVertices[i + 1] = vertexObject->position->y;
        glVertices[i + 2] = vertexObject->position->z;

        // UV

        glVertices[i + 3] = vertexObject->uvTextureCoordinates->u;
        glVertices[i + 4] = vertexObject->uvTextureCoordinates->v;

        // animation matrices info
        // use one bone at index zero by default

        glVertices[i + 5] = vertexObject->indexForAnimationMatrixAtShaderIndex(0);
        glVertices[i + 6] = vertexObject->vertexWeightAtShaderIndex(0);

        glVertices[i + 7] = vertexObject->indexForAnimationMatrixAtShaderIndex(1);
        glVertices[i + 8] = vertexObject->vertexWeightAtShaderIndex(1);

        glVertices[i + 9] = vertexObject->indexForAnimationMatrixAtShaderIndex(2);
        glVertices[i + 10] = vertexObject->vertexWeightAtShaderIndex(2);

        glVertices[i + 11] = vertexObject->indexForAnimationMatrixAtShaderIndex(3);
        glVertices[i + 12] = vertexObject->vertexWeightAtShaderIndex(3);

    }

    glIndices = new GLushort[indices.size() * sizeof (GLushort)];

    for (unsigned int i = 0; i < indices.size(); i++)
    {

        glIndices[i] = indices[i];

    }

    glVerticesBufferSize = verticesObjects.size() * count * sizeof (GLfloat);
    glIndicesBufferSize = indices.size() * sizeof (GLushort);
    glIndicesCount = indices.size();

	isGLDataPrepared = true;

}

FSGLMesh::~FSGLMesh()
{

    if (glIndices != NULL)
    {

        delete glIndices;

    }

    if (glVertices != NULL)
    {

        delete glVertices;

    }

}