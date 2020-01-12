/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLQuaternionKeyframe.cpp
 * Author: demensdeum
 *
 * Created on November 5, 2017, 3:30 PM
 */

#include "FSGLQuaternionKeyframe.h"
#include <sstream>

FSGLQuaternionKeyframe::FSGLQuaternionKeyframe()
{
}

FSGLQuaternionKeyframe::FSGLQuaternionKeyframe(const FSGLQuaternionKeyframe& )
{
}

shared_ptr<string> FSGLQuaternionKeyframe::serializeIntoString(int identation)
{

    stringstream serializedData;

    for (int i = 0; i < identation; i ++)
    {
        serializedData << "\t";
    }

    serializedData << time << ", " << quaternion->serializeIntoString()->c_str();

    auto stringContainer = make_shared<string>(serializedData.str());

    return stringContainer;

}

FSGLQuaternionKeyframe::~FSGLQuaternionKeyframe()
{
}
