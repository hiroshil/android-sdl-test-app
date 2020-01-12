/*
 * Objects.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: demensdeum
 */

#include "Objects.h"

#include <cstddef>
#include <iostream>
#include <FlameSteelCore/FSCUtils.h>

using namespace FlameSteelCore::Utils;

Objects::Objects() {

}

bool Objects::containsComponentWithIdentifier(shared_ptr<string> identifier) {

    return classIdentifierToComponentMap.find(*identifier) != classIdentifierToComponentMap.end();

}

shared_ptr<Objects> Objects::copy() {

    auto copy = make_shared<Objects>();

    for (auto object : objects) {
        copy->addObject(object);
    }

    return copy;

}

void Objects::addObject(shared_ptr<Object> object) {

    if (object->getClassIdentifier().get() == nullptr) {

        throwRuntimeException(string("Trying to add object with classIdentifier = nullptr"));

    }

    if (object->getInstanceIdentifier().get() == nullptr) {

        string errorString = "Trying to add object with instanceIdentifier = nullptr; With class identifier: ";
        errorString += *object->getClassIdentifier().get();

        throwRuntimeException(errorString);

    }

    auto objectInstanceIdentifierString = *object->getInstanceIdentifier().get();

    objects.push_back(object);
    uuidToObject[object->uuid] = object;
    instanceIdentifierToObjectMap[objectInstanceIdentifierString] = object;

    shared_ptr<string> classIdentifier = object->getClassIdentifier();

    if (classIdentifier.get() == nullptr) {

        cout << "FSCComponents: cannot add component - component class identifier is nullptr. Quit.";

        exit(1);
    }

    auto classIdentifierString = *classIdentifier.get();

    if (classIdentifierToComponentMap.find(classIdentifierString) != classIdentifierToComponentMap.end()) {

        auto objects = classIdentifierToComponentMap[classIdentifierString];
        objects.push_back(object);

    }
    else
    {
        vector<shared_ptr<Object> > objects;
        objects.push_back(object);

        classIdentifierToComponentMap[classIdentifierString] = objects;
    }
}

void Objects::removeObject(shared_ptr<Object> object) {

    if (object.get() == nullptr)
    {
        throwRuntimeException(string("Trying to remove nullptr object"));
    }

    auto index = 0;

    for (auto item : objects) {

        if (item->uuid.compare(object->uuid) == 0) {

            shared_ptr<string> classIdentifier = object->getClassIdentifier();
            classIdentifierToComponentMap.erase(*classIdentifier);
            objects.erase(objects.begin() + index);
            return;
        }

        index += 1;
    }

}

shared_ptr<Object> Objects::objectWithUUID(string uuid) {

    return uuidToObject[uuid];

}

shared_ptr<Object> Objects::objectAtIndex(unsigned int index) {
    if (index >= objects.size()) {
        return shared_ptr<Object>();
    }

    return objects[index];
}

int Objects::size() {
    return objects.size();
}

void Objects::removeObjectAtIndex(unsigned int index) {
    if (index < objects.size()) {
        auto objectToRemove = objects[index];

        shared_ptr<string> classIdentifier = objectToRemove->getClassIdentifier();
        classIdentifierToComponentMap.erase(*classIdentifier);

        objects.erase(objects.begin() + index);
    }
}

void Objects::removeAllObjects() {

    objects.clear();
    uuidToObject.clear();
    classIdentifierToComponentMap.clear();
    instanceIdentifierToObjectMap.clear();

}

void Objects::removeObjectWithClassIdentifier(shared_ptr<string> classIdentifier) {

    auto objectIndex = -1;

    for (auto object : objects) {

        objectIndex++;

        if (object->getClassIdentifier()->compare(*classIdentifier) == 0) {
            removeObjectAtIndex(objectIndex);
            return;
        }
    }

}

vector<shared_ptr<Object> > Objects::objectsWithClassIdentifier(shared_ptr<string> identifier) {

    auto classIdentifierString = *identifier.get();

    if (classIdentifierToComponentMap.find(classIdentifierString) != classIdentifierToComponentMap.end()) {

        auto component = classIdentifierToComponentMap[classIdentifierString];

        return component;

    }
    else {

        vector<shared_ptr<Object> > emptyVector;

        return emptyVector;

    }
}

shared_ptr<Object> Objects::objectWithInstanceIdentifier(shared_ptr<string> instanceIdentifier) {

    auto instanceIdentifierString = *instanceIdentifier.get();

    if (instanceIdentifierToObjectMap.find(instanceIdentifierString) != instanceIdentifierToObjectMap.end()) {

        auto object = instanceIdentifierToObjectMap[instanceIdentifierString];

        return object;

    }
    else {

        return shared_ptr<Object>();

    }
}

Objects::~Objects() {
    // TODO Auto-generated destructor stub
}
