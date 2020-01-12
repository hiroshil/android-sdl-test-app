/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLVectorKeyframe.cpp
 * Author: demensdeum
 *
 * Created on November 5, 2017, 3:29 PM
 */

#include "FSGLVectorKeyframe.h"
#include <sstream>

FSGLVectorKeyframe::FSGLVectorKeyframe()
{
}

FSGLVectorKeyframe::FSGLVectorKeyframe(const FSGLVectorKeyframe& )
{
}

shared_ptr<string> FSGLVectorKeyframe::serializeIntoString(int identation)
{

    stringstream serializedData;

    for (int i = 0; i < identation; i ++)
    {
        serializedData << "\t";
    }

    serializedData << time << ", " << vector->serializeIntoString()->c_str();

    auto stringContainer = make_shared<string>(serializedData.str());

    return stringContainer;

}

FSGLVectorKeyframe::~FSGLVectorKeyframe()
{
}
