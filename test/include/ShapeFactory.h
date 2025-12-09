#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

// third-pary
#include "Shape.h"
#include "ShapeType.h"

// system/standart library
#include <string>
#include <vector>
#include <memory>

class ShapeFactory {
public:
	static std::unique_ptr<Shape> createShape( ShapeType etype, 
											   const std::string& name,
											   const std::vector<double>& coords);

};

#endif // SHAPEFACTORY_H
