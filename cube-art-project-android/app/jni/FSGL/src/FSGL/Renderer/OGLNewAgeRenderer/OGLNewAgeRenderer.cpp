/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
 * File:   FSEOGLCore.cpp
 * Author: demensdeum
 *
 * Created on July 8, 2017, 10:10 AM
 */

#include "OGLNewAgeRenderer.h"
#include <FlameSteelCore/FSCUtils.h>

#include <FSGL/Data/Model/FSGLModel.h>
#include <FSGL/Data/Camera/FSGLCamera.h>
#include <FlameSteelCommonTraits/IOSystemParams.h>
#include <FSGL/Data/AnimationTransformationMatrix/AnimationTransformationMatrix.h>
#include <FlameSteelCommonTraits/Color.h>

#define GLM_ENABLE_EXPERIMENTAL 1

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>
#include <thread>

#include <fstream>
#include <iostream>
#include <set>

#include <json/json.hpp>
#include "OGLNewAgeRendererElements.h"

#include "shaders.h"


#define FSGL_LEGACY_OPENGL 1

using namespace std;
using namespace FSGL;
using namespace FlameSteelCore::Utils;

GLint OGLNewAgeRenderer::common_get_shader_program(const char *vertex_shader_source, const char *fragment_shader_source)
{

    GLchar infoLog[512];
    GLint fragment_shader;
    GLint shader_program;
    GLint success;
    GLint vertex_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << endl << infoLog << endl;
        throwRuntimeException(string("Can't compile shader program"));
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << endl << infoLog << endl;
        throwRuntimeException(string("Can't compile shader program"));
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << endl << infoLog << endl;
        throwRuntimeException(string("Can't link shader program"));
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

OGLNewAgeRenderer::~OGLNewAgeRenderer()
{

}

shared_ptr<Screenshot> OGLNewAgeRenderer::takeScreenshot() {

    auto width = params->width;
    auto height = params->height;

    auto colorComponentsCount = 3;
    GLubyte *bytes = (GLubyte *)malloc(colorComponentsCount * width * height);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, bytes);

    auto screenshot = make_shared<Screenshot>(width, height);

    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            auto byteX = x * colorComponentsCount;
            auto byteIndex = byteX + (y * (width * colorComponentsCount));
            auto redColorByte = bytes[byteIndex];
            auto greenColorByte = bytes[byteIndex + 1];
            auto blueColorByte = bytes[byteIndex + 2];
            auto color = make_shared<Color>(redColorByte, greenColorByte, blueColorByte, 255);
            screenshot->setColorAtXY(color, x, height - y - 1);
        }
    }

    free(bytes);

    cout << "OGLNewAgeRenderer - screenshot taken, width: " << width << " height: " << height << endl;

    return screenshot;
};

void OGLNewAgeRenderer::cleanObjectCache(shared_ptr<FSGLObject> object)
{

    auto model = object->model;
    auto size = model->meshes.size();
    for (unsigned int meshIndex = 0; meshIndex < size; meshIndex++)
    {
        auto mesh = model->meshes[meshIndex];
        mapMeshElementsMap.erase(mesh);
    }
    mapObjectElementsMap.erase(object);

}

vector<shared_ptr<AnimationTransformationMatrix> >  OGLNewAgeRenderer::animationTransformationMatricesRelatedToNodeWithName(shared_ptr<string> name,
        shared_ptr<FSGLModel> model,
        shared_ptr<FSGLMesh> mesh)
{

    cout << "Search for related nodes with name: " << *name << endl;

    vector<shared_ptr<AnimationTransformationMatrix> > animationMatrices;

    auto stringName = *(name.get());
    auto node = model->rootNode;
    if (node.get() == nullptr)
    {
        return animationMatrices;
    }

    auto rootNodeName = *(model->rootNode->name.get());

    if ( rootNodeName == *(name.get()) )
    {
        cout << "root node is related to " << *(name.get()) << endl;

        for (auto animationTransformationMatrix : mesh->animationTransformationMatrices)
        {

            if (  *(animationTransformationMatrix->name.get()) == rootNodeName )
            {
                animationMatrices.push_back(animationTransformationMatrix);
            }

        }

        for (auto node : model->rootNode->childs)
        {

            auto nodeName = *(node->name.get());

            for (auto animationTransformationMatrix : mesh->animationTransformationMatrices)
            {

                auto animationTransformationMatrixName = *(animationTransformationMatrix->name.get());

                if (  animationTransformationMatrixName == nodeName )
                {

                    cout << "pushed related animation matrix " << animationTransformationMatrixName << endl;
                    animationMatrices.push_back(animationTransformationMatrix);
                }

            }


        }

    }

    return animationMatrices;
}




