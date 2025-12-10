// project library
#include "ExecuteFileCommand.h"
#include "mainwindow.h"

// third-pary library
#include <QFile>
#include <QTextStream>
#include <QMetaObject>

ExecuteFileCommand::ExecuteFileCommand(MainWindow* window, 
									   const QString& path)
    								   : m_window(window), 
									   m_filePath(path){
}

void ExecuteFileCommand::execute() {
    QFile file(m_filePath);

    if( !file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
		m_window->log("Cannot open file " + m_filePath, Qt::red);
        return;
    }

	m_window->log("Executing file" + m_filePath, Qt::cyan);

    QTextStream in(&file);
    while( !in.atEnd() ) {
        QString line = in.readLine().trimmed();
        if( line.isEmpty() || line.startsWith("#") || line.startsWith("//") )
            continue;
		m_window->parseAndExecute(line);
    }

	m_window->log("File executed successfully ", Qt::green);
    file.close();
}
