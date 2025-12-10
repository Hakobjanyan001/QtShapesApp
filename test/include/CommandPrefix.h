#ifndef COMMANDPREFIX_H
#define COMMANDPREFIX_H

// system/standart library
#include <string>
#include <optional>
#include <algorithm>
#include <cctype>

enum CommandPrefix {  
    CREATE,
    CONNECT,
    EXECUTE_FILE,
    UNKNOWN
};

std::optional<CommandPrefix> prefixFromString(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if( lower.find("create_") == 0 ) return CREATE;
    if( lower.find("connect_") == 0 ) return CONNECT;
    if( lower.find("execute_file_") == 0 ) return EXECUTE_FILE;

    if( lower == "connect" ) return CONNECT;
    if( lower == "execute_file" ) return EXECUTE_FILE;

    return UNKNOWN;

}

#endif // COMMANDPREFIX_H
