#ifndef SQUARE_H
#define SQUARE_H

// project libraries
#include <Shape.h>

class Square : public Shape {
private:
	double m_x1, m_y1, m_x2, m_y2, m_x3, m_y3, m_x4, m_y4;
public:
	Square( const std::string& name, 
			double x1, 
			double y1, 
			double x2, 
			double y2 );
	
	Square( const std::string& name,	
			double x1, 
			double y1,
			double x2, 
			double y2, 
			double x3, 
			double y3, 
			double x4, 
			double y4 );

    
	QGraphicsItem* draw(QGraphicsScene* scene) override;

	QPointF center() const override;
};

#endif //SQUARE_H
