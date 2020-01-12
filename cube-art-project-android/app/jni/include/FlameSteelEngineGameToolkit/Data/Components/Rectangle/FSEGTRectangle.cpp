#include "FSEGTRectangle.h"

#include <FlameSteelEngineGameToolkit/Data/Components/Integer/FSEGTIntegerComponent.h>
#include <FlameSteelEngineGameToolkit/Data/Components/Rectangle/FSEGTRectangle.h>

using namespace FlameSteelCore;

FSEGTRectangle::FSEGTRectangle(float x, float y, float width, float height)
{

    auto componentX = make_shared<FSEGTIntegerComponent>(x);
    componentX->setClassIdentifier(make_shared<string>("x"));
    componentX->setInstanceIdentifier(make_shared<string>("x"));

    auto componentY = make_shared<FSEGTIntegerComponent>(y);
    componentY->setClassIdentifier(make_shared<string>("y"));
    componentY->setInstanceIdentifier(make_shared<string>("y"));

    auto componentWidth = make_shared<FSEGTIntegerComponent>(width);
    componentWidth->setClassIdentifier(make_shared<string>("width"));
    componentWidth->setInstanceIdentifier(make_shared<string>("width"));

    auto componentHeight = make_shared<FSEGTIntegerComponent>(height);
    componentHeight->setClassIdentifier(make_shared<string>("height"));
    componentHeight->setInstanceIdentifier(make_shared<string>("height"));

    this->addComponent(componentX);
    this->addComponent(componentY);
    this->addComponent(componentWidth);
    this->addComponent(componentHeight);

}

float FSEGTRectangle::x()
{
    auto componentX = static_pointer_cast<FSEGTIntegerComponent>(getComponent(make_shared<string>("x")));
    return componentX->value;
}

float FSEGTRectangle::y()
{
    auto componentX = static_pointer_cast<FSEGTIntegerComponent>(getComponent(make_shared<string>("y")));
    return componentX->value;
}

float FSEGTRectangle::width()
{
    auto componentX = static_pointer_cast<FSEGTIntegerComponent>(getComponent(make_shared<string>("width")));
    return componentX->value;
}

float FSEGTRectangle::height()
{
    auto componentX = static_pointer_cast<FSEGTIntegerComponent>(getComponent(make_shared<string>("height")));
    return componentX->value;
}

void FSEGTRectangle::setX(float x)
{
    auto componentX = static_pointer_cast<FSEGTIntegerComponent>(getComponent(make_shared<string>("x")));
    componentX->value = x;
}

void FSEGTRectangle::setY(float y)
{
    auto componentY = static_pointer_cast<FSEGTIntegerComponent>(getComponent(make_shared<string>("x")));
    componentY->value = y;
}

void FSEGTRectangle::setWidth(float width)
{
    auto componentWidth = static_pointer_cast<FSEGTIntegerComponent>(getComponent(make_shared<string>("width")));
    componentWidth->value = width;
}

void FSEGTRectangle::setHeight(float height)
{
    auto componentHeight = static_pointer_cast<FSEGTIntegerComponent>(getComponent(make_shared<string>("height")));
    componentHeight->value = height;
}

bool FSEGTRectangle::isPointXYInside(float x, float y,
                                     float rectangleDiffX, float rectangleDiffY)
{

    auto rectangleX = this->x() + rectangleDiffX;
    auto rectangleY = this->y() + rectangleDiffY;

    auto rectangleXX = rectangleX + width();
    auto rectangleYY = rectangleY + height();

    if (x >= this->x() && x <= rectangleXX)
    {
        if (y >= this->y() && y <= rectangleYY)
        {
            return true;
        }
    }

    return false;
}
