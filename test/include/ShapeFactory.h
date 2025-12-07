#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Shape.h"
#include <string>
#include <vector>

class ShapeFactory {
public:
	static std::unique_ptr<Shape> createShape(const std::string& type, 
					const std::string& name, const std::vector<double>& cords);
};

#endif // SHAPEFACTORY_H
