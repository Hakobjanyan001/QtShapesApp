// project libraries
#include "CommandFactory.h"
#include "CreateShapeCommand.h"
#include "ConnectShapesCommand.h"
#include "ExecuteFileCommand.h"
#include "CommandType.h"

// third-pary library
#include <QString>

std::unique_ptr<Command> CommandFactory::createCommand( class MainWindow* window, const std::vector<std::string>& etokens) {

    if ( etokens.empty() ) return nullptr;

    auto cmdType = commandTypeFromString(etokens[0]);
    if ( !cmdType || *cmdType == CommandType::UNKNOWN ) {
        return nullptr;
    }

    switch (*cmdType) {     
        case CommandType::CREATE_SHAPE:
			return std::make_unique<CreateShapeCommand>(window, etokens);

        case CommandType::CONNECT_SHAPES:
            if (etokens.size() >= 3) {
                return std::make_unique<ConnectShapesCommand>(
					window,
                    QString::fromStdString(etokens[1]),
                    QString::fromStdString(etokens[2])
                );
            }
            return nullptr;

        case CommandType::EXECUTE_FILE:
            if (etokens.size() >= 2) {
                return std::make_unique<ExecuteFileCommand>(
                    window,
					QString::fromStdString(etokens[1])
                );
            }
            break;

        default:
            break;
    }
	return nullptr;
}
