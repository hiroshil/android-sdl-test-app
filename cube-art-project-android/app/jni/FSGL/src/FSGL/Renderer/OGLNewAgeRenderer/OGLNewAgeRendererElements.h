#ifndef FSGLOGLNEWAGERENDERERELEMENTS_H_
#define FSGLOGLNEWAGERENDERERELEMENTS_H_

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#include <memory>

using namespace std;

class FSGLMesh;

namespace FSGL
{

class OGLNewAgeRendererElements
{

public:
    OGLNewAgeRendererElements(shared_ptr<FSGLMesh> mesh);
    ~OGLNewAgeRendererElements();
    GLuint vao, vbo, indexBuffer;
    GLsizei    indicesCount = 0;
    GLsizeiptr verticesBufferSize, indicesBufferSize;
    GLuint textureBinding = 0;

    void performPreRender();

private:
    shared_ptr<FSGLMesh> mesh;

    void bind();
    void fillTexture();

};

};

#endif
