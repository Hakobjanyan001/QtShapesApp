#ifndef LINE_H
#define LINE_H

// project libraries
#include "Shape.h"

class Line : public Shape {
private:
	double m_x1, m_y1, m_x2, m_y2;
public:
	Line( const std::string& name, 
		  double x1, 
		  double y1, 
		  double x2, 
		  double y2 );
	
	QGraphicsItem* draw( QGraphicsScene* scene ) override;
	
	QPointF center () const override; 
};


#endif // LINE_H
