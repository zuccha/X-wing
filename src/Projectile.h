#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include "Base.h"
#include "Model.h"

class Projectile
{
public:
    Projectile(Model * model, const Point3d & p, const Point3d & o,
               double alpha, double beta, const Point3d & color);

    void init();
    void draw();
    void move(double time, double angle);

    double t() { return _t; }
    const Point3d & p() { return _p; }

    Model * model() { return _model; }

private:
    typedef std::vector<Point3d> PointArray;
    std::vector<PointArray> _faces;

    Model * _model;
    double _length = 10;
    double _radius = 1;
    Point3d _p; // Position
    Point3d _d; // Direction
    Point3d _o; // Offset
    double _alpha;
    double _beta;
    Point3d _color;

    PointArray _bottom;
    PointArray _top;
    double _phi;

    double _t = 0.0;
};

#endif // PROJECTILE_H
