#ifndef CREATESHAPECOMMAND_H
#define CREATESHAPECOMMAND_H

// project library
#include "Command.h"

// system/standart library
#include <vector>
#include <string>

class MainWindow;

class CreateShapeCommand : public Command {
public:
    CreateShapeCommand( MainWindow* window, 
						const std::vector<std::string>& tokens );
    
	void execute() override;

private:
    MainWindow* m_window;
    std::vector<std::string> m_tokens;
};

#endif // CREATESHAPECOMMAND_H
