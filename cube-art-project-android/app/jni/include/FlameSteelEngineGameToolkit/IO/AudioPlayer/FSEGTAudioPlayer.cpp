/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEGTAudioPlayer.cpp
 * Author: demensdeum
 *
 * Created on March 26, 2017, 9:11 AM
 */

#include <FlameSteelBattleHorn/Sound.h>
#include <FlameSteelBattleHorn/Music.h>
#include "FSEGTAudioPlayer.h"
#include <json/json.hpp>
#include <iostream>
#include <fstream>

using namespace nlohmann;

FSEGTAudioPlayer::FSEGTAudioPlayer()
{

    Sound::initializeSoundSystem();

}

FSEGTAudioPlayer::FSEGTAudioPlayer(const FSEGTAudioPlayer& )
{
}

void FSEGTAudioPlayer::play(shared_ptr<string> soundName)
{

    shared_ptr<Playable> sound = nullptr;

    if (soundsMap.find(*soundName) == soundsMap.end())
    {
        loadAudioJSON(soundName);
    }

    sound = soundsMap[*soundName];
    sound->play();
}

void FSEGTAudioPlayer::stop(shared_ptr<string> soundName)
{

    if (soundsMap.find(*soundName) == soundsMap.end())
    {
        return;
    }

    auto sound = soundsMap[*soundName];
    sound->stop();
}

void FSEGTAudioPlayer::loadAudioJSON(shared_ptr<string> path)
{

    std::ifstream fileInput(path->c_str());
    json fileJson;
    fileInput >> fileJson;

    auto length = fileJson["length"];
    string filePathRaw = fileJson["path"];
    auto filePath = make_shared<string>(filePathRaw);

    //cout << length << endl;

    auto playable = shared_ptr<Playable>();

    if (length > 60)
    {
        playable = make_shared<Music>(filePath);
    }
    else
    {
        playable = make_shared<Sound>(filePath);
    }

    soundsMap[*path] = playable;

}

FSEGTAudioPlayer::~FSEGTAudioPlayer()
{
}