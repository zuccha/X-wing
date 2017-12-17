#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include "Base.h"

class Projectile
{
public:
    Projectile(const Point3d & p, double angle);

    void init();
    void draw();
    void move(double time);

    double t() { return _t; }
    const Point3d & p() { return _p; }

private:
    typedef std::vector<Point3d> PointArray;
    std::vector<PointArray> _faces;

    double _length = 10;
    double _radius = 1;
    Point3d _p; // Position
    double _angle; // Direction

    PointArray _bottom;
    PointArray _top;
    double _phi;

    double _t = 0.0;
};

#endif // PROJECTILE_H
