#ifndef TIE_H
#define TIE_H

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
};

#endif // TIE_H
