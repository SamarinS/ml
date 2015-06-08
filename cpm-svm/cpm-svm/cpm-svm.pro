TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


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

CONFIG(debug, debug|release) {
    DEFINES += "BMRM_INFO"
}

CONFIG(release, debug|release) {
    DEFINES += "NDEBUG"
}



