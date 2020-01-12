/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLMesh.h
 * Author: demensdeum
 *
 * Created on August 1, 2017, 11:02 PM
 */

#ifndef FSGLMESH_H
#define FSGLMESH_H

#include <vector>
#include <memory>

#include <SDL_opengles2.h>

#include "../Vertex/FSGLVertex.h"
#include <FlameSteelCommonTraits/Material.h>
#include <glm/glm.hpp>
#include "../Vector/FSGLVector.h"
#include "../Quaternion/FSGLQuaternion.h"
#include "../Matrix/FSGLMatrix.h"

namespace FSGL
{
class AnimationTransformationMatrix;
};

class FSGLBone;
class FSGLModel;
class FSGLVertex;

using namespace std;
using namespace FSGL;

class FSGLMesh: public std::enable_shared_from_this<FSGLMesh>
{
public:
    FSGLMesh();
    virtual ~FSGLMesh();

    vector<shared_ptr<FSGLVertex> > verticesObjects;

    vector<GLushort> indices;

    GLushort* glIndices = NULL;
    GLfloat* glVertices = NULL;

    GLsizeiptr glVerticesBufferSize = 0;
    GLsizeiptr glIndicesBufferSize = 0;
    GLsizei glIndicesCount = 0;

    static int glVertexCount();
    static GLsizei glVertexSize();

    void updateGlData();
    void populateAnimationTransformationMatrices();

    shared_ptr<FSGLMaterial> material;
    shared_ptr<FSGLModel> parentModel;
    vector<shared_ptr<AnimationTransformationMatrix> > animationTransformationMatrices;

    vector<shared_ptr<FSGLBone> > bones;

    shared_ptr<AnimationTransformationMatrix> animationTransformationMatrixWithName(shared_ptr<string> name);

	bool isGLDataPrepared = false;

};

#endif /* FSGLMESH_H */

