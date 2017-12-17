#include "Tie.h"

#include <cstdlib>

Tie::Tie(const std::string & path, const std::string & name)
    : Model         (path, name, Point3d(5.0, 20.0, -20.0), Point3d(), Point3d())
    , _is_exploding (false)
{
    for (unsigned int i = 0; i < _components.size(); ++i) {
        double x = ((rand() % 300) - 150) / 10.0;
        double y = ((rand() % 300) - 150) / 10.0;
        double z = ((rand() % 300) - 150) / 10.0;
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
    static double d = 0.0;
    for (unsigned int i = 0; i < _components.size(); ++i) {
      glPushMatrix();
      Point3d & e = _explosion[i];
      glTranslated(d * e.x(), d * e.y(),  d * e.z());
      _components[i].draw();
      glPopMatrix();
    }
    d += 0.01;
  }
}

void Tie::move(double time)
{
  Model::move(time);
}
