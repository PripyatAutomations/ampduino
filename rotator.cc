//
// Support for antenna rotors for rotation in up to 3 axis.
//
// X: Cardinal (N/E/S/W) direction we are facing
// Y: Vertical azimuth
// Z: Rotate the antenna on the feed-end
//
// This will probably not be worked on much until later Summer 2022.

#include "ampduino.h"

#if	defined(CF_ROTORS)

// defined(CF_ROTORS)

Coordinate *ad_Rotator::GetPosition(void) {
    return &this->current;
}

bool ad_Rotator::SetPosition(Coordinate *c) {
    Coordinate old;

    if (c->x < this->min.x || c->x > this->max.x)
       return false;
    if (c->y < this->min.y || c->y > this->max.y)
       return false;
    if (c->z < this->min.z || c->z > this->max.z)
       return false;

    // if we made it here, it's probably valid, save old values
    old.x = this->current.x;
    old.y = this->current.y;
    old.z = this->current.z;

    // then assign new ones
    this->current.x = c->x;
    this->current.y = c->y;
    this->current.z = c->z;

    // XXX: and command the steppers!
    return true;
}

bool ad_Rotator::SetPosition(unsigned int x, unsigned int y, unsigned int z) {
    Coordinate c;
    bool ret;

    c.x = x;
    c.y = y;
    c.z = z;

    ret = this->SetPosition(&c);

    return ret;
}

#endif
