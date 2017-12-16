#include "Camera.h"

Camera::Camera():
    _position(1.0, 10.0, 10.0)
{}

void Camera::translate(Point3d offset)
{
    _position += offset;
}

//void Camera::rotate(double angle_offset, Point3d axis)
//{
//    _angle += angle_offset;
//    _rotation_axis = axis;
//}

Point3d Camera::getPos() {
    return _position;
}

//Point3d Camera::getRotAxis() {
//    return _rotation_axis;
//}

//double Camera::getAngle() {
//    return _angle;
//}

