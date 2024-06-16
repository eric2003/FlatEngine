#pragma once
#include <cmath>

class FlatVector {
public:
    FlatVector() = default;
    ~FlatVector() = default;
    FlatVector( float x, float y) {
        this->x = x;
        this->y = y;
    }
public:
    FlatVector & operator +=( const FlatVector & rhs ) {
        this->x += rhs.x;
        this->y += rhs.y;
        return * this;
    }
    FlatVector & operator -=( const FlatVector & rhs ) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return * this;
    }
    FlatVector & operator +=( const float & value ) {
        this->x += value;
        this->y += value;
        return * this;
    }

    FlatVector & operator -=( const float & value ) {
        this->x -= value;
        this->y -= value;
        return * this;
    }

    FlatVector & operator *=( const float & value ) {
        this->x *= value;
        this->y *= value;
        return * this;
    }

    FlatVector & operator /=( const float & value ) {
        this->x /= value;
        this->y /= value;
        return * this;
    }

    FlatVector operator *( const float & value ) const {
        return FlatVector(this->x*value,  this->y * value);
    }

    float length() {
        return std::sqrt( x * x + y * y );
    }

    FlatVector normalize() {
        float len = this->length();
        if ( len == 0 ) {
            return FlatVector( 0, 0 );
        }
        return FlatVector( this->x/len,  this->y/len );
    }

public:
    float x = 0;
    float y = 0;
};