#include "light.h"

Light::Light(QVector3D position, QVector3D intensity)
{
    position_ = position;
    intensity_ = intensity;
}

Light::~Light()
{

}

