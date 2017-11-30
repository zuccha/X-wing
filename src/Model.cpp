#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model(const std::string & path)
{
  _load(path);
}

Component Model::_makeComponent(const std::vector<int>     & vertexIds,
                                const std::vector<int>     & uvIds,
                                const std::vector<int>     & normalIds,
                                const std::vector<Point3d> & vertices,
                                const std::vector<Point2d> & uvs,
                                const std::vector<Point3d> & normals)
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
  return component;
}

void Model::_load(const std::string & path)
{
  std::vector<int> vertexIds, uvIds, normalIds;
  std::vector<Point3d> vertices;
  std::vector<Point2d> uvs;
  std::vector<Point3d> normals;

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cout << "Failed to open file " << path << std::endl;
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
                                             vertices , uvs  , normals));
      }
      vertices.clear();
      uvs.clear();
      normals.clear();
      vertexIds.clear();
      uvIds.clear();
      normalIds.clear();
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
      uvs.push_back(Point2d(x, -y));
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
  }
  if (vertexIds.size() > 0) {
    _components.push_back(_makeComponent(vertexIds, uvIds, normalIds,
                                         vertices , uvs  , normals));
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
  for (int i = 0; i < _components.size(); ++i) {
    _components[i].draw();
  }
}
