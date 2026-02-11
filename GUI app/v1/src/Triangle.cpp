// project libraries
#include "Triangle.h"
#include "Constants.h"

// third-party libraries
#include <QGraphicsPolygonItem>
#include <QPolygonF>


Triangle::Triangle( const std::string& name, 
	    			double x1, 
					double y1, 
					double x2,
					double y2, 
					double x3,
					double y3 )
					: Shape(name),
					m_x1(x1),
					m_y1(y1),
					m_x2(x2), 
					m_y2(y2), 
					m_x3(x3), 
					m_y3(y3) {}
	
QGraphicsItem* Triangle::draw( QGraphicsScene* scene ) {
	QPolygonF polygon;
	polygon << QPointF(m_x1, m_y1) 
			<< QPointF(m_x2, m_y2) 
			<< QPointF(m_x3, m_y3);

	QPen pen(Constants::shapePenColor);
    pen.setWidth(Constants::shapePenWidthDefault);
    QBrush brush(Constants::shapeBrushColor);

	m_item = scene->addPolygon(polygon, pen, brush);
	return m_item;
}

QPointF Triangle::center() const {
		return QPointF((m_x1 + m_x2 + m_x3) / 3.0, (m_y1 + m_y2 + m_y3) / 3.0);
}
