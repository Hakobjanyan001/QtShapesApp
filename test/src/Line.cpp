// project libraries
#include "Line.h"

// third-par
#include <QGraphicsLineItem>

Line::Line( const std::string& name, 
			double x1, 
			double y1, 
			double x2, 
			double y2 )
    		: Shape(name), 
			m_x1(x1), 
			m_y1(y1), 
			m_x2(x2), 
			m_y2(y2) {}

QGraphicsItem* Line::draw( QGraphicsScene* scene )  {
    m_item = scene->addLine(m_x1, m_y1, m_x2, m_y2, QPen(Qt::blue));
    return m_item;
}

QPointF Line::center() const {
	return QPointF( (m_x1 + m_x2) / 2.0, (m_y1 + m_y2) / 2.0 );
}
