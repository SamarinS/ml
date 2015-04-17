TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "D:/DevTools/boost_1_57_0"

SOURCES += main.cpp \
    data.cpp \
    solve_qp.cpp \
    svm.cpp

HEADERS += \
    data.h \
    linear_algebra.h \
    solve_qp.h \
    svm.h \
    timer.h



