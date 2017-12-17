#include "Skybox.h"
#include "Base.h"
#include <QtOpenGL>
#include <math.h>

Skybox::Skybox():
    _texture("./media/models/grass.jpg")
{}

void Skybox::init()
{
    _texture.setTexture();
    double dis = 1000;

    _faces.resize(6);

    _uvs.push_back({0.0,0.0});
    _uvs.push_back({0.0,1.0});
    _uvs.push_back({1.0,0.0});
    _uvs.push_back({1.0,1.0});

    _faces[0].push_back(Point3d( dis, -dis, -dis));
    _faces[0].push_back(Point3d( dis,  dis, -dis));
    _faces[0].push_back(Point3d( dis, -dis,  dis));
    _faces[0].push_back(Point3d( dis,  dis,  dis));

    _faces[1].push_back(Point3d(-dis,  dis, -dis));
    _faces[1].push_back(Point3d(-dis, -dis, -dis));
    _faces[1].push_back(Point3d(-dis,  dis,  dis));
    _faces[1].push_back(Point3d(-dis, -dis,  dis));

    _faces[2].push_back(Point3d( dis,  dis, -dis));
    _faces[2].push_back(Point3d(-dis,  dis, -dis));
    _faces[2].push_back(Point3d( dis,  dis,  dis));
    _faces[2].push_back(Point3d(-dis,  dis,  dis));

    _faces[3].push_back(Point3d(-dis, -dis, -dis));
    _faces[3].push_back(Point3d( dis, -dis, -dis));
    _faces[3].push_back(Point3d(-dis, -dis,  dis));
    _faces[3].push_back(Point3d( dis, -dis,  dis));

    _faces[4].push_back(Point3d(-dis, -dis,  dis));
    _faces[4].push_back(Point3d( dis, -dis,  dis));
    _faces[4].push_back(Point3d(-dis,  dis,  dis));
    _faces[4].push_back(Point3d( dis,  dis,  dis));

    _faces[5].push_back(Point3d(-dis, -dis, -dis));
    _faces[5].push_back(Point3d( dis, -dis, -dis));
    _faces[5].push_back(Point3d(-dis,  dis, -dis));
    _faces[5].push_back(Point3d( dis,  dis, -dis));
}

void Skybox::draw()
{
    for (int i = 0; i < _faces.size(); ++i) {
        PointArray & face = _faces[i];
        _texture.bind();
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < face.size(); ++j) {
            const Point3d & p = face[j];
            const Point2d & uv = _uvs[j];
            glTexCoord2d(uv.x(), uv.y());
            glVertex3d(p.x(), p.y(), p.z());
        }
        glEnd();
        _texture.unbind();
    }
}
