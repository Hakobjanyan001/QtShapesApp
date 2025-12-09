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
    if (m_tokens.size() < 3) {
        m_window->log("Error: Too few arguments for create", Qt::red);
        return;
    }

    QString fullLine;
    for (const auto& t : m_tokens) fullLine += QString::fromStdString(t) + " ";
    
    QStringList args = fullLine.split(' ', Qt::SkipEmptyParts);
    if (args.size() < 3) return;

    QString typeStr = args[1];
    std::string stdType = typeStr.toLower().toStdString();
    auto shapeTypeOpt = ShapeTypeFromString(stdType);
    if (!shapeTypeOpt || *shapeTypeOpt == ShapeType::UNKNOWN) {
        m_window->log("Unknown shape type: " + typeStr, Qt::red);
        return;
    }
    ShapeType shapeType = *shapeTypeOpt;

    QString name = m_window->extractName(args);
    if (name.isEmpty()) {
        m_window->log("Error: Name not provided", Qt::red);
        return;
    }

    std::vector<double> coords = m_window->extractCoordinates(args);
    if (!CheckShapeType::isValid(shapeType, coords.size())) {
        m_window->log("Invalid coordinate count for " + typeStr, Qt::red);
        return;
    }

    std::string stdName = name.toStdString();
    auto shape = ShapeFactory::createShape(shapeType, stdName, coords);
    if (!shape) {
        m_window->log("Failed to create shape", Qt::red);
        return;
    }

    
    QGraphicsItem* item = shape->draw(m_window->scene); 
    if (item) {
        m_window->shapes[QString::fromStdString(stdName)] = item;
        m_window->m_ownedShapes[QString::fromStdString(stdName)] = shape.release();

        m_window->addShapeLabel(item, name);
        m_window->log("Created " + typeStr + " '" + name + "'", Qt::green);
    } else {
        m_window->log("Failed to draw shape", Qt::red);
    }
}
