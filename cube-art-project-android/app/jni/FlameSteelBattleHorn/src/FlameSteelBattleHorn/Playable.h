#ifndef FSBH_SOUND_SYSTEM_PLAYABLE_H
#define FSBH_SOUND_SYSTEM_PLAYABLE_H

#include <stdexcept>
#include <FlameSteelCore/FSCUtils.h>

using namespace std;
using namespace FlameSteelCore::Utils;

namespace FlameSteelBattleHorn
{
class Playable
{

public:
    virtual void play()
    {
        throwRuntimeException(string("Call to not overriden method play, playable abstract class"));
    };
    virtual void stop()
    {
        throwRuntimeException(string("Call to not overriden method stop, playable abstract class"));
    };

};
};

#endif