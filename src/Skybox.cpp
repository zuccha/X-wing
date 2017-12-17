#include "Skybox.h"
#include "Base.h"
#include <QtOpenGL>
#include <math.h>

Skybox::Skybox():
    _textures({
                {"./media/models/desert/desert_right.png"},
                {"./media/models/desert/desert_left.png"},
                {"./media/models/desert/desert_top.png"},
                {"./media/models/desert/desert_bottom.png"},
                {"./media/models/desert/desert_front.png"},
                {"./media/models/desert/desert_back.png"},
              })
{}

void Skybox::init()
{
    // init textures
    for (Texture& tex: _textures) {
        tex.setSkyboxTexture();
    }

    double dis = 1000;

    _faces.resize(6);

    _uvs.push_back({0.0,0.0});
    _uvs.push_back({0.0,1.0});
    _uvs.push_back({1.0,0.0});
    _uvs.push_back({1.0,1.0});

    // right
    _faces[0].push_back(Point3d( dis, -dis,  dis));
    _faces[0].push_back(Point3d( dis,  dis,  dis));
    _faces[0].push_back(Point3d( dis, -dis, -dis));
    _faces[0].push_back(Point3d( dis,  dis, -dis));

    // left
    _faces[1].push_back(Point3d(-dis, -dis, -dis));
    _faces[1].push_back(Point3d(-dis,  dis, -dis));
    _faces[1].push_back(Point3d(-dis, -dis,  dis));
    _faces[1].push_back(Point3d(-dis,  dis,  dis));

    // top
    _faces[2].push_back(Point3d(-dis,  dis,  dis));
    _faces[2].push_back(Point3d(-dis,  dis, -dis));
    _faces[2].push_back(Point3d( dis,  dis,  dis));
    _faces[2].push_back(Point3d( dis,  dis, -dis));


    // bottom
    _faces[3].push_back(Point3d(-dis, -dis, -dis));
    _faces[3].push_back(Point3d( dis, -dis, -dis));
    _faces[3].push_back(Point3d(-dis, -dis,  dis));
    _faces[3].push_back(Point3d( dis, -dis,  dis));

    // front
    _faces[4].push_back(Point3d(-dis, -dis,  dis));
    _faces[4].push_back(Point3d(-dis,  dis,  dis));
    _faces[4].push_back(Point3d( dis, -dis,  dis));
    _faces[4].push_back(Point3d( dis,  dis,  dis));

    // back
    _faces[5].push_back(Point3d( dis, -dis, -dis));
    _faces[5].push_back(Point3d( dis,  dis, -dis));
    _faces[5].push_back(Point3d(-dis, -dis, -dis));
    _faces[5].push_back(Point3d(-dis,  dis, -dis));
}

void Skybox::draw()
{
    for (int i = 0; i < _faces.size(); ++i) {
        PointArray & face = _faces[i];
        Texture& tex = _textures[i];
        tex.bind();
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < face.size(); ++j) {
            const Point3d & p = face[j];
            const Point2d & uv = _uvs[j];
            glTexCoord2d(uv.x(), uv.y());
            glVertex3d(p.x(), p.y(), p.z());
        }
        glEnd();
        tex.unbind();
    }
}
