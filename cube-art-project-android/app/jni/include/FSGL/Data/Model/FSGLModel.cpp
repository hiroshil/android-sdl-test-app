/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEOGLModel.cpp
 * Author: demensdeum
 *
 * Created on July 8, 2017, 10:39 AM
 */

#include "FSGLModel.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

#include <FSGL/Data/Bone/FSGLBone.h>
#include <SDL2/SDL_image.h>
#include "../ResourcesLoader/FSGLResourceLoader.h"

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include <glm/gtx/transform.hpp>

using namespace std;

FSGLModel::FSGLModel()
{

}

void FSGLModel::playAnimationWithName(shared_ptr<string> animationName)
{

    auto unwrappedAnimationName = *(animationName.get());
    cout << "unwrappedAnimationName: " << unwrappedAnimationName << endl;

    currentAnimation = animations[unwrappedAnimationName];

    cout << "animations.size()" << animations.size() << endl;

    for (auto anim: animations)
    {
        cout << anim.first << ";" << anim.second << endl;
    }

    if (currentAnimation.get() == nullptr)
    {
        cout << "currentAnimation.get() == nullptr" << endl;
    }
    else
    {
        currentAnimation->restartAnimationCounters();
        cout << "currentAnimation: " << *(currentAnimation->name.get()) << endl;
    }
}

void FSGLModel::postRenderUpdate()
{
    if (currentAnimation.get() != nullptr)
    {
        currentAnimation->postRenderUpdate();
    }

    if (currentAnimation.get() != nullptr && currentAnimation->isEnded())
    {
        currentAnimation = nullptr;
    }
}

bool FSGLModel::isValid()
{

    if (meshes.size() < 1)
    {
        cout << "No meshes for model - not valid" << endl;
        return false;
    }

    for (auto mesh : meshes)
    {
        if (mesh->material.get() == nullptr)
        {
            cout << "No material for mesh - not valid" << endl;
            return false;
        }
	if (mesh->verticesObjects.size() < 1) {
            cout << "No vertices in mesh - not valid" << endl;
		return false;
	}
    }

    return true;
}

shared_ptr<string> FSGLModel::serializeIntoString()
{

    stringstream serializedData;

    serializedData << "Flame Steel Graphics Library Model @ Demens Deum" << endl;
    serializedData << "Model version = Happy Sasquatch (1.0)"<< endl;

    for (auto mesh : meshes)
    {

        if (mesh->material.get() == nullptr)
        {
            cout << "No material for mesh, pass" << endl;
            continue;
        }

        if (mesh->material->texturePath.get() == nullptr)
        {
            cout << "No texture for mesh, pass" << endl;
            continue;
        }


        serializedData << "Mesh" << endl;

        for (auto vertexObject : mesh->verticesObjects)
        {

            auto position = vertexObject->position;
            auto uvTextureCoordinates = vertexObject->uvTextureCoordinates;

            serializedData << "Vertex - x = " << position->x << ", y = " << position->y << ", z = " << position->z << ", u = " << uvTextureCoordinates->u << ", v = " << uvTextureCoordinates->v << endl;

        }

        for (unsigned int i = 0; i < mesh->indices.size(); i += 3)
        {

            auto indexA = mesh->indices[i + 0];
            auto indexB = mesh->indices[i + 1];
            auto indexC = mesh->indices[i + 2];

            serializedData << "Index = " << indexA << ", " << indexB << ", " << indexC << endl;

        }

        serializedData << "Material - Texture path = " << mesh->material->texturePath->c_str() << endl;


    }


    auto stringContainer = make_shared<string>(serializedData.str());

    return stringContainer;
}

