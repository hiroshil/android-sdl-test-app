#ifndef FSBH_MUSIC_H_
#define FSBH_MUSIC_H_

#include <FlameSteelBattleHorn/Playable.h>

#include <memory>
#include <string>

#ifndef __EMSCRIPTEN__
#include <SDL2/SDL_mixer.h>
#endif

using namespace std;

namespace FlameSteelBattleHorn
{

class Music: public Playable
{

public:
    Music(shared_ptr<string> path);
    void play();
    void stop();
    virtual ~Music();

private:
#ifndef __EMSCRIPTEN__
    Mix_Music *music = nullptr;
#else
    shared_ptr<string> path;
#endif

};

}

#endif