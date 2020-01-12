#ifndef FLAMESTEELENGINEGAMETOOLKIT_DEFINED
#define FLAMESTEELENGINEGAMETOOLKIT_DEFINED

#include <memory>
#include <map>

using namespace std;

namespace FlameSteelCore
{
class Object;
class Objects;
};


using namespace FlameSteelCore;

namespace FlameSteelEngine
{
namespace GameToolkit
{

class ObjectsMap
{

public:
    ObjectsMap();

    void handleObject(shared_ptr<Object> object);
    void removeObject(shared_ptr<Object> object);
    void removeAllObjects();

    shared_ptr<Objects> objectsAtXY(int x, int y);

private:
    string tileIndexAtXY(int x, int y);
    void addObjectToTileIndex(shared_ptr<Object> object, string tileIndex);
    void removeObjectAtTileIndex(shared_ptr<Object> object, string tileIndex);

    map<string, shared_ptr<Objects> > tileIndexToObjects;
    map<string, string> objectUUIDToTileIndex;
};
};
};

#endif