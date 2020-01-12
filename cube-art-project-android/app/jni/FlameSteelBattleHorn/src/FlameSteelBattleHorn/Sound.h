#ifndef FSBH_SOUND_H_
#define FSBH_SOUND_H_

#include <FlameSteelBattleHorn/Playable.h>

#include <memory>
#include <string>

#ifndef __EMSCRIPTEN__
#include <SDL2/SDL_mixer.h>
#endif

using namespace std;
using namespace FlameSteelBattleHorn;

namespace FlameSteelBattleHorn
{

class Sound: public Playable
{

public:
    static void initializeSoundSystem();
    Sound(shared_ptr<string> path);
    void play();
    void stop();
    virtual ~Sound();

private:
#ifndef __EMSCRIPTEN__
    Mix_Chunk *chunk = nullptr;
#else
    shared_ptr<string> path;
#endif

};

}

#endif