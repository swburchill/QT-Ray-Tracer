#include "material.h"

Material::Material(QVector3D ambient, QVector3D diffuse, QVector3D specular, float specularExponent)
{
    ambient_ = ambient;
    diffuse_ = diffuse;
    specular_ = specular;
    specularExponent_ = specularExponent;
}

Material::~Material()
{

}

