#####################################################################
# Automatically generated by qmake (2.01a) Fr 23. Okt 14:07:47 2009 #
#####################################################################

CONFIG += release

TEMPLATE = app
TARGET = GLRender
DEPENDPATH += .
INCLUDEPATH += . \

QT += core gui xml opengl

# Header files
HEADERS += ./Base.h \
           ./CCanvas.h \
           ./Point2.h \
           ./Point3.h \
           ./GLRender.h \
           ./Sphere.h \
           ./texture.hpp \
           ./tinyply.h \
    XWing.h \
    Model.h \
    Component.h \
    perlinnoise.hpp \
    terrain.hpp \
    Tie.h

# Source files
SOURCES += ./CCanvas.cpp \
           ./GLRender.cpp \
           ./main.cpp \
           ./Sphere.cpp \
           ./tinyply.cpp \
    XWing.cpp \
    Model.cpp \
    Component.cpp \
    terrain.cpp \
    Tie.cpp

# Forms
FORMS += ./GLRender.ui

# Install
install_media.path = ../build/GLRender.app/Contents/MacOS/
install_media.files += ../media/
INSTALLS += install_media
