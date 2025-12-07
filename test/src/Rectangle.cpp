#include "Rectangle.h"
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QPolygonF>
#include <QPointF>
#include <algorithm>

Rectangle::Rectangle(const std::string& name, double x1, double y1, double x2, double y2)
    : Shape(name) { 
	double left = std::min(x1, x2); 
	double right = std::max(x1, x2);
    double top = std::min(y1, y2);
    double bottom = std::max(y1, y2);
    m_x1 = left;   m_y1 = top;
    m_x2 = right;  m_y2 = top;
    m_x3 = right;  m_y3 = bottom;
    m_x4 = left;   m_y4 = bottom;
}

Rectangle::Rectangle(const std::string& name,
             double x1, double y1, double x2, double y2,
             double x3, double y3, double x4, double y4)
  			 : Shape(name) {
		     m_x1 = x1; m_y1 = y1;
		     m_x2 = x2; m_y2 = y2;
		     m_x3 = x3; m_y3 = y3;
		     m_x4 = x4; m_y4 = y4;
}

QGraphicsItem* Rectangle::draw(QGraphicsScene* scene) override {
    QPolygonF polygon;
    polygon << QPointF(m_x1, m_y1) << QPointF(m_x2, m_y2) 
             << QPointF(m_x3, m_y3) << QPointF(m_x4, m_y4);
    QGraphicsPolygonItem* item = scene->addPolygon(polygon, QPen(Qt::darkGreen), QBrush(Qt::green));
    return item;
}
