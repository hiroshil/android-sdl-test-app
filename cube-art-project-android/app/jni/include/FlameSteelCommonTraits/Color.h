#ifndef FLAMESTEELCOMMONTRAITSCOLOR_H_
#define FLAMESTEELCOMMONTRAITSCOLOR_H_

#include <cstdint>
#include <memory>

using namespace std;

namespace FlameSteelEngine {
namespace CommonTraits {

class Color {

public:
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;

	bool isEqualTo(shared_ptr<Color> color);
	string asString();

};
};
};

#endif