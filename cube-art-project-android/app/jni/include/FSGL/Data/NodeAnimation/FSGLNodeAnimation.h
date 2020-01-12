/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLNodeAnimation.h
 * Author: demensdeum
 *
 * Created on November 5, 2017, 2:32 PM
 */

#ifndef FSGLNODEANIMATION_H
#define FSGLNODEANIMATION_H

#include <memory>
#include <string>
#include <vector>

class FSGLAnimation;

#include "../Matrix/FSGLMatrix.h"
#include "../VectorKeyframe/FSGLVectorKeyframe.h"
#include "../QuaternionKeyframe/FSGLQuaternionKeyframe.h"

class FSGLNode;

using namespace std;

class FSGLNodeAnimation
{
public:
    FSGLNodeAnimation();
    FSGLNodeAnimation(const FSGLNodeAnimation& orig);
    virtual ~FSGLNodeAnimation();

    shared_ptr<string> name;

    vector <shared_ptr<FSGLVectorKeyframe> > positions;
    vector <shared_ptr<FSGLQuaternionKeyframe> > rotations;
    vector <shared_ptr<FSGLVectorKeyframe> > scalings;

    shared_ptr<FSGLNode> node;

    shared_ptr<string> serializeIntoString(int identation = 0);

    shared_ptr<FSGLVector> positionVectorFor(shared_ptr<FSGLAnimation> currentAnimation);
    shared_ptr<FSGLQuaternion> rotationFor(shared_ptr<FSGLAnimation> currentAnimation);





private:

};

#endif /* FSGLNODEANIMATION_H */

