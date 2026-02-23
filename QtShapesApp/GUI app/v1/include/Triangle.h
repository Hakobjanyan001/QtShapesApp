#ifndef TRIANGLE_H
#define TRIANGLE_H

// project libraries
#include "Shape.h"

class Triangle : public Shape {

private:
	double m_x1, m_y1, m_x2, m_y2, m_x3, m_y3;
public:
	Triangle( const std::string& name, 
			  double x1, 
			  double y1,
			  double x2, 
			  double y2, 
			  double x3, 
			  double y3);
	
	QGraphicsItem* draw( QGraphicsScene* scene ) override;
	
	QPointF center() const override; 
};

#endif // TRIANGLE_H
