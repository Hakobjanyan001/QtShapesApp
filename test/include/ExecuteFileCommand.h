#ifndef EXECUTEFILECOMMAND_H
#define EXECUTEFILECOMMAND_H

// project library
#include "Command.h"

// third-pary library
#include <QString>

class MainWindow;

class ExecuteFileCommand : public Command
{
public:
    // Այս կոնստրուկտորը պետք է լինի հենց այսպես
    ExecuteFileCommand(MainWindow* window, const QString& path);

    void execute() override;

private:
    MainWindow* m_window;
    QString m_filePath;
};

#endif // EXECUTEFILECOMMAND_H
