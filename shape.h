#ifndef SHAPE_H
#define SHAPE_H

class QVector3D;
class Intersection;

using namespace std;

class Shape
{
public:
    virtual void intersect(QVector3D rayOrigin, QVector3D rayDirection, Intersection* result) = 0; //populates intersection data
};

#endif // SHAPE
