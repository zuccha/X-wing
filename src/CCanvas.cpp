#include "CCanvas.h"
#include "Base.h"
#include "Sphere.h"

using namespace std;

//-----------------------------------------------------------------------------


void CCanvas::keyPressEvent(QKeyEvent *event) {
//    std::cout << "Pressed " << event->key() << std::endl;
    double delta = 10.0;
    switch(event->key()) {
    case Qt::Key_W:
        _camera.translate({0.0, 0.0, -delta});
        break;
    case Qt::Key_A:
        _camera.translate({-delta, 0.0, 0.0});
        break;
    case Qt::Key_S:
        _camera.translate({0.0, 0.0, delta});
        break;
    case Qt::Key_D:
        _camera.translate({delta, 0.0, 0.0});
        break;
    case Qt::Key_Q:
        _camera.rotateZ(0.05);
        break;
    case Qt::Key_E:
        _camera.rotateZ(-0.05);
        break;
    case Qt::Key_Shift:
        _camera.translate({0.0, delta, 0.0});
        break;
    case Qt::Key_Control:
        _camera.translate({0.0, -delta, 0.0});
        break;
    case Qt::Key_Left:
        _camera.rotateX(-0.05);
        break;
    case Qt::Key_Right:
        _camera.rotateX(0.05);
        break;
    case Qt::Key_Up:
        _camera.rotateY(0.05);
        break;
    case Qt::Key_Down:
        _camera.rotateY(-0.05);
        break;
    }
}

void CCanvas::initializeGL()
{
    this->setFocusPolicy(Qt::StrongFocus);
    glClearColor(0.56f, 0.82f, 1.0f, 1.0f);			   // black background

    glClearDepth(1.0f);								   // depth buffer setup
    glEnable(GL_DEPTH_TEST);						   // enables depth testing
    glDepthFunc(GL_LEQUAL);							   // the type of depth testing to do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // really nice perspective calculations
    glShadeModel(GL_SMOOTH);

    /*
     * Before you can use the texture you need to initialize it by calling the setTexture() method.
     * Before you can use OBJ/PLY model, you need to initialize it by calling init() method.
     */

//    _camera_pos = {1.0, -10.f, -10.0};`
    tau = 0;
    _x_wing.init();
    _vader_tie.init();
    _terrain.generate(300);
    _skybox.init();

    _camera.setPosition(Point3d(1.0, 50.0, 30.0));
    _camera.rotateY(-PI/4);
}

//-----------------------------------------------------------------------------

void CCanvas::glPerspective(const GLdouble fovy, const GLdouble aspect, const GLdouble zNear, const GLdouble zFar)
{
    const GLdouble d = 1.0 / tan(fovy / 360.0 * PI);
    const GLdouble delta = zNear - zFar;

    GLdouble *mat = new GLdouble[16];

    mat[0] = d / aspect;
    mat[1] = 0.0;
    mat[2] = 0.0;
    mat[3] = 0.0;

    mat[4] = 0.0;
    mat[5] = d;
    mat[6] = 0.0;
    mat[7] = 0.0;

    mat[8]  = 0.0;
    mat[9]  = 0.0;
    mat[10] = (zNear + zFar) / delta;
    mat[11] = -1.0;

    mat[12] = 0.0;
    mat[13] = 0.0;
    mat[14] = 2.0 * zNear * zFar / delta;
    mat[15] = 0.0;

    glMultMatrixd(mat);

    delete[] mat;
}

