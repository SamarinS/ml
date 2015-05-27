TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L"../build-cpm-svm-Desktop-Debug" -lcpm-svm

SOURCES += main.cpp

