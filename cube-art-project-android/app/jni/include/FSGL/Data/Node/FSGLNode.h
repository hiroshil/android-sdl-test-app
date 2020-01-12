/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLNode.h
 * Author: demensdeum
 *
 * Created on November 5, 2017, 2:03 PM
 */

#ifndef FSGLNODE_H
#define FSGLNODE_H

#include <string>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <FSGL/Data/Mesh/FSGLMesh.h>
#include <FSGL/Data/Matrix/FSGLMatrix.h>

class FSGLMesh;

using namespace std;

class FSGLNode: public enable_shared_from_this<FSGLNode>
{
public:
    FSGLNode();
    virtual ~FSGLNode();

    shared_ptr<string> name;

    shared_ptr<FSGLNode> parent;
    vector < shared_ptr<FSGLNode> > childs;
    vector< shared_ptr<FSGLMesh> > meshes;
    shared_ptr<FSGLMatrix> transformationMatrix;

    shared_ptr<string> serializeIntoString(int identation = 0);

private:

};

#endif /* FSGLNODE_H */

