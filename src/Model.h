#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "Base.h"
#include "Component.h"

class Model
{
public:
  Model(const std::string & path, const std::string & name,
        const Point3d & o, const Point3d & p, const Point3d & d);

  virtual void init();
  virtual void draw();
  virtual void move(double time);
  virtual void reset();

  const Point3d & p() { return _p; }
  const Point3d & d() { return _d; }

  double alpha() { return _alpha * PI / 180.0; }
  double beta() { return _beta * PI / 180.0; }

  double s() { return _s; }

  void speed(double n);

  bool is_exploding() { return _is_exploding; }
  void is_exploding(bool is_exploding) { _is_exploding = is_exploding; }

protected:
  double _rotation(double x, double y);
  double _incline(double alpha, double beta);

  Point3d _elipse_position(double time);
  void _move_elipse(double time);

  void explode();

  std::vector<Component> _components;

  Point3d _o; // Offset
  Point3d _p; // Position
  Point3d _d; // Direction
  double  _s; // Speed
  double  _a; // Accelleration
  double  _t; // Time (tau)
  double  _e; // Explosion time
  double _alpha;
  double _beta;
  double _gamma_prev;
  bool   _first_move;

  bool _is_exploding;
  std::vector<Point3d> _explosion;

private:
  void _load(const std::string & path, const std::string & name);
  Component _makeComponent(const std::vector<int>     & vertexIds,
                           const std::vector<int>     & uvIds,
                           const std::vector<int>     & normalIds,
                           const std::vector<Point3d> & vertices_all,
                           const std::vector<Point2d> & uvs_all,
                           const std::vector<Point3d> & normals_all,
                           const std::vector<Point3d> & vertices,
                           const std::vector<Point2d> & uvs,
                           const std::vector<Point3d> & normals,
                           const std::string          & texture_path);
};

#endif // MODEL_H
