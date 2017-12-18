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
    void move(double time) override;
};

#endif // TIE_H
