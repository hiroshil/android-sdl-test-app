/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLAnimation.cpp
 * Author: demensdeum
 *
 * Created on October 22, 2017, 8:14 PM
 */

#include "FSGLAnimation.h"

#include <iostream>
#include <sstream>

FSGLAnimation::FSGLAnimation()
{

    currentOffset = 0;

}

FSGLAnimation::FSGLAnimation(const FSGLAnimation& )
{
}

shared_ptr<string> FSGLAnimation::serializeIntoString(int identation)
{

    stringstream serializedData;

    for (auto i = 0; i < identation; i++)
    {
        serializedData << "\t";
    }

    serializedData << "Animation - " << name->c_str() << ", duration = " << duration << endl;

    if (nodeAnimations.size() > 0)
    {
        for (auto nodeAnimation : nodeAnimations)
        {
            serializedData << nodeAnimation->serializeIntoString(identation + 1)->c_str();
        }
    }

    for (auto i = 0; i < identation; i++)
    {
        serializedData << "\t";
    }

    serializedData << "Animation End" << endl;

    auto stringContainer = make_shared<string>(serializedData.str());
    return stringContainer;

}

void FSGLAnimation::restartAnimationCounters()
{

    startDate = make_shared<time_point<system_clock> > (system_clock::now());
    auto endDateStruct = *startDate + milliseconds(int(duration));
    endDate = make_shared<time_point<system_clock> >(endDateStruct);

    cout << "duration: " << duration << endl;
    cout << "breakpoint" << endl;
}

void FSGLAnimation::setCurrentOffset(double offset)
{

}

bool FSGLAnimation::isEnded()
{
    auto now = system_clock::now();

    if (now > *endDate)
    {
        return true;
    }

    return false;
}

int FSGLAnimation::ticks()
{

    auto now = system_clock::now();

    if (now <= *endDate)
    {
        auto ticksTimePoint = duration_cast<milliseconds>(now - *startDate).count();
        cout << "ticksTimePoint - " << ticksTimePoint << endl;
        return ticksTimePoint;
    }

    return 0;

}

void FSGLAnimation::postRenderUpdate()
{

}

FSGLAnimation::~FSGLAnimation()
{
    cout << "FSGLAnimation is dead" << endl;
}
