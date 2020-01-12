#ifndef FSGLANIMATIONKEYFRAME_DEFINED_H_
#define FSGLANIMATIONKEYFRAME_DEFINED_H_

#include <memory>

class FSGLMatrix;

using namespace std;

namespace FSGL
{

class AnimationKeyframe
{

public:
    AnimationKeyframe(float offset, shared_ptr<FSGLMatrix> transformMatrix);
    float offset = 0;
    shared_ptr<FSGLMatrix> transformMatrix;
};
};

#endif