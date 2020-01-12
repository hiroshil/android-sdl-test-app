/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLBone.h
 * Author: demensdeum
 *
 * Created on October 22, 2017, 7:37 PM
 */

#ifndef FSGLBONE_H
#define FSGLBONE_H

#include <string>
#include <memory>

#include <FSGL/Data/Matrix/FSGLMatrix.h>
#include <FSGL/Data/Node/FSGLNode.h>
#include <FSGL/Data/VertexWeight/FSGLVertexWeight.h>

#include "../NodeAnimation/FSGLNodeAnimation.h"

#include <vector>

class FSGLMesh;
class FSGLMatrix;

using namespace std;

class FSGLBone
{
public:
    FSGLBone();
    FSGLBone(const FSGLBone& orig);
    virtual ~FSGLBone();

    shared_ptr<string> name;
    shared_ptr<FSGLMatrix> offsetMatrix;
    vector<shared_ptr<FSGLVertexWeight> > vertexWeights;

    shared_ptr<string> serializeIntoString(int identation = 0);

private:

};

#endif /* FSGLBONE_H */

