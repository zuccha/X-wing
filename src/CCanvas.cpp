#include "CCanvas.h"
#include "Base.h"
#include "Sphere.h"

using namespace std;

//-----------------------------------------------------------------------------


void CCanvas::keyPressEvent(QKeyEvent *event) {
//    std::cout << "Pressed " << event->key() << std::endl;
    double delta = 0.5;
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
    case Qt::Key_Shift:
        _camera.translate({0.0, -delta, 0.0});
        break;
    case Qt::Key_Control:
        _camera.translate({0.0, delta, 0.0});
        break;
//    case Qt::Key_Left:
//        _camera.rotate(-1.0, {0,1.0,0});
//        break;
//    case Qt::Key_Right:
//        _camera.rotate(1.0, {0,1.0,0});
//        break;
//    case Qt::Key_Up:
//        _camera.rotate(-1.0, {1.0,0,0});
//        break;
//    case Qt::Key_Down:
//        _camera.rotate(1.0, {1.0,0,0});
//        break;
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

    // One light source
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    /*
     * The position is transformed by the modelview matrix when glLightfv is called (just as if it were
     * a point), and it is stored in eye coordinates. If the w component of the position is 0.0,
     * the light is treated as a directional source. Diffuse and specular lighting calculations take
     * the light's direction, but not its actual position, into account, and attenuation is disabled.
     * Otherwise, diffuse and specular lighting calculations are based on the actual location of the
     * light in eye coordinates, and attenuation is enabled. The default position is (0,0,1,0); thus,
     * the default light source is directional, parallel to, and in the direction of the -z axis.
     */
    GLfloat lightpos[] = {0.0, -100.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    GLfloat lightAmb[]  = {0.3, 0.3, 0.3};
    GLfloat lightDiff[] = {1.0, 1.0, 1.0};
    GLfloat lightSpec[] = {0.5, 0.5, 0.5};

    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiff);

    /*
     * Before you can use the texture you need to initialize it by calling the setTexture() method.
     * Before you can use OBJ/PLY model, you need to initialize it by calling init() method.
     */

//    _camera_pos = {1.0, -10.f, -10.0};
    tau = 1;
    _x_wing.init();
    _vader_tie.init();
    _terrain.generate(100);
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
    double f = -1000.0;

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
    Point3d pos = _camera.getPos();
//    double angle = _camera.getAngle() * PI/180;
//    std::cout << angle << std::endl;
//    Point3d axis = _camera.getRotAxis();
    Point3d target = {pos.x(), pos.y(), (pos.z()-1.0)};
    switch(_view) {
    case Perspective:
        lookAt(pos.x(), pos.y(), pos.z(),

               target.x(), target.y(), target.z(),

               0.0, 1.0, 0.0);
//        glTranslatef(pos.x(), pos.y(), pos.z());
//        glRotatef(angle, axis.x(), axis.y(), axis.z());
        break;

    case Cockpit:
        // Maybe you want to have an option to view the scene from the train cockpit, up to you
        break;
    }
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
    setView(View::Perspective);

    // You can always change the light position here if you want
    GLfloat lightpos[] = {10.0f, 100.0f, 10.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    // Terrain
    glPushMatrix();
    _terrain.draw();
    glPopMatrix();

    // X-wing
    glPushMatrix();
    //glTranslatef(0, 7.5+sin(tau/10)*0.25, 0);
//    glRotatef(sin(tau/6)*2.5, 1.0f, 1.0f, 0.0f);
    glTranslatef(3, 7, -2);
    glRotatef(tau / 4, 0.0, 1.0, 0.0);
//    glRotatef(-51.5f, 0.0, 1.0, 0.0);
    _x_wing.draw();
    glPopMatrix();

    // Vader tie fighter
    glPushMatrix();
    glTranslatef(0, 15, -10);
    _vader_tie.draw();
    glPopMatrix();

    tau++;
}
