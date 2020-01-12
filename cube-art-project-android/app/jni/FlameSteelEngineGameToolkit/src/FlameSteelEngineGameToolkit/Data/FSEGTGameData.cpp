/*
 * FSEGTGameData.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: demensdeum
 */

#include "FSEGTGameData.h"
#include <cstddef>

#include <FlameSteelEngineGameToolkit/Data/Components/Vector/FSEGTVector.h>
#include "FlameSteelEngineGameToolkit/Const/FSEGTConst.h"

#include <memory>

using namespace std;

FSEGTGameData::FSEGTGameData()
{

    gameObjects = make_shared<Objects>();

}

shared_ptr<Objects> FSEGTGameData::getGameObjects()
{
    return this->gameObjects;
}

FSEGTGameData::~FSEGTGameData()
{
    // TODO Auto-generated destructor stub
}
