#include "Tie.h"
#include "Base.h"

#include <cstdlib>

Tie::Tie(const std::string & path, const std::string & name)
    : Model         (path, name, Point3d(5.0, 20.0, -70.0), Point3d(), Point3d())
    , _is_exploding (false)
{
    _t = -3 * PI / 4;
    _s = 0.035;
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
}

void Tie::draw()
{
  Model::draw();
}

void Tie::move(double time)
{
  if (!_is_exploding) {
    Model::move(time);
  } else {
    static double d = 0.0;
    for (unsigned int i = 0; i < _components.size(); ++i) {
      glPushMatrix();
      Point3d & e = _explosion[i];
      glTranslated(_p.x() + d * e.x(),
                   _p.y() + d * e.y(),
                   _p.z() + d * e.z());
      _components[i].draw();
      glPopMatrix();
    }
    d += 0.01;
  }
  _t += _s;
}
