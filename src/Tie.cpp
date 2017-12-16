#include "Tie.h"

#include <cstdlib>

Tie::Tie(const std::string & path, const std::string & name)
    : Model         (path, name, Point3d(), Point3d(), Point3d())
    , _is_exploding (false)
{
    for (Component & component : _components) {
        float x = (float(rand() % 300) - 150) / 10.0f;
        float y = (float(rand() % 300) - 150) / 10.0f;
        float z = (float(rand() % 300) - 150) / 10.0f;
        _explosion.push_back(Point3d(x, y, z));
    }
}

void Tie::init()
{
  Model::init();
//  explode(true);
}

void Tie::draw()
{
  if (!_is_exploding) {
    Model::draw();
  } else {
    static float d = 0.0f;
    for (unsigned int i = 0; i < _components.size(); ++i) {
      glPushMatrix();
      Point3d & e = _explosion[i];
      glTranslatef(d * e.x(), d * e.y(),  d * e.z());
      _components[i].draw();
      glPopMatrix();
    }
    d += 0.01f;
  }
}
