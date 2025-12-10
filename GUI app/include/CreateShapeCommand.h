#ifndef CREATESHAPECOMMAND_H
#define CREATESHAPECOMMAND_H

// project library
#include "Command.h"

// system/standart library
#include <vector>
#include <string>

/*
    CreateShapeCommand – Handles all create_* commands
    Supported:
      create_line, create_triangle, create_rectangle, create_square
      create line/triangle/rectangle/square (legacy)
      Name uniqueness check
      Coordinate parsing with {x,y} or (x,y) support
*/

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
