#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "Component.h"

class Model
{
public:
  Model(const std::string & path, const std::string & name,
        const Point3d & o, const Point3d & p, const Point3d & d);

  virtual void init();
  virtual void draw();
  virtual void move();

protected:
  std::vector<Component> _components;

  Point3d _o; // Offset
  Point3d _p; // Position
  Point3d _d; // Direction
  double  _s; // Speed
  double  _a; // Accelleration

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
