#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <QtOpenGl>
#include "Point3.h"
#include "Point2.h"

class Component
{
public:
  Component();

  void init();
  void draw();

  void add_vertex(const Point3d & vertex);
  void add_uv    (const Point2d & uv);
  void add_normal(const Point3d & normal);

private:
  std::vector<GLfloat> _vertices;
  std::vector<GLfloat> _uvs;
  std::vector<GLfloat> _normals;

  GLuint _vertex_buffer;
  GLuint _uv_buffer;
};

#endif // COMPONENT_H
