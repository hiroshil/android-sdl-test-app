#ifndef FSGLVERTEX_H
#define FSGLVERTEX_H


#include <memory>
#include <map>

#include "../Vector/FSGLVector.h"
#include "../Mesh/FSGLMesh.h"
#include "../Matrix/FSGLMatrix.h"
#include "../UVTextureCoordinates/FSGLUVTextureCoordinates.h"

using namespace std;

class FSGLMesh;
class FSGLVertexWeight;
class FSGLBone;

static const int FSGLVertexMaxBonesPerVertex = 4;

class FSGLVertex
{

public:
    FSGLVertex(float x, float y, float z, float u, float v);

    shared_ptr<FSGLVector> position;
    shared_ptr<FSGLUVTextureCoordinates> uvTextureCoordinates;
    weak_ptr<FSGLMesh> mesh;

    void setWeigthForMatrixAtIndex(float vertexWeight, int matrixIndex);
    void resetAnimation();

    int indexForAnimationMatrixAtShaderIndex(int index);
    float vertexWeightAtShaderIndex(int index);

private:
    map<int, float> boneNameToWeightMap;
    vector<float> bonesWeightsVector;

    float vertexWeights[FSGLVertexMaxBonesPerVertex] = {1, 0, 0, 0};
    int animationMatricesIndexes[FSGLVertexMaxBonesPerVertex] = {0, 0, 0, 0};

};

#endif