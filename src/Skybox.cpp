#include "Skybox.h"
#include "Base.h"
#include <QtOpenGL>
#include <math.h>

Skybox::Skybox():
    _texture("./media/models/sand4.jpg")
{
    _texture.setTexture();
    double dis = 1000;

    _faces.resize(6);
    _normals.resize(6);

    _faces[0].push_back(Point3d( dis, -dis, -dis));
    _faces[0].push_back(Point3d( dis,  dis, -dis));
    _faces[0].push_back(Point3d( dis, -dis,  dis));
    _faces[0].push_back(Point3d( dis,  dis,  dis));
    _normals[0] = Point3d(dis, 0, 0);


    _faces[dis].push_back(Point3d(-dis,  dis, -dis));
    _faces[dis].push_back(Point3d(-dis, -dis, -dis));
    _faces[dis].push_back(Point3d(-dis,  dis,  dis));
    _faces[dis].push_back(Point3d(-dis, -dis,  dis));
    _normals[1] = Point3d(-dis, 0, 0);

    _faces[2].push_back(Point3d( dis,  dis, -dis));
    _faces[2].push_back(Point3d(-dis,  dis, -dis));
    _faces[2].push_back(Point3d( dis,  dis,  dis));
    _faces[2].push_back(Point3d(-dis,  dis,  dis));
    _normals[2] = Point3d(0, dis, 0);

    _faces[3].push_back(Point3d(-dis, -dis, -dis));
    _faces[3].push_back(Point3d( dis, -dis, -dis));
    _faces[3].push_back(Point3d(-dis, -dis,  dis));
    _faces[3].push_back(Point3d( dis, -dis,  dis));
    _normals[3] = Point3d(0, -dis, 0);

    _faces[4].push_back(Point3d(-dis, -dis,  dis));
    _faces[4].push_back(Point3d( dis, -dis,  dis));
    _faces[4].push_back(Point3d(-dis,  dis,  dis));
    _faces[4].push_back(Point3d( dis,  dis,  dis));
    _normals[4] = Point3d(0, 0, dis);

    _faces[5].push_back(Point3d(-dis, -dis, -dis));
    _faces[5].push_back(Point3d( dis, -dis, -dis));
    _faces[5].push_back(Point3d(-dis,  dis, -dis));
    _faces[5].push_back(Point3d( dis,  dis, -dis));
    _normals[5] = Point3d(0, 0, -dis);
}

void Skybox::draw()
{
    _texture.bind();
    for (int i = 0; i < _faces.size(); ++i) {
        PointArray & face = _faces[i];

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < face.size(); ++j) {
            const Point3d & p = face[j];
            glVertex3d(p.x(), p.y(), p.z());
            glNormal3d(p.x(), p.y(), p.z());
        }
        glEnd();
    }
    _texture.unbind();
}
