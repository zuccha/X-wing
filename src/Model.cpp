#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Base.h"
#include "Tie.h"

Model::Model(const std::string & path, const std::string & name,
             const Point3d & o, const Point3d & p, const Point3d & d)
    : _o(o)
    , _p(p)
    , _d(d)
    , _s(0.0)
    , _a(0.0)
    , _t(0.0)
    , _alpha(0.0)
{
  _load(path, name);
}

Component Model::_makeComponent(const std::vector<int>     & vertexIds,
                                const std::vector<int>     & uvIds,
                                const std::vector<int>     & normalIds,
                                const std::vector<Point3d> & vertices_all,
                                const std::vector<Point2d> & uvs_all,
                                const std::vector<Point3d> & normals_all,
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
    // Vertices
    const Point3d & vertex = vertexId < 0
                           ? vertices[vertices.size() + vertexId]
                           : vertices_all[vertexId - 1];
    const Point2d & uv     = uvId < 0
                           ? uvs[uvs.size() + uvId]
                           : uvs_all[uvId - 1];
    const Point3d & normal = normalId < 0
                           ? normals[normals.size() + normalId]
                           : normals_all[normalId - 1];
    component.add_vertex(vertex);
    component.add_uv(uv);
    component.add_normal(normal);
  }
  if (texture_path != "") {
    component.set_texture(texture_path);
  }
  return component;
}

void Model::_load(const std::string & path, const std::string & name)
{
  std::vector<int> vertexIds, uvIds, normalIds;
  std::vector<Point3d> vertices_all, vertices;
  std::vector<Point2d> uvs_all, uvs;
  std::vector<Point3d> normals_all, normals;
  std::string texture_path;

  std::ifstream file(path + name);
  if (!file.is_open()) {
    std::cout << "Failed to open file " << path + name << std::endl;
    return;
  }

  std::string line;
  //int g = 0;
  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string field;
    stream >> field;

    // Component
    if (field == "g" || field == "o") {

      //std::string name;
      //stream >> name;
      //std::cout << g++ << "\t" << name << std::endl;

      if (vertexIds.size() > 0) {
        _components.push_back(_makeComponent(vertexIds,    uvIds,   normalIds,
                                             vertices_all, uvs_all, normals_all,
                                             vertices,     uvs,     normals,
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
      vertices_all.push_back(Point3d(x, y, z));
      continue;
    }

    // Vertex texture
    if (field == "vt") {
      double x, y;
      stream >> x >> y;
      uvs.push_back(Point2d(x, y));
      uvs_all.push_back(Point2d(x, y));
      continue;
    }
    
    // Vertex normal
    if (field == "vn") {
      double x, y, z;
      stream >> x >> y >> z;
      normals.push_back(Point3d(x, y, z));
      normals_all.push_back(Point3d(x, y, z));
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
    _components.push_back(_makeComponent(vertexIds,    uvIds,   normalIds,
                                         vertices_all, uvs_all, normals_all,
                                         vertices,     uvs,     normals,
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

void Model::move(double time)
{
    _move_elipse(time);
}

void Model::_move_elipse(double time)
{
    Point3d p = _p;

    _p = _o + _elipse_position(_t);
    double k = 0.0;
    if (dynamic_cast<Tie *>(this)) {
      k = 2.0 / time;
    }
    _d = p - _p;

    glPushMatrix();
    glTranslated(_p.x() + k, _p.y(), _p.z() + k);

    double alpha_old = _alpha;
    _alpha      = _rotation(-_d.z(), -_d.x());
    double beta = _incline(_alpha, alpha_old);

    glRotated(_alpha, 0, 1, 0); // Movement direction
    glRotated(beta,   0, 0, 1); // Curvature

    this->draw();

    glPopMatrix();
}

double Model::_rotation(double x, double y)
{
    double r = sqrt(x * x + y * y);
    double alpha = acos(x / r);
    if (y < 0.0) alpha = (2 * PI) - alpha;
    return alpha * 180 / PI;
}

double Model::_incline(double alpha, double beta)
{
    double gamma = abs(alpha - beta) * -36.8;
    return -90.0 <= gamma ? gamma : -90.0;
}

Point3d Model::_elipse_position(double time)
{
//    constexpr double A = 50.0;
//    constexpr double B = 35.0;
//    double x = sin(time) * A;
//    double y = 0.0;
//    double z = cos(time) * B;
//    return Point3d(x, y, z);

    constexpr double A = 50.0;
    constexpr double B = 75.0;
    double x = sin(time) * A + cos(time*8)*0.20;
    double y = sin(time*8)*0.25;
    double z = cos(time/2) * B + sin(time*5)*0.2;
    return Point3d(x, y, z);
}
