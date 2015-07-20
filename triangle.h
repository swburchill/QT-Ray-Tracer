#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "material.h"
#include "shape.h"

#include <QVector3D>
#include <QVector4D>

class Intersection;

using namespace std;

class Triangle : public Shape
{
public:
    Triangle(QVector3D vertex1, QVector3D vertex2, QVector3D vertex3, Material* material);
    ~Triangle();
    void intersect(QVector3D rayOrigin, QVector3D rayDirection, Intersection* result);
private:
    QVector3D vertex1_;
    QVector3D vertex2_;
    QVector3D vertex3_;
    QVector3D normal_;
    Material* material_;
};

#endif // TRIANGLE_H