void OGLNewAgeRenderer::removeObject(shared_ptr<FSGLObject> object)
{

    cleanObjectCache(object);

    auto layer = object->layer;

    if (layerToObjectsMap.find(layer) == layerToObjectsMap.end())
    {
        throwRuntimeException(string("Can't remove object, because layer does not exist in layer map"));
    }

    auto objects = layerToObjectsMap[layer];

    for (size_t i = 0; i < objects.size(); i++)
    {

        auto iteratedObject = objects[i];

        if (object->id == iteratedObject->id)
        {

            objects.erase(objects.begin() + i);

            layerToObjectsMap[layer] = objects;

            break;

        }
    }

    if (objects.size() < 1)
    {

        layerToObjectsMap.erase(layer);

        cout << "Layer removed" << endl;

    }

}

#ifndef FSGL_LEGACY_OPENGL

static void  FSGL_openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    if (type != GL_DEBUG_TYPE_OTHER)
    {
        cout << "OpenGL: "<< message << endl;
    }
}

#endif

void OGLNewAgeRenderer::preInitialize()
{
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,16);

    SDL_Init(SDL_INIT_VIDEO);
}

void OGLNewAgeRenderer::fillParams(shared_ptr<IOSystemParams> params)
{

    SDL_DisplayMode displayMode;
    SDL_GetDesktopDisplayMode(0, &displayMode);

    params->width = displayMode.w;
    params->height = displayMode.h;
}

SDL_Window* OGLNewAgeRenderer::initializeWindow(shared_ptr<IOSystemParams> params)
{

    this->params = params;

    if (params.get() == nullptr)
    {
        throwRuntimeException(string("Can't initialize renderer - params is null"));
    }

    if (params->title.get() == nullptr)
    {
        throwRuntimeException(string("Can't initialize renderer - title is null in params"));
    }

    auto title = params->title->c_str();

    Uint32 flags = 0;
    flags = flags | SDL_WINDOW_OPENGL;

    if (params->windowed == false)
    {
        flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0,0,&mode);
    int width = mode.w;
    int height = mode.h;

    window = SDL_CreateWindow(
                 title,
                 0,
                 0,
                 width,
                 height,
                 SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE
             );

    if (window == NULL)
    {

        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);

    }

#ifndef __EMSCRIPTEN__
#ifndef FSGL_LEGACY_OPENGL
    auto majorVersion = 4;
    auto minorVersion = 2;
#else
    auto majorVersion = 2;
    auto minorVersion = 0;
#endif


    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    context = SDL_GL_CreateContext(window);

    if (context == NULL)
    {

        printf("SDL_Init failed: %s\n", SDL_GetError());

    }

    /*GLenum err = glewInit();

    if (GLEW_OK != err)
    {

        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    }*/

    SDL_GL_MakeCurrent(window, context);

    //glEnable(GL_MULTISAMPLE);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

#ifndef FSGL_LEGACY_OPENGL
    glEnable(GL_DEBUG_OUTPUT);
    if (glGetError() != GL_NO_ERROR)
    {
        throwRuntimeException(string("Can't enable debug output"));
    }

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    if (glGetError() != GL_NO_ERROR)
    {
        throwRuntimeException(string("Can't enable debug output synchronous"));
    }

    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    if (glGetError() != GL_NO_ERROR)
    {
        throwRuntimeException(string("Can't enable debug message control"));
    }

    glDebugMessageCallback(FSGL_openGLDebugCallback, NULL);
#endif

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glViewport(0, 0, width, height);

    shader_program = common_get_shader_program(vertexShaderSource, fragmentShaderSource);

    glUseProgram(shader_program);

    GLint projectionMatrixUniform;

    glm::mat4 projectionMatrix = glm::perspective(45.0f, float(float(width) / float(height)), 0.001f, 200.0f);
    projectionMatrixUniform = glGetUniformLocation(shader_program, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    return window;

}

