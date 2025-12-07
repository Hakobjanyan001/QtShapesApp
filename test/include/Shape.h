#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <QGraphicsScene>
#include <QGraphicsItem>

class Shape { // Shape-y abstract class-a, iranic chpetqa objekt stexcenq
protected:    
	std::string m_name;
public:
	Shape(const std::string& name);
	virtual ~Shape();

	std::string getName() const;
	virtual QGraphicsItem* draw(QGraphicsScene* scene) = 0; // bolor jarangac klassnery partadir override petqa anen
}

#endif // SHAPE_H
