#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "Component.h"

class Model
{
public:
  Model(const std::string & path, const std::string & name);

  void init();
  void draw();

  void bind_texture();
  void unbind_texture();

private:
  void _load(const std::string & path, const std::string & name);
  Component _makeComponent(const std::vector<int>     & vertexIds,
                           const std::vector<int>     & uvIds,
                           const std::vector<int>     & normalIds,
                           const std::vector<Point3d> & vertices,
                           const std::vector<Point2d> & uvs,
                           const std::vector<Point3d> & normals,
                           const std::string          & texture_path);
  
  std::vector<Component> _components;
};

#endif // MODEL_H
