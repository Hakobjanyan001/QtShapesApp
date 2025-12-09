// project library
#include "ConnectShapesCommand.h"
#include "mainwindow.h"

ConnectShapesCommand::ConnectShapesCommand(MainWindow* window, const QString& s1, const QString& s2)
    : m_window(window), m_shape1(s1), m_shape2(s2) {}

void ConnectShapesCommand::execute() {
    m_window->handleConnect({m_shape1, m_shape2});
}
