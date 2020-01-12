/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ResourceLoader.cpp
 * Author: demensdeum
 *
 * Created on March 12, 2017, 9:28 AM
 */

#include "ResourcesLoader.h"
#include <iostream>

using namespace std;

ResourcesLoader::ResourcesLoader() {
}

ResourcesLoader::ResourcesLoader(const ResourcesLoader& ) {
}

void ResourcesLoader::loadURL(shared_ptr<string>, shared_ptr<ResourcesManager> ) {

    cout << "ResourcesLoader: loadURL must be overridden." << endl;

    exit(1);
}

ResourcesLoader::~ResourcesLoader() {
}