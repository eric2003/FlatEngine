#include "FlatUtil.h"

FlatVector Transform(const FlatVector &v, const FlatTransform &transform)
{
    float rx = transform.cosa * v.x - transform.sina * v.y;
    float ry = transform.sina * v.x + transform.cosa * v.y;

    float tx = rx + transform.positionX;
    float ty = ry + transform.positionY;
    FlatVector result(tx, ty);
    return result;
}

