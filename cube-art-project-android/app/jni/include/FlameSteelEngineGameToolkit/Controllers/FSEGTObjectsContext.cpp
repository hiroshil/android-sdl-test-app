/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEGTObjectsController.cpp
 * Author: demensdeum
 *
 * Created on April 30, 2017, 8:17 PM
 */

#include "FSEGTObjectsContext.h"
#include <FlameSteelCore/FSCUtils.h>

using namespace FlameSteelCore::Utils;

FSEGTObjectsContext::FSEGTObjectsContext()
{

    objects = make_shared<Objects>();

}

shared_ptr<Object> FSEGTObjectsContext::objectWithInstanceIdentifier(shared_ptr<string> instanceIdentifier)
{

    return objects->objectWithInstanceIdentifier(instanceIdentifier);

}

void FSEGTObjectsContext::setObjects(shared_ptr<Objects> objects)
{

    this->objects = objects;

}

void FSEGTObjectsContext::removeAllObjects()
{

    objects->removeAllObjects();

    for (auto subscriber : subscribers)
    {

        subscriber->objectsContextAllObjectsRemoved(shared_from_this());

    }
}

void FSEGTObjectsContext::addObject(shared_ptr<Object> object)
{

	if (objects.get() == nullptr) {
		throwRuntimeException(string("objects object is null"));
	}

    objects->addObject(object);

    for (auto subscriber : subscribers)
    {

        subscriber->objectsContextObjectAdded(shared_from_this(), object);

    }
}

void FSEGTObjectsContext::updateObject(shared_ptr<Object> object)
{

    for (auto subscriber : subscribers)
    {

        subscriber->objectsContextObjectUpdate(shared_from_this(), object);

    }
}

void FSEGTObjectsContext::removeObject(shared_ptr<Object> object)
{

    objects->removeObject(object);

    for (auto subscriber : subscribers)
    {

        subscriber->objectsContextObjectRemoved(shared_from_this(), object);

    }
}

void FSEGTObjectsContext::subscribe(shared_ptr<FSEGTObjectContextDelegate> delegate)
{

    subscribers.push_back(delegate);

}

void FSEGTObjectsContext::unsubscribe(shared_ptr<FSEGTObjectContextDelegate> delegate)
{

    for (size_t i = 0; i < subscribers.size(); i++)
    {

        auto subscriber = subscribers.at(i);

        if (subscriber.get() == delegate.get())
        {

            subscribers.erase(subscribers.begin(),subscribers.begin() + 1);

        }
    }
}

FSEGTObjectsContext::~FSEGTObjectsContext()
{
}
