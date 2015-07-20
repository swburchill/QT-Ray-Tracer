#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "material.h"
#include "shape.h"

#include <QVector3D>
#include <QVector4D>

using namespace std;

class Intersection
{
public:
    Intersection();
    ~Intersection();

    bool hit_;
    QVector3D intersectPoint_;
    QVector3D normalAtIntersect_;
    float distance_;
    Material* material_;
    Shape* Object_;
};

#endif // INTERSECTION_H
