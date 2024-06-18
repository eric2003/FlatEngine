#pragma once
#include "FlatVector.h"
#include "FlatTransform.h"
#include "FlatUtil.h"
#include "FlatMath.h"
#include <vector>

enum class ShapeType
{
    Circle = 0,
    Box = 1
};

class FlatBody
{
public:
    FlatBody(FlatVector position,float width, float height, ShapeType shapeType) 
    {
        this->position = position;
        this->width = width;
        this->height = height;
        this->shapeType = shapeType;
        this->rotation = 0.0f;
        this->transformUpdateRequired = true;
        if ( shapeType == ShapeType::Box )
        {
            this->CreateBoxVertices(width, height);
            this->GetTransformedVertices();
        }
    }
    ~FlatBody() {}

    void Move(const FlatVector &amount)
    {
        this->position += amount;
    }

    void Rotate( float rot_angle )
    {
        this->rotation += rot_angle;
        this->transformUpdateRequired = true;
    }

    void CreateBoxVertices(float width, float height)
    {
        float left = -width / 2.0f;
        float right = left + width;
        float bottom = -height / 2.0f;
        float top = bottom + height;

        this->vertices.resize( 4 );
        this->vertices[0] = FlatVector(left, top);
        this->vertices[1] = FlatVector(right, top);
        this->vertices[2] = FlatVector(right, bottom);
        this->vertices[3] = FlatVector(left, bottom);
    }

    void GetTransformedVertices()
    {
        //if ( this->transformUpdateRequired )
        {
            FlatTransform transform(this->position, this->rotation);
            this->transformedVertices.resize( this->vertices.size() );

            for ( int i = 0; i < this->transformedVertices.size(); ++ i )
            {
                FlatVector v = this->vertices[i];
                this->transformedVertices[i] = Transform(v, transform);
            }
        }

        this->transformUpdateRequired = false;
    }
public:
    ShapeType shapeType;
    FlatVector position;
    float width, height;
    float rotation;
    std::vector< FlatVector > vertices;
    std::vector< FlatVector > transformedVertices;
    bool transformUpdateRequired;
};