shared_ptr<FSGLModel> FSGLModel::deserializeFromString(shared_ptr<string> serializedData,
        shared_ptr<MaterialLibrary> materialLibrary)
{

    auto model = make_shared<FSGLModel>();

    cout << "Read serialized data:" << endl;

    std::istringstream f(serializedData->c_str());

    std::string line;

    auto mesh = shared_ptr<FSGLMesh>();

    auto nodeNameToNode = map<string, shared_ptr<FSGLNode> >();

    while (std::getline(f, line))
    {

std::cout << line << std::endl;

        if (line.find("Mesh") != std::string::npos)
        {

            mesh = make_shared<FSGLMesh>();

            cout << "Mesh was added" << endl;

        }
        else if (line.find("Node") != std::string::npos)
        {

            std::regex r("Node - (.*)");
            std::smatch m;
            std::regex_search(line, m, r);

            auto rootNodeName = m[1].str();

            auto rootNode = make_shared<FSGLNode>();
            rootNode->name = make_shared<string>(rootNodeName);

            nodeNameToNode[rootNodeName] = rootNode;

            while (std::getline(f, line))
            {
                if (line.find("Node Childs") != std::string::npos)
                {

                    auto nodeChild = shared_ptr<FSGLNode>();

                    while (std::getline(f, line))
                    {

                        if (line.find("Node - ") != std::string::npos)
                        {

                            std::regex r("Node - (.*)");
                            std::smatch m;
                            std::regex_search(line, m, r);

                            auto nodeName = m[1].str();

                            nodeChild = make_shared<FSGLNode>();
                            nodeChild->name = make_shared<string>(nodeName);

                            nodeNameToNode[nodeName] = nodeChild;

                            rootNode->childs.push_back(nodeChild);
                        }
                        else if (line.find("Matrix 4 - ") != std::string::npos)
                        {
                            auto matrix = make_shared<FSGLMatrix>();
                            matrix->deserializeFromString(make_shared<string>(line));

                            if (nodeChild.get() == nullptr)
                            {
                                cout << "nodeChild is nullptr" << endl;
                                exit(1);
                            }
                            nodeChild->transformationMatrix = matrix;
                        }
                        else if (line.find("Node Childs End") != std::string::npos)
                        {
                            break;
                        }
                    }
                }
                else if (line.find("Matrix 4 - ") != std::string::npos)
                {
                    auto matrix = make_shared<FSGLMatrix>();
                    matrix->deserializeFromString(make_shared<string>(line));
                    rootNode->transformationMatrix = matrix;
                }
                else if (line.find("Node End") != std::string::npos)
                {
                    break;
                }
            }

            model->rootNode = rootNode;
        }
        else if (line.find("Animations") != std::string::npos)
        {
            while (std::getline(f, line))
            {
                if (line.find("Animation - ") != std::string::npos)
                {
                    std::regex r("Animation - (.*), duration = (.*)");
                    std::smatch m;
                    std::regex_search(line, m, r);

                    auto animationName = m[1].str();
                    float duration = stof(m[2].str());

                    auto convertedAnimation  = make_shared<FSGLAnimation>();
                    convertedAnimation->duration = duration;
                    convertedAnimation->name = make_shared<string>(animationName);

                    while (std::getline(f, line))
                    {

                        if (line.find("Node Animation - ") != std::string::npos)
                        {

                            std::regex r("Node Animation - (.*)");
                            std::smatch m;
                            std::regex_search(line, m, r);

                            auto animationName = m[1].str();

                            auto convertedNodeAnimation = make_shared<FSGLNodeAnimation>();
                            convertedNodeAnimation->name = make_shared<string>(animationName);

                            if (nodeNameToNode.find(animationName) == nodeNameToNode.end())
                            {
                                cout << "Incorrent node animation, break" << endl;
                            }

                            convertedNodeAnimation->node = nodeNameToNode[animationName];

                            while (std::getline(f, line))
                            {

                                if (line.find("Position Keyframes") != std::string::npos)
                                {

                                    while (std::getline(f, line))
                                    {

                                        if (line.find("VectorKeyframe - ") != std::string::npos)
                                        {

                                            std::regex r(".*time = (.*), x = (.*), y = (.*), z = (.*)");
                                            std::smatch m;
                                            std::regex_search(line, m, r);

                                            float time = stof(m[1].str());
                                            float x = stof(m[2].str());
                                            float y = stof(m[3].str());
                                            float z = stof(m[4].str());

                                            auto convertedPositionVectorKeyframe = make_shared<FSGLVectorKeyframe>();
                                            convertedPositionVectorKeyframe->time = time;

                                            auto convertedVector = make_shared<FSGLVector>(x, y, z);
                                            convertedPositionVectorKeyframe->vector = convertedVector;

                                            convertedNodeAnimation->positions.push_back(convertedPositionVectorKeyframe);
                                        }
                                        else if (line.find("Position Keyframes End") != std::string::npos)
                                        {
                                            break;
                                        }
                                    }
                                }

                                if (line.find("Scaling Keyframes") != std::string::npos)
                                {
                                    while (std::getline(f, line))
                                    {

                                        if (line.find("VectorKeyframe - ") != std::string::npos)
                                        {

                                            std::regex r(".*time = (.*), x = (.*), y = (.*), z = (.*)");
                                            std::smatch m;
                                            std::regex_search(line, m, r);

                                            float time = stof(m[1].str());
                                            float x = stof(m[2].str());
                                            float y = stof(m[3].str());
                                            float z = stof(m[4].str());

                                            auto convertedScalingVectorKeyframe = make_shared<FSGLVectorKeyframe>();
                                            convertedScalingVectorKeyframe->time = time;

                                            auto convertedVector = make_shared<FSGLVector>(x, y, z);
                                            convertedScalingVectorKeyframe->vector = convertedVector;

                                            convertedNodeAnimation->scalings.push_back(convertedScalingVectorKeyframe);
                                        }
                                        else if (line.find("Scaling Keyframes End") != std::string::npos)
                                        {
                                            break;
                                        }
                                    }
                                }

                                if (line.find("Rotation Keyframes") != std::string::npos)
                                {
                                    while (std::getline(f, line))
                                    {

                                        if (line.find("QuaternionKeyframe - ") != std::string::npos)
                                        {

                                            std::regex r(".*time = (.*), w = (.*), x = (.*), y = (.*), z = (.*)");
                                            std::smatch m;
                                            std::regex_search(line, m, r);

                                            float time = stof(m[1].str());
                                            float w = stof(m[2].str());
                                            float x = stof(m[3].str());
                                            float y = stof(m[4].str());
                                            float z = stof(m[5].str());

                                            auto convertedRotationVectorKeyframe = make_shared<FSGLQuaternionKeyframe>();
                                            convertedRotationVectorKeyframe->time = time;

                                            auto convertedQuaternion = make_shared<FSGLQuaternion>(w, x, y, z);
                                            convertedRotationVectorKeyframe->quaternion = convertedQuaternion;

                                            convertedNodeAnimation->rotations.push_back(convertedRotationVectorKeyframe);
                                        }

                                        else if (line.find("Rotation Keyframes End") != std::string::npos)
                                        {
                                            break;
                                        }
                                    }
                                }

                                if (line.find("Node Animation End") != std::string::npos)
                                {
                                    break;
                                }
                            }

                            convertedAnimation->nodeAnimations.push_back(convertedNodeAnimation);
                        }

                        if (line.find("Animation End") != std::string::npos)
                        {
                            break;
                        }
                    }

                    auto unwrappedAnimationName = *(convertedAnimation->name);
                    model->animations[unwrappedAnimationName] = convertedAnimation;

                    cout << "Converted animation loaded: " << unwrappedAnimationName << endl;
                    cout << "Node animations count: " << convertedAnimation->nodeAnimations.size() << endl;

                    for (auto nodeAnimation : convertedAnimation->nodeAnimations)
                    {
                        cout << unwrappedAnimationName << endl;
                    }

                    for (auto anim: animations)
                    {
                        cout << anim.first << ";" << anim.second << endl;
                    }

                }

                if (line.find("Animations End") != std::string::npos)
                {
                    break;
                }
            }
        }
        else if (line.find("Bone - ") != std::string::npos)
        {
            std::regex r("Bone - (.*)");
            std::smatch m;
            std::regex_search(line, m, r);

            string boneName = m[1].str();

            auto convertedBone = make_shared<FSGLBone>();
            convertedBone->name = make_shared<string>(boneName);

            while (std::getline(f, line))
            {

                if (line.find("Vertex Weights") != std::string::npos)
                {

                    while (std::getline(f, line))
                    {

                        if (line.find("Vertex Weight - ") != std::string::npos)
                        {

                            std::regex r(".*vertexID = (.*), weight = (.*)");
                            std::smatch m;
                            std::regex_search(line, m, r);

                            float vertexID = stoi(m[1].str());
                            float weight = stof(m[2].str());

                            auto vertexWeight = make_shared<FSGLVertexWeight>(vertexID, weight);

                            convertedBone->vertexWeights.push_back(vertexWeight);
                        }

                        else if (line.find("Vertex Weights End") != std::string::npos)
                        {
                            break;
                        }

                    }

                }

                if (line.find("Bone End") != std::string::npos)
                {
                    break;
                }
            }
            mesh->bones.push_back(convertedBone);

        }
        else if (line.find("Vertex - ") != std::string::npos)
        {

            std::regex r(".*x = (.*), y = (.*), z = (.*), u = (.*), v = (.*)");
            std::smatch m;
            std::regex_search(line, m, r);

            float x = stof(m[1].str());
            float y = stof(m[2].str());
            float z = stof(m[3].str());
            float u = stof(m[4].str());
            float v = stof(m[5].str());

            if (mesh.get() == nullptr)
            {

                cout << "FSGLModel deserialize from string error - mesh is null - incorrect model string format" << endl;
                exit(1);
            }

            auto vertexObject = make_shared<FSGLVertex>(x, y, z, u, v);
            mesh->verticesObjects.push_back(vertexObject);

        }
        else if (line.find("Index = ") != std::string::npos)
        {

            std::regex r("Index = (.*), (.*), (.*)");
            std::smatch m;
            std::regex_search(line, m, r);

            if (mesh.get() == nullptr)
            {

                //cout << "FSGLModel deserialize from string error - mesh is null - incorrect model string format" << endl;
                exit(1);
            }

            for (unsigned int i =1; i < 4; i++)
            {
                auto index = stoi(m[i].str());
                mesh->indices.push_back(index);
            }
        }
        else if (line.find("Material - Texture path = ") != std::string::npos)
        {

            std::regex r("Material - Texture path = (.*)");
            std::smatch m;
            std::regex_search(line, m, r);

            if (mesh.get() == nullptr)
            {

                //cout << "FSGLModel deserialize from string error - mesh is null - incorrect model string format" << endl;
                exit(1);
            }

            auto texturePath = make_shared<string>(m[1].str());
            auto convertedMaterial = materialLibrary->materialForPath(texturePath);

            if (convertedMaterial.get() == nullptr)
            {
                convertedMaterial = make_shared<FSGLMaterial>(texturePath);
		if (*texturePath == string("<No Path>")) {
			
		}
		else {


                auto surface = IMG_Load(convertedMaterial->texturePath->c_str());

                if (surface == nullptr)
                {

                    string errorString = "FSGLModelLoaderAssimp: cannot load texture: ";
                    errorString += convertedMaterial->texturePath->c_str();

                    throw runtime_error(errorString);
                }

                SDL_PixelFormat *pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
                SDL_Surface *resultSurface = SDL_ConvertSurface(surface, pixelFormat, 0);
                SDL_FreeSurface(surface);
                SDL_FreeFormat(pixelFormat);

                convertedMaterial->surface = resultSurface;

                materialLibrary->setMaterialForPath(convertedMaterial, texturePath);
		   }
            }

            mesh->material = convertedMaterial;

            if (convertedMaterial.get() == nullptr)
            {
                cout << "Converted material for mesh is nullptr" << endl;
                exit(1);
            }
            else
            {
                model->meshes.push_back(mesh);
            }

            mesh->populateAnimationTransformationMatrices();
            mesh->updateGlData();
        }
    }

	cout << "FSGLModel: deserialized from string with meshes count: " << model->meshes.size() << endl;

    return model;
}

FSGLModel::~FSGLModel()
{

}
