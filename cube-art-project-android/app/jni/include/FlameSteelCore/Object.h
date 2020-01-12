/*
 * Object.h
 *
 *  Created on: Jul 10, 2016
 *      Author: demensdeum
 */

#ifndef FSCOBJECT_H_
#define FSCOBJECT_H_

#include <cstdlib>
#include <utility>
#include <string>
#include <memory>
#include "Serializable.h"

namespace FlameSteelCore {
class Objects;
};

using namespace std;
using namespace FlameSteelCore;

static unsigned long long int FSGL_OBJECT_ID = 0;

namespace FlameSteelCore {

class Object : public Serializable {
public:
    Object();
    virtual ~Object();

    string uuid;

    void setInstanceIdentifier(shared_ptr<string> gameSceneIdentifier);
    void setClassIdentifier(shared_ptr<string> gameSceneClass);
    shared_ptr<string> getInstanceIdentifier();
    shared_ptr<string> getClassIdentifier();
    void addComponent(shared_ptr<Object> component);
    shared_ptr<Object> getComponent(shared_ptr<string> identifier);
    void removeComponent(shared_ptr<string> identifier);

    bool containsComponentWithIdentifier(shared_ptr<string> identifier);

    string debugIdentifier = "";

private:
    shared_ptr<string> instanceIdentifier;
    shared_ptr<string> classIdentifier;

    shared_ptr<Objects> components;

};

};

#endif /* FSCOBJECT_H_ */
