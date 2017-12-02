#include "Component.h"

Component::Component()
{
}

void Component::add_vertex(const Point3d & vertex)
{
  double r = 1.0;
  double n = 0.0;
  _vertices.push_back(vertex.x() * r + n);
  _vertices.push_back(vertex.y() * r + n);
  _vertices.push_back(vertex.z() * r + n);
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

void Component::set_texture(const std::string & path)
{
    _texture = std::make_shared<Texture>(path + ".jpg");
}

void Component::init()
{
  _texture->setTexture();
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
  _bind_texture();

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

  _unbind_texture();
}

void Component::_bind_texture()
{
    if (_texture) {
        _texture->bind();
    }
}

void Component::_unbind_texture()
{
    if (_texture) {
        _texture->unbind();
    }
}
