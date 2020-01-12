
#include "FSGLVertex.h"

#include <iostream>
#include <string>
#include <FSGL/Data/VertexWeight/FSGLVertexWeight.h>
#include <FSGL/Data/Bone/FSGLBone.h>

using namespace std;

#define VERTEX_DEBUGGING 0

FSGLVertex::FSGLVertex(float x, float y, float z, float u, float v)
{

    position = make_shared<FSGLVector>(x, y, z);
    uvTextureCoordinates = make_shared<FSGLUVTextureCoordinates>(u, v);

#if VERTEX_DEBUGGING

    //cout << "x = " << x << "; y = " << y << "; z = " << z << ";" << endl;
    //cout << "u = " << u << "; v = " << v << ";" << endl;

#endif

}

void FSGLVertex::resetAnimation()
{
    vertexWeights[0] = 1;
    vertexWeights[1] = 0;
    vertexWeights[2] = 0;
    vertexWeights[3] = 0;

    animationMatricesIndexes[0] = 0;
    animationMatricesIndexes[1] = 0;
    animationMatricesIndexes[2] = 0;
    animationMatricesIndexes[3] = 0;

    boneNameToWeightMap.clear();
    bonesWeightsVector.clear();
}

void FSGLVertex::setWeigthForMatrixAtIndex(float vertexWeight, int matrixIndex)
{

    boneNameToWeightMap[matrixIndex] = vertexWeight;

    //cout << "set vertex weight: " << vertexWeight << " for matrixIndex: " << matrixIndex << endl;

    if (boneNameToWeightMap.size() > FSGLVertexMaxBonesPerVertex)
    {
        throw runtime_error("More than 4 bones does not supported by engine");
    }

    // cout << "boneNameToWeightMap.size() " << boneNameToWeightMap.size() << endl;

    bonesWeightsVector.push_back(vertexWeight);

    auto slot = bonesWeightsVector.size() - 1;

    animationMatricesIndexes[slot] = matrixIndex;

    // cout << "animationMatricesIndexes["<< slot <<"] = " << matrixIndex << endl;

    for (auto i = 0; i < bonesWeightsVector.size(); i++)
    {
        vertexWeights[i] = bonesWeightsVector[i];
    }
}

int FSGLVertex::indexForAnimationMatrixAtShaderIndex(int index)
{
    auto animationIndex = animationMatricesIndexes[index];

    //cout << "indexForAnimationMatrixAtShaderIndex: " << index << " = " << animationIndex << endl;

    /*if (animationIndex == 1) {
    	cout << "Animation index = 1" << endl;
    }*/

    return animationIndex;
}

float FSGLVertex::vertexWeightAtShaderIndex(int index)
{
    auto weight = vertexWeights[index];
    //cout << "vertexWeight at index " << index << " - weight " << weight << endl;

    return weight;
}
