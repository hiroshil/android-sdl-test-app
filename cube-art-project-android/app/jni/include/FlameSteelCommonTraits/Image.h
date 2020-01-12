#ifndef FLAMESTEELCOMMONTRAITSIMAGE_H_
#define FLAMESTEELCOMMONTRAITSIMAGE_H_

#include <cstdint>
#include <memory>
#include <vector>

using namespace std;

namespace FlameSteelEngine {
namespace CommonTraits {

class Color;

};
};

using namespace FlameSteelEngine::CommonTraits;

namespace FlameSteelEngine {
namespace CommonTraits {

class Image {

public:
    Image(int width, int height);
    void setColorAtXY(shared_ptr<Color> color, int x, int y);
    shared_ptr<Color> getColorAtXY(int x, int y);

    int getWidth();
    int getHeight();

private:
    vector<shared_ptr<Color>> colors;
    int width;
    int height;

};

};
};

#endif