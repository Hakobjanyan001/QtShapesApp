// project libraries
#include "CommandFactory.h"
#include "CreateShapeCommand.h"
#include "ConnectShapesCommand.h"
#include "ExecuteFileCommand.h"
#include "CommandType.h"
#include "ShapeType.h"

// third-pary library
#include <QString>

// system/standart library
#include <algorithm>
#include <cctype>

std::unique_ptr<Command> CommandFactory::createCommand( class MainWindow* window, const std::vector<std::string>& etokens) {

    if( etokens.empty() ) return nullptr;
	
	std::string firstLower = etokens[0];
    std::transform(firstLower.begin(), firstLower.end(), firstLower.begin(), 
                   [](unsigned char c){ return std::tolower(c); });
	
	if (firstLower.find("create_") == 0) {
        std::string typeStr = firstLower.substr(7);
        auto shapeTypeOpt = ShapeTypeFromString(typeStr);
        if (shapeTypeOpt && *shapeTypeOpt != ShapeType::UNKNOWN) {
            return std::make_unique<CreateShapeCommand>(window, etokens);
        }
	}

	if( firstLower == "connect" ) {
        QString shape1, shape2;

        if( etokens.size() == 3 ) {
            shape1 = QString::fromStdString(etokens[1]).remove('{').remove('}');
            shape2 = QString::fromStdString(etokens[2]).remove('{').remove('}');
        } else {
            for( size_t i = 1; i < etokens.size() - 1; ++i ) {
                std::string tokenLower = etokens[i];
                std::transform(tokenLower.begin(), tokenLower.end(), tokenLower.begin(), ::tolower);
                if( tokenLower == "-object_name_1" ) {
                    shape1 = QString::fromStdString(etokens[i + 1]).remove('{').remove('}');
                } else if( tokenLower == "-object_name_2" ) {
                    shape2 = QString::fromStdString(etokens[i + 1]).remove('{').remove('}');
                }
            }
        }

        if( shape1.isEmpty() || shape2.isEmpty() ) return nullptr;
        return std::make_unique<ConnectShapesCommand>(window, shape1, shape2);
    }

    if( firstLower == "execute_file" && etokens.size() >= 2 ) {
        return std::make_unique<ExecuteFileCommand>(window, QString::fromStdString(etokens[1]));
    }

    return nullptr;
}
