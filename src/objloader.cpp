#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>

#include "objloader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide : 
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool loadOBJ(const char * path,
              std::vector<Point3d> & out_vertices,
              std::vector<Point2d> & out_uvs,
              std::vector<Point3d> & out_normals)
{
  std::vector<int> vertexIndices, uvIndices, normalIndices;
  std::vector<Point3d> temp_vertices;
  std::vector<Point2d> temp_uvs;
  std::vector<Point3d> temp_normals;

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cout << "Failed to open file " << path << std::endl;
  }

  std::string line;
  int g = -1;
  int g_start = 1, g_iter = 1;
  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string field;
    stream >> field;

    // Component
    if (field == "g") {
      ++g;
      if (g < g_start) continue;
      if (g == g_start + g_iter) break;
      int tvs = int(temp_vertices.size());
      int uvs = int(temp_uvs.size());
      int nvs = int(temp_normals.size());
      // For each vertex of each triangle
      for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        // Get the indices of its attributes
        int vertexIndex = vertexIndices[i];
        int uvIndex     = uvIndices[i];
        int normalIndex = normalIndices[i];
        // Negative indexes
        if (vertexIndex < 0) vertexIndex = tvs + vertexIndex + 1;
        if (uvIndex     < 0) uvIndex     = uvs + uvIndex     + 1;
        if (normalIndex < 0) normalIndex = nvs + normalIndex + 1;
        // Put the attributes in buffers
        out_vertices.push_back(temp_vertices[vertexIndex - 1]);
        out_uvs     .push_back(temp_uvs[uvIndex - 1]);
        out_normals .push_back(temp_normals[normalIndex - 1]);
      }
      
      temp_vertices.clear();
      temp_uvs.clear();
      temp_normals.clear();
      vertexIndices.clear();
      uvIndices.clear();
      normalIndices.clear();
      continue;
    }

    if (g < g_start) continue;
    
    // Vertex
    if (field == "v") {
      double x, y, z;
      stream >> x >> y >> z;
      temp_vertices.push_back(Point3d(x, y, z));
      continue;
    }

    // Vertex texture
    if (field == "vt") {
      double x, y;
      stream >> x >> y;
      temp_uvs.push_back(Point2d(x, -y));
      continue;
    }
    
    // Vertex normal
    if (field == "vn") {
      double x, y, z;
      temp_normals.push_back(Point3d(x, y, z));
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
        vertexIndices.push_back(stoi(index));
        // Screen index
        std::getline(indexes, index, '/');
        uvIndices.push_back(stoi(index));
        // Normal index
        std::getline(indexes, index, '/');
        normalIndices.push_back(stoi(index));
      }
    }
  }

  int tvs = temp_vertices.size();
  int uvs = temp_uvs.size();
  int nvs = temp_normals.size();
  // For each vertex of each triangle
  for (unsigned int i = 0; i < vertexIndices.size(); i++) {
    // Get the indices of its attributes
    int vertexIndex = vertexIndices[i];
    int uvIndex     = uvIndices[i];
    int normalIndex = normalIndices[i];
    // Negative indexes
    if (vertexIndex < 0) vertexIndex = tvs + vertexIndex + 1;
    if (uvIndex     < 0) uvIndex     = uvs + uvIndex     + 1;
    if (normalIndex < 0) normalIndex = nvs + normalIndex + 1;
    // Put the attributes in buffers
    out_vertices.push_back(temp_vertices[vertexIndex - 1]);
    out_uvs     .push_back(temp_uvs[uvIndex - 1]);
    out_normals .push_back(temp_normals[normalIndex - 1]);
  }
  
  file.close();
  return true;
}

void vecPoint2dToFloat(std::vector<Point2d> &_vec, std::vector<GLfloat> &_out) {
  _out.clear();
  for(auto i = _vec.begin(); i != _vec.end(); ++i) {
    _out.push_back(i->x());
    _out.push_back(i->y());
  }
}

void vecPoint3dToFloat(std::vector<Point3d> &_vec, std::vector<GLfloat> &_out) {
  _out.clear();
  for(auto i = _vec.begin(); i != _vec.end(); ++i) {
    _out.push_back(i->x());
    _out.push_back(i->y());
    _out.push_back(i->z());
  }
}
