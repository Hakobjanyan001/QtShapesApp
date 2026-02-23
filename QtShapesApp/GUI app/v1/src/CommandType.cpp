// project libraries
#include "CommandType.h"

// system/standart library
#include <string>
#include <optional>
#include <cctype>
#include <algorithm>

std::optional<CommandType> commandTypeFromString( const std::string& str ) {

    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    if( lower == "create" || lower == "create_shape" ) return CommandType::CREATE_SHAPE;
    if( lower == "connect" || lower == "connect_shapes" ) return CommandType::CONNECT_SHAPES;
    if( lower == "execute_file" ) return CommandType::EXECUTE_FILE;

    return CommandType::UNKNOWN;

}
