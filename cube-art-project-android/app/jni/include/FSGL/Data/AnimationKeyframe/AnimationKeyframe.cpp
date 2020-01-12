#include "AnimationKeyframe.h"

using namespace FSGL;

AnimationKeyframe::AnimationKeyframe(float offset, shared_ptr<FSGLMatrix> transformMatrix)
{
    this->offset = offset;
    this->transformMatrix = transformMatrix;
}