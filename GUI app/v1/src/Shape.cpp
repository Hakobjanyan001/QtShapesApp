// project libraries
#include "Shape.h"

Shape::Shape( const std::string& name ) : m_name( name ) {}

std::string Shape::getName() const { return m_name; }

QGraphicsItem* Shape::getItem() const { return m_item; }
