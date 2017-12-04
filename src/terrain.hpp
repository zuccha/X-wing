#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Point2.h"
#include "Point3.h"
#include "perlinnoise.hpp"
#include "texture.hpp"

struct Strip {
    std::vector<Point3d> vertices;
    std::vector<Point3d> normals;
    std::vector<Point2d> uvs; // TODO
};

class Terrain
{
public:
    Terrain();
    void generate(int size);
    void draw();

private:
    std::vector<Strip> _strips;
    siv::PerlinNoise _noiseGen;
    Texture _texture;

    float _generateHeight(float x, float y);
    Point3d _computeNormal(float x, float y);
};


#endif // TERRAIN_HPP
