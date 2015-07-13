TEMPLATE = lib
#CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
    solve_qp.cpp \
    svm.cpp \
    data.cpp

HEADERS += \
    solve_qp.h \
    svm.h \
    timer.h \
    linear_algebra.h \
    data.h

CONFIG(debug, debug|release) {
    DEFINES += "BMRM_INFO"
}

CONFIG(release, debug|release) {
    DEFINES += "NDEBUG"
}



