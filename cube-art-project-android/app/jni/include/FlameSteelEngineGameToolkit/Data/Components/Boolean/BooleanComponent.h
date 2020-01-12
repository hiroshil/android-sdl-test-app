#ifndef FSEGTBOOLEANCOMPONENT_DEFINED_H
#define FSEGTBOOLEANCOMPONENT_DEFINED_H 1

#include <FlameSteelCore/Object.h>

using namespace FlameSteelCore;

namespace FlameSteelEngine
{
namespace GameToolkit
{
class BooleanComponent: public Object
{

public:
    bool booleanValue = false;

};
};
};

#endif