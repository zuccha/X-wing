#include "Skybox.h"
#include "Base.h"
#include <QtOpenGL>
#include <math.h>

Skybox::Skybox()
    //_texture("./media/models/sand4.jpg")
{
    double dis = 1000;

    _faces.resize(6);

    _faces[0].push_back(Point3d( dis, -dis, -dis));
    _faces[0].push_back(Point3d( dis,  dis, -dis));
    _faces[0].push_back(Point3d( dis, -dis,  dis));
    _faces[0].push_back(Point3d( dis,  dis,  dis));

    _faces[dis].push_back(Point3d(-dis,  dis, -dis));
    _faces[dis].push_back(Point3d(-dis, -dis, -dis));
    _faces[dis].push_back(Point3d(-dis,  dis,  dis));
    _faces[dis].push_back(Point3d(-dis, -dis,  dis));

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
    //_texture.bind();
    for (int i = 0; i < _faces.size(); ++i) {
        PointArray & face = _faces[i];

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < face.size(); ++j) {
            const Point3d & p = face[j];
            glVertex3d(p.x(), p.y(), p.z());
        }
        glEnd();
    }
    //_texture.unbind();
}