void OGLNewAgeRenderer::addObject(shared_ptr<FSGLObject> object)
{

	cout << "OGLNewAgeRenderer::addObject(shared_ptr<FSGLObject> object)" << endl;

    auto model = object->model;
    auto size = model->meshes.size();

    for (unsigned int meshIndex = 0; meshIndex < size; meshIndex++)
    {

        auto mesh = model->meshes[meshIndex];
        auto elements = make_shared<OGLNewAgeRendererElements>(mesh);

        mapMeshElementsMap[mesh] = elements;
        mapObjectElementsMap[object] = elements;
    }

    auto layer = object->layer;

    if (layerToObjectsMap.find(layer) == layerToObjectsMap.end())
    {
        auto newLayer = vector<shared_ptr<FSGLObject>>();
        layerToObjectsMap[layer] =  newLayer;
    }

    auto objectsLayer = layerToObjectsMap[layer];
    objectsLayer.push_back(object);

    layerToObjectsMap[layer] = objectsLayer;

}

void OGLNewAgeRenderer::render()
{

	//cout << "OGLNewAgeRenderer::render()" << endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepthf(1.0f);

    vector<shared_ptr<FSGLObject> > overlapObjects;

    for (auto pair : layerToObjectsMap)
    {

        auto objects = pair.second;

        glClear(GL_DEPTH_BUFFER_BIT);
        glClearDepthf(1.0f);

	//cout << "OGLNewAgeRenderer::render objects: " << objects.size() << endl;

        for (auto object : objects)
        {
            if (object.get() == nullptr)
            {

                throwRuntimeException(string("can't render null object"));

            }

            if (object->overlapObject == false)
            {
                renderObject(object);
            }
            else
            {
                overlapObjects.push_back(object);
            }
        }

        for (auto object: overlapObjects)
        {
            renderObject(object);
        }
    }

	glFinish();

    SDL_GL_SwapWindow(window);
}

void OGLNewAgeRenderer::stop()
{

}

shared_ptr<FSGLObject> OGLNewAgeRenderer::getObjectWithID(string id)
{

    if (idToObjectMap.find(id) == idToObjectMap.end())
    {

        throwRuntimeException(string("Id not found in id to object map, it was added? it was removed?"));

    }

    return idToObjectMap[id];
}

