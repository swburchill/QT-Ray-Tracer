#include "plane.h"
#include "intersection.h"

#include <math.h>

Plane::Plane(QVector3D bottomLeftVertex, QVector3D topRightVertex, QVector3D normal, QVector3D point, Material *material)
{
    minCoords_.setX(qMin(bottomLeftVertex.x(),topRightVertex.x()));
    minCoords_.setY(qMin(bottomLeftVertex.y(),topRightVertex.y()));
    minCoords_.setZ(qMin(bottomLeftVertex.z(),topRightVertex.z()));
    maxCoords_.setX(qMax(bottomLeftVertex.x(),topRightVertex.x()));
    maxCoords_.setY(qMax(bottomLeftVertex.y(),topRightVertex.y()));
    maxCoords_.setZ(qMax(bottomLeftVertex.z(),topRightVertex.z()));
    normal_ = normal;
    normal_.normalize();
    point_ = point;
    material_ = material;
}

Plane::~Plane()
{
    if(material_)
    {
        delete material_;
    }
}

void Plane::intersect(QVector3D rayOrigin, QVector3D rayDirection, Intersection* result)
{ //from https://web.archive.org/web/20150212124302/http://geomalgorithms.com/a06-_intersect-2.html
    if(normal_ == QVector3D(0,0,0)) //plane is degenerate
    {
        return;
    }
    float minT;
    //t = -Normal*(Origin-Point) / Normal*direction
    float numerator = (-1)*QVector3D::dotProduct(normal_, (rayOrigin - point_));
    float denominator = QVector3D::dotProduct(normal_, rayDirection);
    if (fabs(denominator) < 0.01) //plane orthogonal to view
    {
        return;
    }
    minT = numerator / denominator;
    if (minT < 0.01)
    {
        return;
    }
    QVector3D intersectPoint = rayOrigin + (rayDirection * minT);
    //check inside plane dimensions
    if(intersectPoint.x() < (minCoords_.x() - 0.001) || intersectPoint.x() > (maxCoords_.x() + 0.001) ||
       intersectPoint.y() < (minCoords_.y() - 0.001) || intersectPoint.y() > (maxCoords_.y() + 0.001) ||
       intersectPoint.z() < (minCoords_.z() - 0.001) || intersectPoint.z() > (maxCoords_.z() + 0.001))
    {
        return;
    }
    //only update if closest object
    if(result->distance_ > minT)
    {
        result->hit_ = true;
        result->intersectPoint_ = intersectPoint;
        result->normalAtIntersect_ = normal_;
        result->distance_ = minT;
        result->material_ = material_;
        result->Object_ = this;
    }
}
