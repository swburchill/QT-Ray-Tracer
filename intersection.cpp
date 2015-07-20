#include "intersection.h"

Intersection::Intersection()
{
    hit_ = false;
    intersectPoint_ = QVector3D(0,0,0);
    normalAtIntersect_ = QVector3D(0,0,0);
    distance_ = 1000;
    material_ = new Material(QVector3D(0.0f,0.0f,0.0f), QVector3D(2.55f,2.55f,2.55f), QVector3D(127.5f,127.5f,127.5f), (float)32);
    Object_ = NULL;
}

Intersection::~Intersection()
{
    if(material_)
    {
        delete material_;
    }
}

