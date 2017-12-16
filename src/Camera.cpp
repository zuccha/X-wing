#include "Camera.h"
#include "Base.h"

Camera::Camera():
    _position(1.0, 10.0, 10.0),
    _pitch(0.0),
    _yaw(0.0)
{}

void Camera::translate(Point3d offset)
{
    _position += offset;
}

void Camera::setPosition(Point3d position)
{
    _position = position;
}

void Camera::setYaw(double yaw)
{
    _yaw = yaw;
}

void Camera::setPitch(double pitch)
{
    _pitch = pitch;
}

void Camera::rotateX(double amount)
{
    _yaw = fmod(_yaw + amount, 2*PI);
}

void Camera::rotateY(double amount)
{
    _pitch += amount;
    if (_pitch > PI/2) _pitch = PI/2;
    if (_pitch < -PI/2) _pitch = -PI/2;
}

Point3d Camera::getPosition()
{
    return _position;
}

double Camera::getYaw()
{
    return _yaw;
}

double Camera::getPitch()
{
    return _pitch;
}
