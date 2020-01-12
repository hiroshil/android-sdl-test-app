/*
 * FSEGTGameData.h
 *
 *  Created on: Jul 31, 2016
 *      Author: demensdeum
 */

#ifndef FSEGTGAMEDATA_H_
#define FSEGTGAMEDATA_H_

#include <map>
#include <FlameSteelCore/Objects.h>
#include <FlameSteelEngineGameToolkit/Data/Components/GameMap/GameMap.h>

using namespace std;
using namespace FlameSteelCore;
using namespace FlameSteelEngine::GameToolkit;

class FSEGTGameData: public Object
{
public:
    FSEGTGameData();
    virtual ~FSEGTGameData();

public:
    void setGameObjects(shared_ptr<Objects> gameObjects);

    shared_ptr<Objects> getGameObjects();

    shared_ptr<GameMap> gameMap;

private:
    shared_ptr<Objects> gameObjects; // scene independent game objects
};

#endif /* FSEGTGAMEDATA_H_ */
