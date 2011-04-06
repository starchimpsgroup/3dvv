#-------------------------------------------------
#
# Project created by QtCreator 2011-01-18T01:27:31
#
#-------------------------------------------------

QT       += opengl

TARGET = Qt3DVectorViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    glperspective.cpp \
    glvector.cpp \
    glcoordinateaxes.cpp \
    glcolor.cpp \
    globject.cpp \
    glpoint.cpp \
    gltext.cpp \
    navigation.cpp \
    navigationlabel.cpp \
    preferences.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glperspective.h \
    glvector.h \
    glcoordinateaxes.h \
    glcolor.h \
    globject.h \
    glpoint.h \
    gltext.h \
    navigation.h \
    navigationlabel.h \
    preferences.h \
    settings.h

FORMS    += mainwindow.ui \
    navigation.ui \
    preferences.ui

OTHER_FILES += \
    README.markdown

RESOURCES += \
    Resouces/resouces.qrc
