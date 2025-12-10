# Qt model
QT += core gui widgets

# Configs
CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = ShapeCanvas
TEMPLATE = app

# src files

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/Shape.cpp \
    src/ShapeFactory.cpp \
    src/Line.cpp \
    src/Triangle.cpp \
    src/Rectangle.cpp \
    src/Square.cpp \
    src/CheckShapeType.cpp \
    src/ShapeType.cpp \
    src/CommandFactory.cpp \
    src/CommandType.cpp \
    src/CreateShapeCommand.cpp \
    src/ConnectShapesCommand.cpp \
    src/ExecuteFileCommand.cpp \

HEADERS += \
    include/mainwindow.h \
    include/Shape.h \
    include/ShapeFactory.h \
    include/Line.h \
    include/Triangle.h \
    include/Rectangle.h \
    include/Square.h \
    include/CheckShapeType.h \
    include/ShapeType.h \
    include/CommandFactory.h \
    include/CommandType.h \
	include/Command.h \
	include/CreateShapeCommand.h \
    include/ConnectShapesCommand.h \
    include/ExecuteFileCommand.h

INCLUDEPATH += include

OBJECTS_DIR = build
