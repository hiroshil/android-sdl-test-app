/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEGTObjectsController.h
 * Author: demensdeum
 *
 * Created on April 30, 2017, 8:17 PM
 */

#ifndef FSEGTOBJECTSCONTROLLER_H
#define FSEGTOBJECTSCONTROLLER_H

#include <memory>

#include <FlameSteelCore/Objects.h>
#include <FlameSteelEngineGameToolkit/Controllers/FSEGTObjectContextDelegate.h>

using namespace std;
using namespace FlameSteelCore;

class FSEGTObjectsContext : public std::enable_shared_from_this<FSEGTObjectsContext>
{
public:
    FSEGTObjectsContext();
    virtual ~FSEGTObjectsContext();

    shared_ptr<Object> objectWithInstanceIdentifier(shared_ptr<string> instanceIdentifier);

    void setObjects(shared_ptr<Objects> objects);

    void removeAllObjects();

    void addObject(shared_ptr<Object> object);
    void updateObject(shared_ptr<Object> object);
    void removeObject(shared_ptr<Object> object);

    void subscribe(shared_ptr<FSEGTObjectContextDelegate> delegate);
    void unsubscribe(shared_ptr<FSEGTObjectContextDelegate> delegate);

private:

    vector<shared_ptr<FSEGTObjectContextDelegate> > subscribers;
    shared_ptr<Objects> objects;

};

#endif /* FSEGTOBJECTSCONTROLLER_H */

