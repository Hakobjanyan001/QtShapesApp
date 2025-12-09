#ifndef COMMANDTYPE_H
#define COMMANDTYPE_H

// system/standart library
#include <optional>
#include <string>

enum class CommandType {
    CREATE_SHAPE,
    CONNECT_SHAPES,
    EXECUTE_FILE,
    UNKNOWN
};

std::optional<CommandType> commandTypeFromString(const std::string& str);

#endif // COMMANDTYPE_H
