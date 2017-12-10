#include "XWing.h"

XWing::XWing(const std::string & path, const std::string & name)
    : Model(path, name)
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
      _wings_degree -= 0.01f;
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
    _components[7].draw();
    _components[11].draw();
    _components[12].draw();
    _components[18].draw();
    _components[19].draw();
    _components[27].draw();
    _components[28].draw();
    // Right leg
    glPushMatrix();
    glTranslatef(0.0f, _legs_offset, 0.0f);
    _components[24].draw();
    glPopMatrix();
    glPopMatrix();
    // Wing 2
    glPushMatrix();
    glRotatef(_wings_degree, 0.0, 0.0, 1.0);
    _components[8].draw();
    _components[9].draw();
    _components[10].draw();
    _components[13].draw();
    _components[17].draw();
    _components[20].draw();
    _components[25].draw();
    _components[26].draw();
    // Right leg
    glPushMatrix();
    glTranslatef(0.0f, _legs_offset, 0.0f);
    _components[23].draw();
    glPopMatrix();
    glPopMatrix();

    // Body
    _components[0].draw();
    _components[3].draw();
    _components[4].draw();
    _components[6].draw();
    _components[14].draw();
    _components[15].draw();
    _components[16].draw();
    _components[21].draw();

    // Front-leg
    // Font-leg shutter left
    _components[1].draw();
    // Font-leg shutter right
    _components[2].draw();
    // Leg
    glPushMatrix();
    glTranslatef(0.0f, _legs_offset, 0.0f);
    _components[22].draw();
    glPopMatrix();


}
