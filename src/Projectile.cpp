#include "Projectile.h"
#include <QtOpenGL>

Projectile::Projectile(const Point3d & p, double angle)
    : _p(p)
    , _angle(angle)
{
    init();
}

void Projectile::init()
{
    unsigned int n = 10;

    _faces.resize(n);
    _phi = 2.0 * PI / double(n);

    // Make bottom and top
    _bottom.push_back(Point3d(0.0, 0.0, -_length));
    _top.push_back(Point3d(0.0, 0.0, _length));
    for(unsigned int i = 0; i < n; ++i) {
        double x1 = cos(_radius * _phi * i);
        double y1 = sin(_radius * _phi * i);
        double x2 = cos(_radius * _phi * (i + 1));
        double y2 = sin(_radius * _phi * (i + 1));
        // Bottom
        _bottom.push_back(Point3d(x1, y1, -_length));
        // Top
        _top.push_back(Point3d(x1, y1, _length));
        // Faces
        PointArray & face = _faces[i];
        face.push_back(Point3d(x1, y1, -_length));
        face.push_back(Point3d(x2, y2, -_length));
        face.push_back(Point3d(x1, y1,  _length));
        face.push_back(Point3d(x2, y2,  _length));
    }
    _bottom.push_back(Point3d(1.0, 0.0, -_length));
    _top.push_back(Point3d(1.0, 0.0, _length));
}

void Projectile::draw()
{
//    glColor3d(1.0,  0.01, 0.57);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//    glEnable(GL_COLOR_MATERIAL);

    // Draw bottom
    glBegin(GL_TRIANGLE_FAN);
    for (unsigned int i = 0; i < _bottom.size(); ++i) {
      glVertex3d(_bottom[i].x(), _bottom[i].y(), _bottom[i].z());
    }
    glEnd();

    // Draw top
    glBegin(GL_TRIANGLE_FAN);
    for (unsigned int i = 1; i < _top.size(); ++i) {
      glVertex3d(_top[i].x(), _top[i].y(), _top[i].z());
    }
    glEnd();

    // Draw faces
    for (unsigned int i = 0; i < _faces.size(); ++i) {
      glBegin(GL_TRIANGLE_STRIP);
      PointArray & face = _faces[i];
      glVertex3d(face[0].x(), face[0].y(), face[0].z());
      glVertex3d(face[1].x(), face[1].y(), face[1].z());
      glVertex3d(face[2].x(), face[2].y(), face[2].z());
      glVertex3d(face[3].x(), face[3].y(), face[3].z());
      glEnd();
    }
}

void Projectile::move(double time)
{
    glPushMatrix();
    glTranslated(_p.x(), _p.y(), _p.z());
    glRotated(_angle, 0, 1, 0);
    glTranslated(0.0, 0.0, _t);
    glScaled(0.1, 0.1, 0.1);
    this->draw();
    glPopMatrix();
    _t += 5;
}
