/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLQuaternion.cpp
 * Author: demensdeum
 *
 * Created on November 5, 2017, 2:33 PM
 */

#include "FSGLQuaternion.h"
#include <sstream>
#include <iostream>

FSGLQuaternion::FSGLQuaternion()
{
}

FSGLQuaternion::FSGLQuaternion(float w, float x, float y, float z)
{
    this->w = w;
    this->x = x;
    this->y =y;
    this->z = z;
}

FSGLQuaternion::FSGLQuaternion(const FSGLQuaternion& )
{
}

shared_ptr<string> FSGLQuaternion::serializeIntoString(int identation)
{

    stringstream serializedData;

    for (int i = 0; i < identation; i++)
    {
        serializedData << "\t";
    }

    serializedData << w << "," << x << "," << y << "," << z;

    auto stringContainer = make_shared<string>(serializedData.str());

    return stringContainer;
}

FSGLQuaternion::~FSGLQuaternion()
{
}
