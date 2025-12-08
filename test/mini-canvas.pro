QT += core gui widgets

CONFIG += c++11

TARGET = canvas
TEMPLATE = app

INCLUDEPATH += include

SOURCES += src/main.cpp src/mainwindow.cpp src/ShapeFactory.cpp src/Line.cpp src/Triangle.cpp src/Rectangle.cpp src/Square.cpp
HEADERS += include/mainwindow.h include/Shape.h include/ShapeFactory.h include/Line.h include/Triangle.h include/Rectangle.h include/Square.h
