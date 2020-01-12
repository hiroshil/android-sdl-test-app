#include <FlameSteelBattleHorn/Music.h>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace FlameSteelBattleHorn;
using namespace FlameSteelCore::Utils;

Music::Music(shared_ptr<string> path)
{

#ifndef __EMSCRIPTEN__

    music = Mix_LoadMUS(path->c_str());

    if (music == nullptr)
    {
        //cout << "Can't load music " << Mix_GetError() << endl;
        throwRuntimeException(string("Can't load music"));
    }

#else

    this->path = path;

#endif
}

void Music::play()
{

#ifndef __EMSCRIPTEN__
    if (music)
    {
        if (Mix_PlayMusic(music, -1) == -1)
        {
            throwRuntimeException(string("Can't play music"));
        }
    }
    else
    {
        throwRuntimeException(string("Can't play music - music is null"));
    }
#else
    if (path.get() != nullptr)
    {

        //cout << "play sound through javascript" << endl;

        EM_ASM_(
        {

            var audioPath = UTF8ToString($0);
            audioPath += ".mp3";

            FlameSteelBattleHorn_music_global = new Audio(audioPath);
            FlameSteelBattleHorn_music_global.loop = true;
            FlameSteelBattleHorn_music_global.play();

        }, path->c_str());
    }
    else
    {
        //cout << "can't play sound - path is null" << endl;
    }
#endif
}

void Music::stop()
{

#ifndef __EMSCRIPTEN__

#else
    if (path.get() != nullptr)
    {

        //cout << "play sound through javascript" << endl;

        EM_ASM(
        {

            if (FlameSteelBattleHorn_music_global != null)
            {
                FlameSteelBattleHorn_music_global.pause();
            }

        });
    }
    else
    {
        //cout << "can't play sound - path is null" << endl;
    }
#endif

}

Music::~Music()
{
#ifndef __EMSCRIPTEN__
    if (music)
    {
        Mix_FreeMusic(music);
    }
#endif
}