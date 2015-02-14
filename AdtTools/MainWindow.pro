TEMPLATE = app
TARGET = Window

QT        += core gui 

HEADERS   += Window.h
SOURCES   += main.cpp \
    Window.cpp
FORMS     += ../resource/untitled.ui    
RESOURCES +=

QMAKE_CXXFLAGS += -std=c++0x