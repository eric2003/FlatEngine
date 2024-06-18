#pragma once
#include <cmath>

class FlatVector
{
public:
    FlatVector() = default;
    ~FlatVector() = default;
    FlatVector( float x, float y) {
        this->x = x;
        this->y = y;
    }
public:
    static FlatVector Zero()
    {
        return FlatVector(0.0f, 0.0f);
    }

    friend FlatVector operator + (const FlatVector& a, const FlatVector& b)
    {
        FlatVector result(a.x+b.x,a.y+b.y);
        return result;
    }

    friend FlatVector operator - (const FlatVector& a, const FlatVector& b)
    {
        FlatVector result(a.x-b.x,a.y-b.y);
        return result;
    }

    friend FlatVector operator * (const FlatVector& a, const float & value)
    {
        FlatVector result(a.x*value,a.y*value);
        return result;
    }

    friend FlatVector operator * (const float & value, const FlatVector& a)
    {
        FlatVector result(a.x*value,a.y*value);
        return result;
    }

    FlatVector operator -() {
        FlatVector result(- this->x,- this->y);
        return result;
    }

    friend FlatVector operator / (const FlatVector& a, const float & value)
    {
        FlatVector result(a.x/value,a.y/value);
        return result;
    }

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

    float length()
    {
        return std::sqrt( x * x + y * y );
    }

    void normalize()
    {
        float len = this->length();
        if ( len == 0 ) {
            this->x = 0;
            this->y = 0;
        }
        this->x /= len;
        this->y /= len;
    }
public:
    float x = 0;
    float y = 0;
};
