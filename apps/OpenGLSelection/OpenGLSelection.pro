######################################################################
# Automatically generated by qmake (2.00a) Wed Dec 13 20:28:40 2006
######################################################################

TEMPLATE = app
TARGET +=
DEPENDPATH += . ../Maths/ ../Utils/ ../Geometry
INCLUDEPATH += . ../Maths/ ../Utils/ ../Geometry
CONFIG -= qt
CONFIG += release opengl
LIBS += -lglut
QMAKE_CXXFLAGS_RELEASE += -pedantic -ansi

# Input
# Input
HEADERS += Vector2D.h \
           Vector3D.h \
           Quaternion.h \
           Matrix3x3.h \
           special.h \
           BasicCamera.h \
           QuakeCamera.h \
           QuatCamera.h \
           DraggableInterface.h \
           MiscUtils.h \
           Keybinding.h \
           GLUtils.h \
           GraphicsMaths.h
SOURCES += main.cpp \
           Vector2D.cpp \
           Vector3D.cpp \
           Quaternion.cpp \
           Matrix3x3.cpp \
           special.cpp \
           BasicCamera.cpp \
           QuakeCamera.cpp \
           QuatCamera.cpp \
           DraggableInterface.cpp \
           MiscUtils.cpp \
           Keybinding.cpp \
           GLUtils.cpp \
           GraphicsMaths.cpp
