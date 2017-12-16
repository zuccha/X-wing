#include "XWing.h"
#include "Base.h"

XWing::XWing(const std::string & path, const std::string & name)
    : Model(path, name, Point3d(3.0, 7.0, -2.0), Point3d(), Point3d())
    , _is_take_off    (false)
    , _legs_offset    (0.0f)
    , _is_battle_mode (false)
    , _wings_degree   (0.0f)
{
}

void XWing::init()
{
    Model::init();
    take_off(true);
    battle_mode(true);
}


void XWing::draw()
{
    // Handle take off legs offset
    if (_is_take_off) {
      _legs_offset += 0.01f;
      if (_legs_offset > LEGS_MAX_OFFSET) {
          _legs_offset = LEGS_MAX_OFFSET;
      }
    } else {
      _legs_offset -= 0.01f;
      if (_legs_offset < 0.0f) {
          _legs_offset = 0.0f;
      }
    }

    // Handle battle mode wings degree
    if (_is_battle_mode) {
      _wings_degree += 0.05f;
      if (_wings_degree > WINGS_MAX_DEGREE) {
          _wings_degree = WINGS_MAX_DEGREE;
      }
    } else {
      _wings_degree -= 0.01f;
      if (_wings_degree < 0.0f) {
          _wings_degree = 0.0f;
      }
    }

    // Wing 1
    glPushMatrix();
    glRotatef(-_wings_degree, 0.0, 0.0, 1.0);
    glTranslatef(-_wings_degree / 35.0f, 0.0f, 0.0f);
    _components[3].draw();  // LASER0
    _components[17].draw(); // HULL_SIDE5
    _components[19].draw(); // HULL_SIDE2
    _components[20].draw(); // BLACK_MATTE1
    _components[26].draw(); // INTAKE1
    _components[27].draw(); // ENGINE_TOP0
    _components[28].draw(); // ENGINE_INSIDE1
    // Right leg
    glPushMatrix();
    glTranslatef(0.0f, _legs_offset, 0.0f);
    _components[15].draw(); // HULL_SIDE9
    glPopMatrix();
    glPopMatrix();

    // Wing 2
    glPushMatrix();
    glRotatef(_wings_degree, 0.0, 0.0, 1.0);
    glTranslatef(_wings_degree / 35.0f, 0.0f, 0.0f);
    _components[0].draw();  // BLACK_MATTE0
    _components[6].draw();  // HULL_SIDE3
    _components[9].draw();  // INTAKE0
    _components[10].draw(); // LASER1
    _components[12].draw(); // WING_TOP
    _components[14].draw(); // ENGINE_TOP1
    _components[18].draw(); // HULL_SIDE4
    _components[24].draw(); // ENGINE_INSIDE0
    // Right leg
    glPushMatrix();
    glTranslatef(0.0f, _legs_offset, 0.0f);
    _components[7].draw();  // HULL_SIDE8
    glPopMatrix();
    glPopMatrix();

    // Body
    _components[1].draw();  // BACK_GIZMO
    _components[2].draw();  // WINDOW0
    _components[4].draw();  // WINDOW1
    _components[8].draw();  // CANOPY_BLUE
    _components[11].draw(); // CONTROL_PANEL
    _components[16].draw(); // HULL_SIDE0
    _components[21].draw(); // HULL_SIDE6
    _components[22].draw(); // TOP_GIZMO

    // Front-leg
    // Font-leg shutter left
    _components[23].draw(); // HULL_BOTTOM0
    // Font-leg shutter right
    _components[5].draw();  // HULL_BOTTOM1
    // Leg
    glPushMatrix();
    glTranslatef(0.0f, _legs_offset, 0.0f);
    _components[25].draw(); // HULL_SIDE7
    glPopMatrix();
}

double rotation(double x, double y)
{
    double r = sqrt(x * x + y * y);
    double alpha = acos(x / r);
    if (y < 0.0) alpha = (2 * PI) - alpha;
    return alpha * 180 / PI;
}

double incline(double x, double y)
{
    std::cout << sqrt(x*x + y*y) << std::endl;
    return 0.0;
}


void XWing::move()
{
    static float tau = 0.0f;

    Point3d p = _p;
    _p = _elipse(tau);
    _d = p - _p;

    glPushMatrix();
    glTranslated(_o.x(), _o.y(), _o.z());
    glTranslated(_p.x(), _p.y(), _p.z());
    glRotated(rotation(-_d.z(), -_d.x()), 0, 1, 0);
    glRotated(incline(_d.x(), _d.z()),    0, 0, 1);
    glScalef(0.2f, 0.2f, 0.2f);

    this->draw();

    glPopMatrix();
    tau += 0.02f;
}

Point3d XWing::_elipse(float time)
{
    double x = sin(time * _s) * 5.0;
    double y = 0.0;
    double z = cos(time * _s) * 5.0;
    return Point3d(x, y, z);
}
