QT += core gui widgets

CONFIG += c++11

TARGET = mini-canvas
TEMPLATE = canvas

SOURCES += main.cpp mainwindow.cpp ShapeFactory.cpp Line.cpp Triangle.cpp Rectangle.cpp Square.cpp
HEADERS += mainwindow.h Shape.h ShapeFactory.h Line.h Triangle.h Rectangle.h Square.h
