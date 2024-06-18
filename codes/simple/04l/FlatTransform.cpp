#include "FlatTransform.h"

FlatTransform::FlatTransform( const FlatVector & position, float angle )
{
    this->positionX = position.x;
    this->positionY = position.y;
    this->sina = std::sin( angle );
    this->cosa = std::cos( angle );
}

FlatTransform::FlatTransform( float x, float y, float angle )
{
    this->positionX = x;
    this->positionY = y;
    this->sina = std::sin( angle );
    this->cosa = std::cos( angle );
}
