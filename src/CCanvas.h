/************************************************************************/
/* Guards                                                               */
/************************************************************************/
#ifndef CCANVAS_H
#define CCANVAS_H

#include <iostream>
#include <QtOpenGL>
#include <QGLWidget>
#include <QTimer>

#include "Base.h"
#include "texture.hpp"

#include "Model.h"
#include "XWing.h"
#include "Tie.h"
#include "perlinnoise.hpp"
#include "terrain.hpp"
#include "Camera.h"
#include "Skybox.h"

using namespace std;

/************************************************************************/
/* Canvas to draw                                                       */
/************************************************************************/
class CCanvas : public QGLWidget
{
  Q_OBJECT

public:
    explicit CCanvas(QWidget *parent = 0) : QGLWidget(parent),
//        _x_wing   ("./media/models/", "train.obj")
        _x_wing   ("./media/models/x-wing/", "x-wing.obj"),
        _vader_tie("./media/models/vader-tie/", "vader-tie.obj"),
        _skybox(Skybox())
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
        timer->start(10);
    }

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent * event);

private:

    void lookAt(const GLdouble eyex,
                const GLdouble eyey,
                const GLdouble eyez,
                const GLdouble centerx,
                const GLdouble centery,
                const GLdouble centerz,
                const GLdouble upx,
                const GLdouble upy,
                const GLdouble upz);

    void glPerspective(const GLdouble fovy,
                       const GLdouble aspect,
                       const GLdouble zNear,
                       const GLdouble zFar);


    enum View {
        Perspective = 0,    // View the scene from a perspective (from above, from a side, or whatever)
        Cockpit             // View the scene from the train cockpit (if you want, or whatever other view)
    };

    float generateHeight(float x, float y, const siv::PerlinNoise& perlin);
    void drawTerrain();
    Point3d computeNormal(float x, float y, const siv::PerlinNoise& perlin);


    void setView(View _view);

    Camera _camera;
    Camera _cockpit;

    // Models and textures
    Terrain _terrain;
    XWing _x_wing;
    Tie   _vader_tie;
    Skybox _skybox;

    GLfloat tau;
};

#endif 
