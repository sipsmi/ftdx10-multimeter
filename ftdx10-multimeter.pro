QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /usr/include/qwt
INCLUDEPATH += /usr/include/KF5/KWidgetsAddons
#LIBS += -l qwt-qt5
LIBS +=  -l qwt-qt5 /usr/lib/x86_64-linux-gnu/qt5/plugins/designer/kwidgetsaddons5widgets.so



CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -lxmlrpc++
unix|win32: LIBS += -lxmlrpc_client++
