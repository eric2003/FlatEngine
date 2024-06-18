#pragma once
#include "FlatVector.h"
#include "FlatMath.h"
#include <vector>

class Collisions
{
public:
    Collisions();
public:
    static float Distance( const FlatVector &centerA, const FlatVector &centerB)
    {
        float dx =  centerA.x - centerB.x;
        float dy =  centerA.y - centerB.y;
        return sqrt(dx*dx + dy*dy);
    }

    static bool IntersectCircles( const FlatVector &centerA, float radisuA,  const FlatVector &centerB, float radisuB,
                          FlatVector &normal, float &depth )
    {
        float distance = Collisions::Distance(centerA,centerB);
        float radii = radisuA + radisuB;

        if( distance >= radii )
        {
            normal = FlatVector::Zero();
            depth = 0.0f;
            return false;
        }

        normal = centerB - centerA;
        normal.normalize();
        depth = radii - distance;
        return true;
    }

    static bool IntersectPolygons(std::vector< FlatVector > &verticesA, std::vector< FlatVector > &verticesB)
    {
        int aSize = verticesA.size();
        for ( int i = 0; i < aSize; ++ i )
        {
            FlatVector &va = verticesA[i];
            FlatVector &vb = verticesA[(i+1)%aSize];
            FlatVector edge = vb - va;
            FlatVector axis = FlatVector( - edge.y, edge.x );
            axis.normalize();

            float minA, maxA;
            float minB, maxB;
            Collisions::ProjectVertices( verticesA, axis, minA, maxA );
            Collisions::ProjectVertices( verticesB, axis, minB, maxB );
            if ( minA >= maxB || minB >= maxA )
            {
                return false;
            }
        }

        int bSize = verticesB.size();
        for ( int i = 0; i < bSize; ++ i )
        {
            FlatVector &va = verticesB[i];
            FlatVector &vb = verticesB[(i+1)%aSize];
            FlatVector edge = vb - va;
            FlatVector axis = FlatVector( - edge.y, edge.x );
            axis.normalize();

            float minA, maxA;
            float minB, maxB;
            Collisions::ProjectVertices( verticesA, axis, minA, maxA );
            Collisions::ProjectVertices( verticesB, axis, minB, maxB );
            if ( minA >= maxB || minB >= maxA )
            {
                return false;
            }
        }
        return true;
    }

    static void ProjectVertices(std::vector< FlatVector > &vertices, FlatVector & axis, float &minval, float &maxval )
    {
        minval = std::numeric_limits<float>::max();
        maxval = std::numeric_limits<float>::min();

        for ( int i = 0; i < vertices.size(); ++ i )
        {
            FlatVector &v = vertices[i];
            float proj = FlatMath::Dot(v,axis);
            if ( proj < minval )
            {
                minval = proj;
            }
            if ( proj > maxval )
            {
                maxval = proj;
            }
        }
    }
};

