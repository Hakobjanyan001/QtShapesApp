#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

// system/standart library
#include <memory>
#include <vector>
#include <string>

class Command;

class CommandFactory {
public:
    static std::unique_ptr<Command> createCommand(class MainWindow* window, const std::vector<std::string>& tokens);
};

#endif // COMMANDFACTORY_H
