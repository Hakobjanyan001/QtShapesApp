// project library
#include "CreateShapeCommand.h"
#include "mainwindow.h" 
#include "ShapeType.h"
#include "ShapeFactory.h"
#include "CheckShapeType.h"

// third-pary library
#include <QColor> 

CreateShapeCommand::CreateShapeCommand(MainWindow* window, 
                                       const std::vector<std::string>& tokens)
    : m_window(window), m_tokens(tokens) {}

void CreateShapeCommand::execute() {
   
	 if( m_tokens.size() < 3 ) {
        m_window->log("Error: Too few arguments for create", Qt::red);
        return;
    }

	std::string firstToken = m_tokens[0];
    std::string firstLower = firstToken;
    std::transform(firstLower.begin(), firstLower.end(), firstLower.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    std::string typeStr;
    QStringList args;
    size_t argStart = 1;  

    if( firstLower.find("create_") == 0 ) {
        typeStr = firstLower.substr(7);  
    } else {
        if( m_tokens.size() < 4 ) return;
        typeStr = firstLower;
        argStart = 1; 
        typeStr = m_tokens[1];
        std::transform(typeStr.begin(), typeStr.end(), typeStr.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        argStart = 2;
    }

    auto shapeTypeOpt = ShapeTypeFromString(typeStr);
    if( !shapeTypeOpt || *shapeTypeOpt == ShapeType::UNKNOWN ) {
        m_window->log("Unknown shape type: " + QString::fromStdString(typeStr), Qt::red);
        return;
    }
    ShapeType shapeType = *shapeTypeOpt;

    QString fullArgs;
    for( size_t i = argStart; i < m_tokens.size(); ++i ) {
        fullArgs += QString::fromStdString(m_tokens[i]) + " ";
    }
    args = fullArgs.trimmed().split(' ', Qt::SkipEmptyParts);

    QString name = m_window->extractName(args);
    if( name.isEmpty() ) {
        m_window->log("Error: Name not provided", Qt::red);
        return;
    }

    std::vector<double> coords = m_window->extractCoordinates(args);
    if( coords.empty() ) {
        m_window->log("Error: No coordinates provided", Qt::red);
        return;
    }

    if( !CheckShapeType::isValid(shapeType, coords.size()) ) {
        m_window->log("Invalid coordinate count for " + QString::fromStdString(typeStr), Qt::red);
        return;
    }

    std::string stdName = name.toStdString();
    auto shape = ShapeFactory::createShape(shapeType, stdName, coords);
    if( !shape ) {
        m_window->log("Failed to create shape '" + name + "'", Qt::red);
        return;
    }

    QGraphicsItem* item = shape->draw(m_window->getScene());
    if( item ) {
		if(m_window->firstShape) {
			m_window->scene->clear();
			item = shape->draw(m_window->getScene());
			m_window->firstShape = false;
		}	
		
		QString name = QString::fromStdString(stdName);
		if( m_window->shapes.contains(name)) {
			m_window->log("Error shape already exists ", Qt::red);
			delete shape.release();
			return;
		}

        m_window->shapes[name] = item;
        m_window->m_ownedShapes[name] = shape.release();
        m_window->addShapeLabel(item, name);
        m_window->log("Created " + QString::fromStdString(typeStr) + " '" + name + "'", Qt::green);
    } else {
        m_window->log("Failed to draw shape '" + name + "'", Qt::red);
    }

}	
