/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GameMap.h
 * Author: demensdeum
 *
 * Created on April 25, 2017, 9:18 AM
 */

#ifndef FSEGTGAMEMAP_H
#define FSEGTGAMEMAP_H

#include <memory>
#include <vector>

#include <FlameSteelCore/Object.h>

using namespace std;
using namespace FlameSteelCore;

namespace FlameSteelEngine
{
namespace GameToolkit
{

const int kGameMapMaximalWidth = 4096;
const int kGameMapMaximalHeight = 4096;

class GameMap: public Object
{
public:
    GameMap(int width, int height);
    GameMap(const GameMap& orig);
    virtual ~GameMap();

    int width;
    int height;

    shared_ptr<Object> getTileAtXY(int tileX, int tileY);
    void setTileAtXY(int tileIndex, int tileX, int tileY);

    void addTile(shared_ptr<Object> tile);

    int getTileIndexAtXY(int tileX, int tileY);

private:

    int map[kGameMapMaximalWidth][kGameMapMaximalHeight];

    vector<shared_ptr<Object> > tiles;

};

}
}

#endif /* FSEGTGAMEMAP_H */

