#include "terrain.hpp"
#include <QtOpenGL>

Terrain::Terrain():
    _noiseGen(1252423),
    _texture("./media/models/sand4.jpg")
{}

float Terrain::_generateHeight(float x, float y) {
    const float frequency = 0.01f;
    const float amplitude = 25.0f;
    return _noiseGen.octaveNoise(x*frequency, y*frequency, 3)*amplitude;
}

Point3d Terrain::_computeNormal(float x, float y) {
    // see: https://stackoverflow.com/a/13983431
    Point3d off{1.0,1.0,0.0};
    Point2d offXZ{off.x(), off.z()};
    Point2d offZY{off.z(), off.y()};
    Point2d Pxy{x, y};
    Point2d diffL = Pxy - offXZ;
    Point2d diffR = Pxy + offXZ;
    Point2d diffD = Pxy - offZY;
    Point2d diffU = Pxy + offZY;

    float hL = _generateHeight(diffL.x(), diffL.y());
    float hR = _generateHeight(diffR.x(), diffR.y());
    float hD = _generateHeight(diffD.x(), diffD.y());
    float hU = _generateHeight(diffU.x(), diffU.y());

    Point3d normal{hL - hR, hD - hU, 2.0};
    normal.normalize();
    return normal;
}


void Terrain::generate(const int size) {
    std::cout << "Generating terrain..." << size << std::endl;
    _texture.setTexture();
    for (int i = -size; i < size; i++) {
        Strip strip;
        for (int j = -size; j < size; j++) {
            float fx = (float)i;
            float fx1 = (float)(i+1);
            float fy = (float)j;

            double height1 = _generateHeight(fx, fy);
            double height2 = _generateHeight(fx1, fy);

            Point3d n1 = _computeNormal(fx, fy);
            Point3d n2 = _computeNormal(fx1, fy);

            strip.vertices.push_back({(double)i, height1, (double)j});
            strip.vertices.push_back({(double)i+1, height2, (double)j});

            strip.normals.push_back(n1);
            strip.normals.push_back(n2);

            strip.uvs.push_back({fx, fy});
            strip.uvs.push_back({fx1, fy});
        }
        _strips.push_back(strip);
    }
}

void Terrain::draw() {
    _texture.bind();
    for (Strip& strip: _strips) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i=0; i < strip.vertices.size(); i++) {
            Point3d n = strip.normals[i];
            Point3d v = strip.vertices[i];
            Point2d uv = strip.uvs[i];
            glNormal3f(n.x(), n.y(), n.z());
            glVertex3f(v.x(), v.y(), v.z());
            glTexCoord2f(uv.x(), uv.y());
        }
        glEnd();
    }
    _texture.unbind();
}
