#include "triangle.h"
#include "intersection.h"

Triangle::Triangle(QVector3D vertex1, QVector3D vertex2, QVector3D vertex3, Material *material)
{
    vertex1_ = vertex1;
    vertex2_ = vertex2;
    vertex3_ = vertex3;
    normal_ = QVector3D::normal(vertex2_ - vertex1_, vertex3_ - vertex1_);
    material_ = material;
}

Triangle::~Triangle()
{
    if(material_)
    {
        delete material_;
    }
}

void Triangle::intersect(QVector3D rayOrigin, QVector3D rayDirection, Intersection* result)
{ //from https://web.archive.org/web/20150212124302/http://geomalgorithms.com/a06-_intersect-2.html
    QVector3D    u, v, I;              // triangle vectors
    QVector3D    w0, w;           // ray vectors
    float     r, a, b;              // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    u = vertex2_ - vertex1_;
    v = vertex3_ - vertex1_;
    if (normal_ == QVector3D(0,0,0))
    {// triangle is degenerate
        return;                  // do not deal with this case
    }

    w0 = rayOrigin - vertex1_;
    a = -QVector3D::dotProduct(normal_,w0);
    b = QVector3D::dotProduct(normal_,rayDirection);
    if (fabs(b) < 0.01)
    {     // ray is  parallel to triangle plane
        return;              // ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.01)                    // ray goes away from triangle
    {
        return;                   // => no intersect
    }
    // for a segment, also test if (r > 1.0) => no intersect

    I = rayOrigin + r * rayDirection;            // intersect point of ray and plane

    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = QVector3D::dotProduct(u,u);
    uv = QVector3D::dotProduct(u,v);
    vv = QVector3D::dotProduct(v,v);
    w = I - vertex1_;
    wu = QVector3D::dotProduct(w,u);
    wv = QVector3D::dotProduct(w,v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0 || s > 1)         // I is outside T
    {
        return;
    }
    t = (uv * wu - uu * wv) / D;
    if (t < 0 || (s + t) > 1)  // I is outside T
    {
        return;
    }

    // I is in T
    //only update if closest object
    if(result->distance_ > r)
    {
        result->hit_ = true;
        result->intersectPoint_ = I;
        result->normalAtIntersect_ = normal_;
        result->distance_ = r;
        result->material_ = material_;
        result->Object_ = this;
    }
}
