#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
private:
	double m_x1, m_y1, m_x2, m_y2, m_x3, m_y3, m_x4, m_y4;
public:
	Rectangle(const std::string& name, double x1, double y1, double x2, double y2);
	Rectangle(const std::string& name, 
					double x1, double y1, double x2, double y2, 
					double x3, double y3, double x4, double y4);

	void draw(QGraphicsScene* scene) override;
};

#endif // RECTANGLE_H
