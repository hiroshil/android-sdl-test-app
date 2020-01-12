/*
 * FSCController.h
 *
 *  Created on: Jul 10, 2016
 *      Author: demensdeum
 */

#ifndef FSCCONTROLLER_H_
#define FSCCONTROLLER_H_

#include "Object.h"

using namespace FlameSteelCore;

namespace FlameSteelCore  {

class Controller : public Object  {
public:
    Controller();
    virtual ~Controller();
    virtual void step();
};

};

#endif /* FSCCONTROLLER_H_ */
