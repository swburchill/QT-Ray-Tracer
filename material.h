#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>

using namespace std;

class Material
{
public:
    Material(QVector3D ambient, QVector3D diffuse, QVector3D specular, float specularExponent);
    ~Material();

    QVector3D ambient_;
    QVector3D diffuse_;
    QVector3D specular_;
    float specularExponent_;
};

#endif // MATERIAL_H
