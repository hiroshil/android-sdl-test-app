/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLBone.cpp
 * Author: demensdeum
 *
 * Created on October 22, 2017, 7:37 PM
 */

#include "FSGLBone.h"

#include <iostream>

#include "../Mesh/FSGLMesh.h"

FSGLBone::FSGLBone()
{
}

shared_ptr<string> FSGLBone::serializeIntoString(int identation)
{

    auto serializedData = string("");
    if (name.get() != nullptr)
    {
        for (auto i = 0; i < identation; i++)
        {
            serializedData += "\t";
        }
        serializedData += "Bone - ";
        serializedData += *name;
        serializedData += "\n";
        if (vertexWeights.size() > 0)
        {
            for (auto i = 0; i < identation; i++)
            {
                serializedData += "\t";
            }
            serializedData += "\tVertex Weights";
            serializedData += "\n";
            for (auto vertexWeight : vertexWeights)
            {
                serializedData += vertexWeight->serializeIntoString(identation + 2)->c_str();
                serializedData += "\n";
            }
            for (auto i = 0; i < identation; i++)
            {
                serializedData += "\t";
            }
            serializedData += "\tVertex Weights End";
            serializedData += "\n";
        }
    }

    cout << "Serialized Bone data:" << serializedData << endl;

    auto stringContainer = make_shared<string>(serializedData.c_str());
    return stringContainer;
}

FSGLBone::FSGLBone(const FSGLBone& )
{
}

FSGLBone::~FSGLBone()
{
}
