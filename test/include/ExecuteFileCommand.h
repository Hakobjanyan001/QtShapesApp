#ifndef EXECUTEFILECOMMAND_H
#define EXECUTEFILECOMMAND_H

// project library
#include "Command.h"

// third-pary library
#include <QString>

class MainWindow;

class ExecuteFileCommand : public Command {
public:
    ExecuteFileCommand(MainWindow* window, const QString& filePath);
    void execute() override;

private:
    MainWindow* m_window;
    QString m_filePath;
};

#endif // EXECUTEFILECOMMAND_H
