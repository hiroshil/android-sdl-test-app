#include "FSEGTStick.h"

FSEGTStick::FSEGTStick(int x, int y)
{

    this->setClassIdentifier(make_shared<string>(uuid));
    this->setInstanceIdentifier(make_shared<string>(uuid));

    this->x = x;
    this->y = y;

}