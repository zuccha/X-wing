#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model(const std::string & path, const std::string & name)
{
  _load(path, name);
}

Component Model::_makeComponent(const std::vector<int>     & vertexIds,
                                const std::vector<int>     & uvIds,
                                const std::vector<int>     & normalIds,
                                const std::vector<Point3d> & vertices,
                                const std::vector<Point2d> & uvs,
                                const std::vector<Point3d> & normals,
                                const std::string          & texture_path)
{
  Component component;
  // For each vertex of each triangle
  for (unsigned int i = 0; i < vertexIds.size(); i++) {
    // Get the indices of its attributes
    int vertexId = vertexIds[i];
    int uvId     = uvIds[i];
    int normalId = normalIds[i];
    // Deal with negative indexes
    if (vertexId < 0) vertexId = vertices.size() + vertexId + 1;
    if (uvId     < 0) uvId     = uvs.size()      + uvId     + 1;
    if (normalId < 0) normalId = normals.size()  + normalId + 1;
    // Put the attributes in buffers
    component.add_vertex(vertices[vertexId - 1]);
    component.add_uv(uvs[uvId - 1]);
    component.add_normal(normals[normalId - 1]);
  }
  if (texture_path != "") {
    component.set_texture(texture_path);
  }
  return component;
}

void Model::_load(const std::string & path, const std::string & name)
{
  std::vector<int> vertexIds, uvIds, normalIds;
  std::vector<Point3d> vertices;
  std::vector<Point2d> uvs;
  std::vector<Point3d> normals;
  std::string texture_path;

  std::ifstream file(path + name);
  if (!file.is_open()) {
    std::cout << "Failed to open file " << path + name << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string field;
    stream >> field;

    // Component
    if (field == "g") {
      if (vertexIds.size() > 0) {
        _components.push_back(_makeComponent(vertexIds, uvIds, normalIds,
                                             vertices , uvs  , normals,
                                             texture_path));
      }
      vertices.clear();
      uvs.clear();
      normals.clear();
      vertexIds.clear();
      uvIds.clear();
      normalIds.clear();
      texture_path = "";
      continue;
    }

    // Vertex
    if (field == "v") {
      double x, y, z;
      stream >> x >> y >> z;
      vertices.push_back(Point3d(x, y, z));
      continue;
    }

    // Vertex texture
    if (field == "vt") {
      double x, y;
      stream >> x >> y;
      uvs.push_back(Point2d(x, y));
      continue;
    }
    
    // Vertex normal
    if (field == "vn") {
      double x, y, z;
      normals.push_back(Point3d(x, y, z));
      continue;
    }
    
    // Faces
    if (field == "f") {
      // The stream now contains something like "1/2/3 4/5/6 -1/-2/-3"
      // The while goes over each "x/y/z" block
      while (stream >> field) {
        std::stringstream indexes(field);
        std::string index;
        // Vector index
        std::getline(indexes, index, '/');
        vertexIds.push_back(stoi(index));
        // Screen index
        std::getline(indexes, index, '/');
        uvIds.push_back(stoi(index));
        // Normal index
        std::getline(indexes, index, '/');
        normalIds.push_back(stoi(index));
      }
    }

    // Texture
    if (field == "usemtl") {
        stream >> texture_path;
        texture_path = path + texture_path;
    }

  }
  if (vertexIds.size() > 0) {
    _components.push_back(_makeComponent(vertexIds, uvIds, normalIds,
                                         vertices , uvs  , normals,
                                         texture_path));
  }
  file.close();
}

void Model::init()
{
  for (Component & components : _components) {
    components.init();
  }
}

void Model::draw()
{
  for (Component & components : _components) {
    components.draw();
  }
}
