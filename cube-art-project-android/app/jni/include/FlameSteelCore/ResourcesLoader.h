/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ResourceLoader.h
 * Author: demensdeum
 *
 * Created on March 12, 2017, 9:28 AM
 */

#ifndef FSCRESOURCELOADER_H
#define FSCRESOURCELOADER_H

#include "Resource.h"
#include "ResourcesManager.h"

namespace FlameSteelCore {

class ResourcesLoader {
public:
    ResourcesLoader();
    ResourcesLoader(const ResourcesLoader& orig);
    virtual ~ResourcesLoader();

    virtual void loadURL(shared_ptr<string> url, shared_ptr<ResourcesManager> resourcesManager);

private:

};
};

#endif /* FSCRESOURCELOADER_H */

