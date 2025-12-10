#ifndef CONNECTSHAPESCOMMAND_H
#define CONNECTSHAPESCOMMAND_H

// project library
#include "Command.h"

// third-pary library
#include <QString>

class MainWindow;

class ConnectShapesCommand : public Command {
public:
    ConnectShapesCommand( MainWindow* window, const 
						QString& shape1, 
						const QString& shape2 );
    
	void execute() override;

private:
    MainWindow* m_window;
    QString m_shape1, m_shape2;
};

#endif // CONNECTSHAPESCOMMAND_H
