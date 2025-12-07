#include "../include/Square.h"
#include <QGraphicsRectItem>
#include <cmath>
 
Square::Square(const std::string& name, double x1, double y1, double x2, double y2) 
		: Shape(name){
		double dx = x2 - x1;
		double dy = y2 - y1;
		double side = std::sqrt(dx*dx + dy*dy);
    	double px = -dy;
    	double py = dx;

	    m_x1 = x1;
	    m_y1 = y1;
	    m_x2 = x2;
	    m_y2 = y2;
	    m_x3 = x2 + px;
	    m_y3 = y2 + py;
	    m_x4 = x1 + px;
	    m_y4 = y1 + py;
	    m_side = side;
}

Square::Square(const std::string& name,
              double x1, double y1, double x2, double y2,
              double x3, double y3, double x4, double y4)
        : Shape(name) {
			m_x1 = x1; m_y1 = y1;
    		m_x2 = x2; m_y2 = y2;
    		m_x3 = x3; m_y3 = y3;
  			m_x4 = x4; m_y4 = y4;
}

QGraphicsItem* Square::draw(QGraphicsScene* scene) override {
    QPolygonF polygon;
    polygon << QPointF(m_x1, m_y1) << QPointF(m_x2, m_y2) 
             << QPointF(m_x3, m_y3) << QPointF(m_x4, m_y4);
    QGraphicsPolygonItem* item = scene->addPolygon(polygon, QPen(Qt::blue, 2), QBrush(Qt::blue));
    return item;
}