void OGLNewAgeRenderer::renderObject(shared_ptr<FSGLObject> object)
{

	//cout << "Render object" << endl;

    auto model = object->model;
	if (model->isValid() != true) {
		throwRuntimeException("Can't render - model self validation return false. Malformed model data?");
	}

    for (unsigned int meshIndex = 0; meshIndex < model->meshes.size(); meshIndex++)
    {

        auto mesh = model->meshes[meshIndex];

	if (mesh->isGLDataPrepared != true) {
		throwRuntimeException("Can't render mesh, vertices data was never updated");
	}

        GLint vertexSlot = glGetAttribLocation(shader_program, "vertex");

        auto elements = mapMeshElementsMap[mesh];

        glVertexAttribPointer(vertexSlot, 3, GL_FLOAT, GL_FALSE, FSGLMesh::glVertexSize(), 0);
        glEnableVertexAttribArray(vertexSlot);

        auto material = mesh->material;

        if (material == NULL)
        {

            throwRuntimeException(string("OGLNewAgeRenderer: cannot load material"));

        }

        auto surface = material->surface;

        if (surface == NULL)
        {

            cout << "OGLNewAgeRenderer: cannot load texture " << material->texturePath->c_str() << endl;

            throwRuntimeException(string("OGLNewAgeRenderer: cannot load texture"));

        }

        glActiveTexture(GL_TEXTURE0);

        GLint textureSlot = glGetUniformLocation(shader_program, "texture");
        glUniform1i(textureSlot, 0);

        GLint brightnessSlot = glGetUniformLocation(shader_program, "brightness");
        glUniform1f(brightnessSlot, object->brightness);

        GLint uvSlot = glGetAttribLocation(shader_program, "uvIn");
        glVertexAttribPointer(uvSlot, 2, GL_FLOAT, GL_FALSE, FSGLMesh::glVertexSize(), (GLvoid*) (sizeof (GLfloat) * 3));
        glEnableVertexAttribArray(uvSlot);

        GLint modelMatrixUniform;
        GLint viewMatrixUniform;

        auto currentAnimation = object->model->currentAnimation;

        if (currentAnimation.get() != nullptr)
        {
            for (auto nodeAnimation : currentAnimation->nodeAnimations)
            {

                auto positionVector = nodeAnimation->positionVectorFor(currentAnimation);
                auto rotationQuaternion = nodeAnimation->rotationFor(currentAnimation);

                auto glmQuaternion = glm::quat(rotationQuaternion->w, rotationQuaternion->x, rotationQuaternion->y, rotationQuaternion->z);
                auto rotationQuaternionMatrix = glm::toMat4(glmQuaternion);

                auto scalingVectorKeyframe = nodeAnimation->scalings[0];
                auto scaleVector = scalingVectorKeyframe->vector;

                auto matrix = glm::mat4(1.0);

#define FSGL_MATRIX_FUZZY_MODE 0

#if FSGL_MATRIX_FUZZY_MODE
                float randomFloat = static_cast <float> (rand()) / static_cast <float> (0.2);
                matrix = glm::rotate(matrix, randomFloat, glm::vec3(1.f, 0.f, 0.f));
                matrix = glm::rotate(matrix, randomFloat, glm::vec3(0.f, 1.f, 0.f));
                matrix = glm::rotate(matrix, randomFloat, glm::vec3(0.f, 0.f, 1.f));
#else
                matrix = glm::translate(matrix, glm::vec3(positionVector->x, positionVector->y, positionVector->z));

                matrix = rotationQuaternionMatrix * matrix;

                //matrix = glm::scale(matrix, glm::vec3(scaleVector->x, scaleVector->y, scaleVector->z));
#endif

                auto outputTransformationMatrix = make_shared<FSGLMatrix>();
                outputTransformationMatrix->matrix = matrix;

                auto relatedMatrices = animationTransformationMatricesRelatedToNodeWithName(nodeAnimation->name, model, mesh);

                for (auto relatedMatrix : relatedMatrices)
                {
                    cout << "apply transformation to related matrix" << endl;
                    relatedMatrix->matrix = outputTransformationMatrix;
                }
            }
        }

        GLint bonesMatricesUniform = glGetUniformLocation(shader_program, "bonesMatrices");
        auto animationTransformationMatrices = mesh->animationTransformationMatrices;
        glm::mat4 glmMatrices[64];
        auto unitMatrix = make_shared<FSGLMatrix>();

        for (auto i =0; i < 64; i++)
        {
            glmMatrices[i] = unitMatrix->matrix;
        }

        for (auto i = 0; i < animationTransformationMatrices.size(); i++)
        {
            auto animationTransformationMatrix = animationTransformationMatrices[i];

            glmMatrices[i] = animationTransformationMatrix->matrix->matrix;
            //cout << "shader transformations enabled for index" << i << endl;
        }

        glUniformMatrix4fv(bonesMatricesUniform, 64, GL_FALSE, glm::value_ptr(glmMatrices[0]));

        GLint bone0infoSlot = glGetAttribLocation(shader_program, "bone0info");
        glVertexAttribPointer(bone0infoSlot, 2, GL_FLOAT, GL_FALSE, FSGLMesh::glVertexSize(), (GLvoid*) (sizeof (GLfloat) * 5));
        glEnableVertexAttribArray(bone0infoSlot);

        GLint bone1infoSlot = glGetAttribLocation(shader_program, "bone1info");
        glVertexAttribPointer(bone1infoSlot, 2, GL_FLOAT, GL_FALSE, FSGLMesh::glVertexSize(), (GLvoid*) (sizeof (GLfloat) * 7));
        glEnableVertexAttribArray(bone1infoSlot);

        GLint bone2infoSlot = glGetAttribLocation(shader_program, "bone2info");
        glVertexAttribPointer(bone2infoSlot, 2, GL_FLOAT, GL_FALSE, FSGLMesh::glVertexSize(), (GLvoid*) (sizeof (GLfloat) * 9));
        glEnableVertexAttribArray(bone2infoSlot);

        GLint bone3infoSlot = glGetAttribLocation(shader_program, "bone3info");
        glVertexAttribPointer(bone3infoSlot, 2, GL_FLOAT, GL_FALSE, FSGLMesh::glVertexSize(), (GLvoid*) (sizeof (GLfloat) * 11));
        glEnableVertexAttribArray(bone3infoSlot);

        auto modelMatrix = object->matrix();

        modelMatrixUniform = glGetUniformLocation(shader_program, "modelMatrix");
        glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        auto viewMatrix = camera->matrix();

        viewMatrixUniform = glGetUniformLocation(shader_program, "viewMatrix");
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        elements->performPreRender();

        glDrawElements(GL_TRIANGLES, elements->indicesCount, GL_UNSIGNED_SHORT, 0);

        object->postRenderUpdate();
    }

}
