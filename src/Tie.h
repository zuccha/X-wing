#ifndef TIE_H
#define TIE_H

#include <vector>
#include <Point3.h>
#include "Model.h"

class Tie : public Model
{
public:
    Tie(const std::string & path, const std::string & name);

    void init() override;
    void draw() override;

    void explode(bool is_exploding) { _is_exploding = is_exploding; }

private:
    bool _is_exploding;
    std::vector<Point3d> _explosion;
};

#endif // TIE_H
