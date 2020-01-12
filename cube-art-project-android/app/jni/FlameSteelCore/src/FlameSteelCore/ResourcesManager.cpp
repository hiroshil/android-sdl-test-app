/*
 * ResourcesManager.cpp
 *
 *  Created on: Jan 16, 2017
 *      Author: demensdeum
 */

#include "ResourcesManager.h"
#include <iostream>

using namespace std;

ResourcesManager::ResourcesManager() {
    // TODO Auto-generated constructor stub

}

shared_ptr<Resource> ResourcesManager::getResourceByName(shared_ptr<string> name) {


    //cout << "getResourceByName: " << name->c_str() << endl;

    return resourcesMap[*name.get()];
}

void ResourcesManager::setResourceWithName(shared_ptr<string> name, shared_ptr<Resource> resource) {

    cout << "setResourceByName: " << name->c_str() << endl;

    resourcesMap[*name.get()] = resource;
}

void ResourcesManager::clear() {

    auto itr = resourcesMap.begin();

    if (itr != resourcesMap.end())
    {
        resourcesMap.erase(itr);
    }
}


ResourcesManager::~ResourcesManager() {
    // TODO Auto-generated destructor stub
}

