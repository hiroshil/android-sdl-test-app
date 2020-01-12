/*
 * Objects.h
 *
 *  Created on: Jul 31, 2016
 *      Author: demensdeum
 */

#ifndef FSCOBJECTS_H_
#define FSCOBJECTS_H_

#include "Object.h"

#include <vector>
#include <memory>
#include <string>
#include <map>

using namespace std;
using namespace FlameSteelCore;

namespace FlameSteelCore {

class Objects {
public:
    Objects();

    void addObject(shared_ptr<Object> object);
    void removeObjectAtIndex(unsigned int index);
    void removeAllObjects();

    shared_ptr<Object> objectWithUUID(string uuid);
    shared_ptr<Object> objectAtIndex(unsigned int index);
    vector<shared_ptr<Object> > objectsWithClassIdentifier(shared_ptr<string> identifier);
    shared_ptr<Object> objectWithInstanceIdentifier(shared_ptr<string> instanceIdentifier);

    void removeObject(shared_ptr<Object> object);
    void removeObjectWithClassIdentifier(shared_ptr<string> classIdentifier);

    bool containsComponentWithIdentifier(shared_ptr<string> identifier);

    int size();

    shared_ptr<Objects> copy();

    virtual ~Objects();

private:
    vector <shared_ptr<Object> > objects;

    map <string, shared_ptr<Object> > uuidToObject;
    map<string, vector<shared_ptr<Object> > > classIdentifierToComponentMap;
    map<string, shared_ptr<Object> > instanceIdentifierToObjectMap;

};
};

#endif /* FSCOBJECTS_H_ */
