#ifndef SPHERE_H
#define SPHERE_H

#include "material.h"
#include "shape.h"

#include <QVector3D>
#include <QVector4D>

class Intersection;

using namespace std;

class Sphere : public Shape
{
public:
    Sphere(QVector3D center, float radius, Material* material);
    ~Sphere();
    void intersect(QVector3D rayOrigin, QVector3D rayDirection, Intersection* result);

private:
    QVector3D center_;
    float radius_;
    Material* material_;
};

#endif // SPHERE_H
