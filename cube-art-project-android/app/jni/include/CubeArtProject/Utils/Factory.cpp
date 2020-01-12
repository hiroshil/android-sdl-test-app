#include "Factory.h"
#include <FlameSteelCore/FSCUtils.h>
#include <FlameSteelCommonTraits/Color.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;
using namespace CubeArtProject;
using namespace FlameSteelCore::Utils;
using namespace FlameSteelCommonTraits;

uint32_t getPixel(SDL_Surface *surface, int x, int y) //From SDL doc
{
  int bpp = surface->format->BytesPerPixel;
  /* p is the address to the pixel we want to retrieve */
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  switch(bpp)
  {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;

  default:
    return 0;
  }
}

shared_ptr<Image> Factory::imageFromPath(shared_ptr<Path> path) {
	return Factory::screenshotFromPath(path);
};

shared_ptr<Screenshot> Factory::screenshotFromPath(shared_ptr<Path> path) {

	if (path.get() == nullptr) {
		throwRuntimeException("Can't load screenshot/image from path, because Path object is null");
	}

	auto surface = IMG_Load(path->path.c_str());

	if (surface == nullptr) {
		string errorText = "No image at path: ";
		errorText += path->path;
		throwRuntimeException(string(errorText));
	}

	auto width = surface->w;
	auto height = surface->h;

    auto screenshot = make_shared<Screenshot>(width, height);

    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {

		uint32_t pixel = getPixel(surface, x, y);

		uint8_t redColorByte = 0;
		uint8_t greenColorByte = 0;
		uint8_t blueColorByte = 0;

		SDL_GetRGB(pixel, surface->format, &redColorByte, &greenColorByte, &blueColorByte);

		/*if (redColorByte != 0) {
			string redColorPositionText = "red color at x:";
			redColorPositionText += to_string(x);
			redColorPositionText += " ";
			redColorPositionText += to_string(y);
			redColorPositionText += "-";
			redColorPositionText += to_string(redColorByte);
			throwRuntimeException(redColorPositionText);
		}*/

            auto color = make_shared<Color>(redColorByte, greenColorByte, blueColorByte, 255);
            screenshot->setColorAtXY(color, x, y);
        }
    }

	free(surface);

	/*if (screenshot->getColorAtXY(512, 116)->red != 255) {
			throwRuntimeException("bug");		
	}
	else {
		cout << "Factory is ok - there is red color" << endl;
	}*/

	return screenshot;
};