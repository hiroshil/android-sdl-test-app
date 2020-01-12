#ifndef FSEGTRECTANGLE_H_
#define FSEGTRECTANGLE_H_

#include <FlameSteelCore/Object.h>

using namespace FlameSteelCore;

class FSEGTRectangle: public Object
{

public:

    FSEGTRectangle(float x, float y, float width, float height);

    float x();
    float y();
    float width();
    float height();

    void setX(float x);
    void setY(float y);
    void setWidth(float width);
    void setHeight(float height);

    bool isPointXYInside(float x, float y, float rectangleDiffX, float rectangleDiffY);

};

#endif