#include "FSEGTTouch.h"

FSEGTTouch::FSEGTTouch(shared_ptr<string> uuid, int x, int y)
{

    this->x = x;
    this->y = y;

    this->setClassIdentifier(uuid);
    this->setInstanceIdentifier(uuid);

};