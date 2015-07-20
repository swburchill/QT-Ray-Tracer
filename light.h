#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>

using namespace std;

class Light
{
public:
    Light(QVector3D position, QVector3D intensity);
    ~Light();

    QVector3D intensity_;
    QVector3D position_;
};

#endif // LIGHT_H
