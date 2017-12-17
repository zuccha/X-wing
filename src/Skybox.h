#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include "Base.h"
#include "Point2.h"
#include "texture.hpp"

class Skybox
{
public:
    Skybox();

    void draw();
    void init();

private:
    typedef std::vector<Point3d> PointArray;

    std::vector<PointArray> _faces;
    std::vector<Point3d>    _normals;
    std::vector<Point2d>    _uvs;

    Texture _texture;

};

#endif // SKYBOX_H
