// project library
#include "ExecuteFileCommand.h"
#include "mainwindow.h"

// third-pary library
#include <QFile>
#include <QTextStream>
#include "ExecuteFileCommand.h"
#include <QMetaObject>

ExecuteFileCommand::ExecuteFileCommand(MainWindow* window, const QString& path)
    : m_window(window), m_filePath(path)
{
}

void ExecuteFileCommand::execute()
{
    QFile file(m_filePath);

    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        QMetaObject::invokeMethod(m_window, "log",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, "Cannot open file: " + m_filePath),
                                  Q_ARG(QColor, Qt::red));
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if ( line.isEmpty() || line.startsWith("#") || line.startsWith("//") )
            continue;

        QMetaObject::invokeMethod(m_window, "log",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, ">> " + line),
                                  Q_ARG(QColor, Qt::darkGray));

        QMetaObject::invokeMethod(m_window, "parseAndExecute",
                               Qt::QueuedConnection,
                               Q_ARG(QString, line));
    }

    QMetaObject::invokeMethod(m_window, "log",
                              Qt::QueuedConnection,
                              Q_ARG(QString, "File executed: " + m_filePath),
                              Q_ARG(QColor, Qt::green));

    file.close();
}
