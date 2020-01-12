#include "OGLNewAgeRendererElements.h"
#include <FSGL/Data/Mesh/FSGLMesh.h>
#include <FlameSteelCore/FSCUtils.h>

using namespace FSGL;
using namespace FlameSteelCore::Utils;

OGLNewAgeRendererElements::OGLNewAgeRendererElements(shared_ptr<FSGLMesh> mesh)
{

    this->mesh = mesh;

    glGenBuffers(1, &vbo);
    glGenVertexArraysOES(1, &vao);
    glGenBuffers(1, &indexBuffer);

    verticesBufferSize = mesh->glVerticesBufferSize;
    indicesBufferSize = mesh->glIndicesBufferSize;
    indicesCount = mesh->glIndicesCount;

    glGenTextures(1, &textureBinding);

    performPreRender();

    glBufferData(GL_ARRAY_BUFFER, verticesBufferSize, mesh->glVertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesBufferSize, mesh->glIndices, GL_STATIC_DRAW);

    fillTexture();

}

void OGLNewAgeRendererElements::performPreRender()
{

    bind();

    if (mesh->material == nullptr)
    {
        throwRuntimeException(string("material is null, crashing"));
    }

    if (mesh->material->needsUpdate)
    {
        fillTexture();
        mesh->material->needsUpdate = false;
    }

}

void OGLNewAgeRendererElements::fillTexture()
{

    auto surface = mesh->material->surface;

	if (surface == nullptr) {
		throwRuntimeException(string("material surface is null, crashing"));
	}

    auto palleteMode = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, palleteMode, surface->w, surface->h, 0, palleteMode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

}

void OGLNewAgeRendererElements::bind()
{

    glBindVertexArrayOES(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBindTexture(GL_TEXTURE_2D, textureBinding);

}

OGLNewAgeRendererElements::~OGLNewAgeRendererElements()
{

    glDeleteVertexArraysOES(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteTextures(1, &textureBinding);

}
