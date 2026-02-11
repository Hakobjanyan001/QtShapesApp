// project library
#include "ExecuteFileCommand.h"
#include "mainwindow.h"
#include "Constants.h"

// third-pary library
#include <fstream>
#include <string>

ExecuteFileCommand::ExecuteFileCommand(MainWindow* window, 
									   const QString& path)
    								   : m_window(window), 
									   m_filePath(path){
}

void ExecuteFileCommand::execute() {
    std::ifstream file(m_filePath.toStdString());

    if( !file.is_open() ) {
		m_window->log("Cannot open file " + m_filePath, Constants::logErrorColor);
        return;
    }

	m_window->log("Executing file" + m_filePath, Qt::cyan);

    std::string line;
    while( std::getline(file, line) ) {
		
		if( !line.empty() && line.back() == '\r') {
			line.pop_back();
		}
	
		size_t start = line.find_first_not_of(" \t\n");
		if( start == std::string::npos ) {
			continue;
		}
		
		size_t end = line.find_last_not_of(" \t\n");
	
		line = line.substr(start, end - start + 1);

        if( line.empty() || line[0] == '#' ) {
            continue;
		}
		
		m_window->parseAndExecute(QString::fromStdString(line));
    }

	m_window->log("File executed successfully ", Constants::logSuccessColor);
}