void CCanvas::lookAt(const GLdouble eyex,
                     const GLdouble eyey,
                     const GLdouble eyez,
                     const GLdouble centerx,
                     const GLdouble centery,
                     const GLdouble centerz,
                     const GLdouble upx,
                     const GLdouble upy,
                     const GLdouble upz)
{
    GLdouble *mat = new GLdouble[16];

    // TODO: add computation for the lookat here!
    Point3d VP(eyex, eyey, eyez);
            Point3d q(centerx, centery, centerz);
            Point3d VUP(upx, upy, upz);
            Point3d VPN = VP-q;

          Point3d p_p = VP;
          Point3d z_p = VPN;
          z_p.normalize();
          Point3d x_p = VUP ^ z_p;
          Point3d y_p = z_p ^ x_p;

          mat[0] = x_p.x();
          mat[1] = y_p.x();
          mat[2] = z_p.x();
          mat[3] = 0;

          mat[4] = x_p.y();
          mat[5] = y_p.y();
          mat[6] = z_p.y();
          mat[7] = 0;

          mat[8] = x_p.z();
          mat[9] = y_p.z();
          mat[10] = z_p.z();
          mat[11] = 0;

          mat[12] = -(x_p * p_p);
          mat[13] = -(y_p * p_p);
          mat[14] = -(z_p * p_p);
          mat[15] = 1;

    glMultMatrixd(mat);

    delete[] mat;
}

void CCanvas::resizeGL(int width, int height)
{
    // set up the window-to-viewport transformation
    glViewport(0, 0, width, height);

    // vertical camera opening angle
    double beta = 60.0;

    // aspect ratio
    double gamma;
    if(height > 0) gamma = width / (double)height;
    else gamma = width;

    // front and back clipping plane at
    double n = -0.01;
    double f = -10000.0;

    // frustum corners
     double t = -tan(beta * 3.14159 / 360.0) * n;
     double b = -t;
     double r = gamma * t;
     double l = -r;

    // set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//     glFrustum(l,r, b,t, -n,-f);

    // alternatively, directly from alpha and gamma
    glPerspective(beta, gamma, -n, -f);
}

//-----------------------------------------------------------------------------

void CCanvas::setView(View _view) {
    Point3d pos;
    double pitch;
    double yaw;
    double roll;

    Point3d up = {sin(roll), cos(roll), 0.0};

    switch(_view) {
    case Perspective:
        pos = _camera.getPosition();
        pitch = _camera.getPitch();
        yaw = _camera.getYaw();
        roll = _camera.getRoll();
        break;

    case Cockpit:
        pos = _cockpit.getPosition();
        pitch = _cockpit.getPitch();
        yaw = _cockpit.getYaw();
        roll = _cockpit.getRoll();
        break;
    }

    Point3d target = {sin(yaw), sin(pitch), -cos(yaw)};
    target += pos;
    lookAt(pos.x(), pos.y(), pos.z(),
           target.x(), target.y(), target.z(),
           up.x(), up.y(), up.z());
}

void CCanvas::paintGL()
{
    // clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Setup the current view
    setView(View::Cockpit);

    //Skybox (not lit)
    glPushMatrix();
    _skybox.draw();
    glPopMatrix();

    GLfloat fogColor[4] = {0.85f,0.8f,0.69f,1.0f};

    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, 2.0f);             // Fog Start Depth
    glFogf(GL_FOG_END, 200.0f);             // Fog End Depth

    glEnable(GL_FOG);

    // One light source
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightAmb[]  = {0.6, 0.6, 0.6};
    GLfloat lightDiff[] = {1.0, 1.0, 1.0};
    GLfloat lightSpec[] = {0.5, 0.5, 0.5};

    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiff);

    // You can always change the light position here if you want
    GLfloat lightpos[] = {100.0f, 100.0f, 100.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    // Terrain
    glPushMatrix();
    _terrain.draw();
    glPopMatrix();

    // X-wing
    _x_wing.move(double(tau));

    // Vader tie fighter
    _vader_tie.move(double(tau));

    // Cockpit camera
    _cockpit.setYaw(-_x_wing.alpha() + PI);
    _cockpit.setRoll(_x_wing.beta());
    _cockpit.setPosition(_x_wing.p() + Point3d(0.0, 0.5, 0.0));

    tau += 0.02f;

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
}
