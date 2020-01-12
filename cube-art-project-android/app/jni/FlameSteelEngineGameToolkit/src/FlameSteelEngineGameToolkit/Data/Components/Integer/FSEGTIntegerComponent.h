/*
 * FSEGTIntegerComponent.h
 *
 *  Created on: Sep 10, 2016
 *      Author: demensdeum
 */

#ifndef DATA_COMPONENTS_INTEGER_FSEGTINTEGERCOMPONENT_H_
#define DATA_COMPONENTS_INTEGER_FSEGTINTEGERCOMPONENT_H_

#include <FlameSteelCore/Object.h>

using namespace FlameSteelCore;

class FSEGTIntegerComponent: public Object
{
public:
    FSEGTIntegerComponent(int value);

    int value;

    virtual ~FSEGTIntegerComponent();
};

#endif /* DATA_COMPONENTS_INTEGER_FSEGTINTEGERCOMPONENT_H_ */
