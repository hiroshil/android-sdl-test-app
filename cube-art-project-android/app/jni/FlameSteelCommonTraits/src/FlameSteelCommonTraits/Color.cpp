#include "Color.h"
#include <FlameSteelCore/FSCUtils.h>

using namespace FlameSteelCore::Utils;
using namespace FlameSteelEngine::CommonTraits;

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {

    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;

};

bool Color::isEqualTo(shared_ptr<Color> color) {
	if (color.get() == nullptr) {
		throwRuntimeException(string("Can't check colors equality, rhs color is nullptr"));
	}
	if (red != color->red || green != color->green || blue != color->blue || alpha != color->alpha) {
		return false;
	}
	return true;
};

string Color::asString() {
	string output = "";
	output += "red: ";
	output += to_string(red);
	output += " green: ";
	output += to_string(green);
	output += " blue: ";
	output += to_string(blue);
	output += " alpha: ";
	output += to_string(alpha);
	return output;
};