#include <FlameSteelBattleHorn/Sound.h>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace FlameSteelCore::Utils;
using namespace FlameSteelBattleHorn;

void Sound::initializeSoundSystem()
{

#ifndef __EMSCRIPTEN__

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1 )
    {
        throwRuntimeException(string("Can't initialize sound system"));
    }

    int flags = MIX_INIT_OGG;
    int initted = Mix_Init(flags);

    //cout << flags << endl;
    //cout << initted << endl;

    if ((initted & flags) != flags)
    {
        printf("Mix_Init: Failed to init required ogg and mod support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        throwRuntimeException(string("Can't initialize SDL_Mixer properly"));
    }
    else
    {
        //cout << "SDL_MIXER initialized correctly" << endl;
    }

#endif
}

Sound::Sound(shared_ptr<string> path)
{

#ifndef __EMSCRIPTEN__

    chunk = Mix_LoadWAV(path->c_str());

    if (chunk == nullptr)
    {
        //cout << "Can't load sound " << Mix_GetError() << endl;
        throwRuntimeException(string("Can't load sound"));
    }
#else

    this->path = path;

#endif
}

void Sound::play()
{

#ifndef __EMSCRIPTEN__
    if (chunk)
    {
        if (Mix_PlayChannel(-1, chunk, 0)==-1)
        {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
    }
#else
    if (path.get() != nullptr)
    {

        //cout << "play sound through javascript" << endl;

        EM_ASM_(
        {

            var audioPath = UTF8ToString($0);
            audioPath += ".mp3";

            var audio = new Audio(audioPath);
            audio.play();

        }, path->c_str());
    }
    else
    {
        //cout << "can't play sound - path is null" << endl;
    }
#endif
}

void Sound::stop()
{

}

Sound::~Sound()
{
#ifndef __EMSCRIPTEN__
    if (chunk)
    {
        Mix_FreeChunk(chunk);
    }
#endif
}