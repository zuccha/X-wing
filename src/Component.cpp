#include "Component.h"

Component::Component()
{

}

void Component::add_vertex(const Point3d & vertex)
{
  _vertices.push_back(vertex.x());
  _vertices.push_back(vertex.y());
  _vertices.push_back(vertex.z());
}

void Component::add_uv(const Point2d & uv)
{
  _uvs.push_back(uv.x());
  _uvs.push_back(uv.y());
}

void Component::add_normal(const Point3d & normal)
{
  _normals.push_back(normal.x());
  _normals.push_back(normal.y());
  _normals.push_back(normal.z());
}

void Component::init()
{
  glGenBuffers(1, &_vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER,
               _vertices.size() * sizeof(GLfloat),
               &_vertices[0],
               GL_STATIC_DRAW);

  glGenBuffers(1, &_uv_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer);
  glBufferData(GL_ARRAY_BUFFER,
               _uvs.size() * sizeof(GLfloat),
               &_uvs[0],
               GL_STATIC_DRAW);
}

void Component::draw()
{
  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
  glVertexPointer(
      3,                  // size
      GL_FLOAT,           // type
      0,                  // stride
      (void*)0            // array buffer offset
                  );
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer);
  glTexCoordPointer(
      2,                  // size
      GL_FLOAT,           // type
      0,                  // stride
      (void*)0            // array buffer offset
                    );
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
  glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 3);
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
