/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLNode.cpp
 * Author: demensdeum
 *
 * Created on November 5, 2017, 2:03 PM
 */

#include "FSGLNode.h"

#include <iostream>
#include <sstream>

FSGLNode::FSGLNode()
{
}

shared_ptr<string> FSGLNode::serializeIntoString(int identation)
{
    stringstream serializedData;

    for (auto i = 0; i < identation; i++)
    {
        serializedData << "\t";
    }

    serializedData << "Node - ";
    if (name.get() != nullptr)
    {
        serializedData << *name;
    }
    else
    {
        serializedData << "<NO NAME>";
    }

    serializedData << endl;

    serializedData << transformationMatrix->serializeIntoString(identation + 1)->c_str();

    if (childs.size() > 0)
    {

        for (auto i = 0; i < identation; i++)
        {
            serializedData << "\t";
        }
        serializedData << "Node Childs" << endl;

        for (auto childNode : childs)
        {
            serializedData << childNode->serializeIntoString(identation + 1)->c_str();
        }
    }

    auto stringContainer = make_shared<string>(serializedData.str());
    return stringContainer;
}

FSGLNode::~FSGLNode()
{
}