#ifndef CAMERA_H
#define CAMERA_H

#include "Point3.h"



class Camera
{
public:
    Camera();
    void translate(Point3d offset);
//    void rotate(double angle_offset, Point3d axis);

    Point3d getPos();

    double pitch;
    double yaw;

//    double getAngle();
//    Point3d getRotAxis();

private:
    Point3d _position;
//    Point3d _rotation_axis;
};

#endif // CAMERA_H
