#ifndef XWING_H
#define XWING_H

#include "Model.h"

class XWing : public Model
{
public:
    XWing(const std::string & path, const std::string & name);

    void init() override;
    void draw() override;
    void move(double time) override;
    void reset() override;

    bool is_battle_mode() { return _is_battle_mode; }
    bool is_stable() { return _s_stable; }

    void take_off(bool is_take_off) { _is_take_off = is_take_off; }
    void battle_mode (bool is_battle_mode) { _is_battle_mode = is_battle_mode; }

private:
    bool  _is_take_off;
    float _legs_offset;
    float _front_leg;
    static constexpr float LEGS_MAX_OFFSET = 1.0f;

    bool  _is_battle_mode;
    float _wings_degree;
    static constexpr float WINGS_MAX_DEGREE = 10.0f;

    bool _s_decrease = false;
    bool _s_stable   = false;
};

#endif // XWING_H
