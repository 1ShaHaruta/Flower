QT += testlib
QT += gui core sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += qt warn_on depend_includepath testcase

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


TEMPLATE = app

SOURCES +=  tst_my_test.cpp
SOURCES += \
    delete_form.cpp \
    input_device.cpp \
    insert_form.cpp \
    mainwindow.cpp \
    validator.cpp

HEADERS += \
    delete_form.h \
    input_device.h \
    insert_form.h \
    mainwindow.h \
    validator.h

FORMS += \
    delete_form.ui \
    insert_form.ui \
    mainwindow.ui
