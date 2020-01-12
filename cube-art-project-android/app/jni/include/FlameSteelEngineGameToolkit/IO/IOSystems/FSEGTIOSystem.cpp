/*
 * FSEGTIOSystem.cpp
 *
 *  Created on: Aug 21, 2016
 *      Author: demensdeum
 */

#include "FSEGTIOSystem.h"

FSEGTIOSystem::FSEGTIOSystem()
{

}

void FSEGTIOSystem::clearCache()
{

    resourcesManager->clear();
}

void FSEGTIOSystem::preInitialize()
{

}

void FSEGTIOSystem::initialize(shared_ptr<IOSystemParams> )
{

}

void FSEGTIOSystem::fillParams(shared_ptr<IOSystemParams> params)
{

}

void FSEGTIOSystem::stop()
{

}

FSEGTIOSystem::~FSEGTIOSystem()
{
    // TODO Auto-generated destructor stub
}
