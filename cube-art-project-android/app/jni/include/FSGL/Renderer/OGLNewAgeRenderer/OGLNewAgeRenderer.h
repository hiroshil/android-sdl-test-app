/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEOGLCore.h
 * Author: demensdeum
 *
 * Created on July 8, 2017, 10:10 AM
 */

#ifndef FSGLOGL_RENDERER_H_
#define FSGLOGL_RENDERER_H_

#include <SDL2/SDL.h>

#include <memory>

#include <FSGL/Data/Model/FSGLModel.h>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <FlameSteelCommonTraits/Screenshot.h>
#include <FSGL/Data/Object/FSGLObject.h>
#include <FSGL/Renderer/Renderer.h>
#include <FSGL/Renderer/OGLNewAgeRenderer/OGLNewAgeRendererElements.h>

#include <map>
#include <set>

using namespace std;
using namespace FSGL;

namespace FSGL
{

class OGLNewAgeRenderer: public Renderer
{
public:

    OGLNewAgeRenderer() : Renderer() { };
    virtual ~OGLNewAgeRenderer();

    void preInitialize();
    void fillParams(shared_ptr<IOSystemParams> params);
    SDL_Window* initializeWindow(shared_ptr<IOSystemParams> params);

    //Create, Remove
    void addObject(shared_ptr<FSGLObject> object);
    void removeObject(shared_ptr<FSGLObject> object);

    shared_ptr<FSGLObject> getObjectWithID(string id);

    void render();
    void stop();

    shared_ptr<Screenshot> takeScreenshot();

private:
    void cleanObjectCache(shared_ptr<FSGLObject> object);
    void renderObject(shared_ptr<FSGLObject> object);

    vector<shared_ptr<AnimationTransformationMatrix> > animationTransformationMatricesRelatedToNodeWithName(shared_ptr<string> name,
            shared_ptr<FSGLModel> model,
            shared_ptr<FSGLMesh> mesh);

    GLint common_get_shader_program(const char *vertex_shader_source, const char *fragment_shader_source);

    SDL_GLContext context;
    GLuint shader_program;

    SDL_Window *window;

    map<string, shared_ptr<FSGLObject>> idToObjectMap;
    map<int, vector<shared_ptr<FSGLObject>>> layerToObjectsMap;

    map<shared_ptr<FSGLMesh>, shared_ptr<OGLNewAgeRendererElements>> mapMeshElementsMap;
    map<shared_ptr<FSGLObject>, shared_ptr<OGLNewAgeRendererElements>> mapObjectElementsMap;

    shared_ptr<IOSystemParams> params;

};

};

#endif /* FSEOGLCORE_H */

