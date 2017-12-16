#ifndef CAMERA_H
#define CAMERA_H

#include "Point3.h"



class Camera
{
public:
    Camera();

    void translate(Point3d offset);
    void rotateX(double amount);
    void rotateY(double amount);

    void setPosition(Point3d position);
    void setYaw(double yaw);
    void setPitch(double pitch);

    Point3d getPosition();
    double getYaw();
    double getPitch();

private:
    double _pitch;
    double _yaw;
    Point3d _position;
};

#endif // CAMERA_H
