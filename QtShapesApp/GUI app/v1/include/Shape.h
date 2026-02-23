#ifndef SHAPE_H
#define SHAPE_H

// project Libraries
#include "Constants.h"

// system/standatr library
#include <string>

// third-pary
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPointF>

class Shape { // Shape-y abstract class-a, iranic chenqkara objekt stexcenq
protected:    
	std::string m_name;
	QGraphicsItem* m_item = nullptr;
public:
	Shape( const std::string& name );
	virtual ~Shape() = default;

	std::string getName() const;
	virtual QGraphicsItem* draw( QGraphicsScene* scene ) = 0; // bolor jarangac klassnery override petqa anen
	virtual QGraphicsItem* getItem() const;   
	virtual QPointF center() const = 0;
};

#endif // SHAPE_H
