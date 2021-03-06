######################################################################
# Automatically generated by qmake (2.00a) Mon Mar 13 14:24:29 2006
######################################################################

TEMPLATE = app
TARGET +=
DEPENDPATH += . .. ../../Maths/ ../../Utils/ ../../Kinematics
INCLUDEPATH += . .. ../../Maths/ ../../Utils/ ../../Kinematics
CONFIG -= qt
CONFIG += release opengl
LIBS += -lglut
QMAKE_CXXFLAGS_RELEASE += -pedantic -ansi

# Input
HEADERS += KinematicJoint.h \
           KinematicModel.h \
           Visualisation.h \
           BiovisionJoint.h \
           BiovisionReader.h \
           BiovisionAnimation.h \
           BiovisionDisplay.h \
           MiscUtils.h \
           Vector3D.h \
           Quaternion.h \
           Matrix3x3.h \
           ExponentialMap.h \
           special.h \
           BasicCamera.h \
           QuakeCamera.h \
           Keybinding.h \
           GLUtils.h

SOURCES += main.cpp \
           KinematicJoint.cpp \
           BiovisionJoint.cpp \
           BiovisionReader.cpp \
           BiovisionAnimation.cpp \
           BiovisionDisplay.cpp \
           MiscUtils.cpp \
           Vector3D.cpp \
           Quaternion.cpp \
           Matrix3x3.cpp \
           ExponentialMap.cpp \
           special.cpp \
           BasicCamera.cpp \
           QuakeCamera.cpp \
           Keybinding.cpp \
           GLUtils.cpp
