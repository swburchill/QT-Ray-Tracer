#ifndef PLANE_H
#define PLANE_H

#include "material.h"
#include "shape.h"

#include <QVector3D>
#include <QVector4D>

using namespace std;

class Plane : public Shape
{
public:
    Plane(QVector3D bottomLeftVertex, QVector3D topRightVertex, QVector3D normal, QVector3D point, Material* material);
    ~Plane();
    void intersect(QVector3D rayOrigin, QVector3D rayDirection, Intersection* result);

private:
    QVector3D minCoords_;
    QVector3D maxCoords_;
    QVector3D normal_;
    QVector3D point_;
    Material* material_;
};

#endif // PLANE_H
