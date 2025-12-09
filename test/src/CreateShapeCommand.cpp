// project library
#include "CreateShapeCommand.h"
#include "mainwindow.h" 

CreateShapeCommand::CreateShapeCommand(MainWindow* window, const std::vector<std::string>& tokens)
    : m_window(window), m_tokens(tokens) {}

void CreateShapeCommand::execute() {
    if (m_tokens.size() < 3) return;
    QString commandLine = QString::fromStdString(m_tokens[0]);
    for (size_t i = 1; i < m_tokens.size(); ++i)
        commandLine += " " + QString::fromStdString(m_tokens[i]);
    m_window->parseAndExecute(commandLine);
}
