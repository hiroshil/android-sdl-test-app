/*
 * ResourcesManager.h
 *
 *  Created on: Jan 16, 2017
 *      Author: demensdeum
 */

#ifndef FSCRESOURCESMANAGER_H_
#define FSCRESOURCESMANAGER_H_

#include "Object.h"
#include "Resource.h"

#include <memory>
#include <map>

namespace FlameSteelCore {

class ResourcesManager: public Object {
public:
    ResourcesManager();

    shared_ptr<Resource> getResourceByName(shared_ptr<string> name);
    void setResourceWithName(shared_ptr<string> name, shared_ptr<Resource> resource);

    void clear();

    virtual ~ResourcesManager();

private:
    map<string, shared_ptr<Resource> > resourcesMap;

};
};

#endif /* FSCRESOURCESMANAGER_H_ */
