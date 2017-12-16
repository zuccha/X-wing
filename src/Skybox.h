#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include "Base.h"
#include "texture.hpp"

class Skybox
{
public:
    Skybox();

    void draw();

private:
    typedef std::vector<Point3d> PointArray;

    std::vector<PointArray> _faces;
    //Texture _texture;

};

#endif // SKYBOX_H
