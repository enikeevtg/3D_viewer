macx {  #win32, macx, unix
    QT       += core gui openglwidgets
    LIBS     += -framework GLUT -framework OpenGL -framework Cocoa
} else {
    QT       += core gui opengl
    LIBS     += -lOpenGL -lGLU -lglut
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../02_model_loading/01_getGeometryInfo.c \
    ../02_model_loading/02_getComponentsCount.c \
    ../02_model_loading/03_getComponents.c \
    ../02_model_loading/04_getVertex.c \
    ../02_model_loading/05_getFacet.c \
    ../02_model_loading/06_getRange.c \
    ../02_model_loading/07_structClean.c \
    ../03_affine_transformations/affine_transformations.c \
    eopenglwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../02_model_loading/model_loading.h \
    ../03_affine_transformations/affine_transformations.h \
    ../3D_viewer.h \
    eopenglwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
