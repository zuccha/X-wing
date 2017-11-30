#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "Component.h"

class Model
{
public:
  Model(const std::string & path);

  void init();
  void draw();

private:
  void _load(const std::string & path);
  Component _makeComponent(const std::vector<int>     & vertexIds,
                           const std::vector<int>     & uvIds,
                           const std::vector<int>     & normalIds,
                           const std::vector<Point3d> & vertices,
                           const std::vector<Point2d> & uvs,
                           const std::vector<Point3d> & normals);
  
  std::vector<Component> _components;
};

#endif // MODEL_H
