#include "Tie.h"

Tie::Tie(const std::string & path, const std::string & name)
    : Model         (path, name)
    , _is_exploding (false)
{
}

void Tie::init()
{
  Model::init();
  explode(true);
}

void Tie::draw()
{
  Model::draw();
}
