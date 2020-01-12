#ifndef FSGLANIMATIONTRANSFORMATIONMATRIX_H_
#define FSGLANIMATIONTRANSFORMATIONMATRIX_H_

#include <memory>
#include <vector>

using namespace std;

class FSGLMatrix;
class FSGLVertexWeight;

namespace FSGL
{

class AnimationTransformationMatrix
{

public:
    AnimationTransformationMatrix();

    int index;
    shared_ptr<string> name;
    shared_ptr<FSGLMatrix> matrix;
    vector<shared_ptr<FSGLVertexWeight> > vertexWeights;

};
};

#endif