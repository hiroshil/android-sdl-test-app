#ifndef FSEGTSTICK_H_
#define FSEGTSTICK_H_

#include <FlameSteelCore/Object.h>

using namespace FlameSteelCore;

class FSEGTStick: public Object
{

public:
    FSEGTStick(int x, int y);
    int x = 0;
    int y = 0;

};

#endif