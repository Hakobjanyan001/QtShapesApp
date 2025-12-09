// project library
#include "ExecuteFileCommand.h"
#include "mainwindow.h"

// third-pary library
#include <QFile>
#include <QTextStream>

ExecuteFileCommand::ExecuteFileCommand(MainWindow* window, const QString& path)
    : m_window(window), m_filePath(path) {}

void ExecuteFileCommand::execute() {
    m_window->handleExecuteFile({"execute_file", m_filePath});
}
