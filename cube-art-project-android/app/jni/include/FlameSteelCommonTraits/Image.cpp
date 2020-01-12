#include "Image.h"
#include "Color.h"
#include "FlameSteelCore/FSCUtils.h"

using namespace FlameSteelCore::Utils;

Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    auto size = width * height;
    for (auto i = 0; i < size; i++) {
        auto color = make_shared<Color>(0, 0, 0, 255);
        colors.push_back(color);
    }
}

void Image::setColorAtXY(shared_ptr<Color> color, int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
	string errorString = string("Can't set color outside of image size");
	errorString += to_string(x);
	errorString += " ";
	errorString += to_string(y);
	throwRuntimeException(errorString);
    }

    int index = (y * width) + x;
    colors[index] = color;
}

shared_ptr<Color> Image::getColorAtXY(int x, int y) {

    if (x < 0 || y < 0 || x >= width || y >= height) {
	throwRuntimeException("Can't get color outside of image size");
    }

    int index = (y * width) + x;
    return colors[index];

};

int Image::getWidth() {
    return width;
};

int Image::getHeight() {
    return height;
};
