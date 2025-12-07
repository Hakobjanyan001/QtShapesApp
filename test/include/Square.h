#ifndef SQUARE_H
#define SQUARE_H

#include <Shape.h>

class Square : public Shape {
private:
	double m_x1, m_y1, m_x2, m_y2, m_x3, m_y3, m_x4, m_y4;
	double m_x, m_y, m_side;
	bool useFourPoints = false;
public:
	Square(const std::string& name, double x1, double y1, double x2, double y2);
	Square(const std::string& name,	
					double x1, double y1, double x2, double y2, 
					double x3, double y3, double x4, double y4);

    double side() const {return m_side;}
	void draw(QGraphicsScene* scene) override;
};

#endif //SQUARE_H
