#include "sphere.h"
#include "intersection.h"

#include <math.h>

Sphere::Sphere(QVector3D center, float radius, Material *material)
{
    center_ = center;
    radius_ = radius;
    material_ = material;
}

Sphere::~Sphere()
{
    if(material_)
    {
        delete material_;
    }
}

void Sphere::intersect(QVector3D rayOrigin, QVector3D rayDirection, Intersection* result)
{
    //intersect code for sphere
    float minT;

    //D = point - center
    QVector3D D = rayOrigin - center_;
    float d_D = QVector3D::dotProduct(rayDirection, D);
    float D_D = QVector3D::dotProduct(D, D);
    float discriminant = pow(d_D,2.0) - (D_D - pow(radius_,2.0));
    if(discriminant <= 0.01) //does not intersect
    {
        return;
    }
    float t1 = (-1*(d_D) + sqrt(discriminant));
    float t2 = (-1*(d_D) - sqrt(discriminant));
    // only want positive intersections infront of camera
    if(t1 > 0.01)
    {
        if(t2 > 0.01)
        {
            minT = qMin(t1, t2);
        }
        else
        {
            minT = t1;
        }
    }
    else if(t2 > 0.01)
    {
        minT = t2;
    }
    else //for any intersections outside behind camera
    {
        return;
    }
    //only update if closest object
    if(result->distance_ > minT)
    {
        result->hit_ = true;
        result->intersectPoint_ = rayOrigin + (rayDirection * minT);
        QVector3D normal = (rayOrigin + (rayDirection * minT)) - center_;
        normal.normalize();
        result->normalAtIntersect_ = normal;
        result->distance_ = minT;
        result->material_ = material_;
        result->Object_ = this;
    }
}
