#include "ShapeFactory.h"
#include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Square.h"
#include <memory>

static std::unique_ptr<Shape> ShapeFactory::createShape(const std::string& type, 
					const std::string& name, const std::vector<double>& cords) {
	if(type == "line" && cords.size() == 4) {
		return std::make_unique<Line>(name, cords[0], cords[1], cords[2], cords[3]);  
	} else if(type == "triangle" && cords.size() == 6) {
		return std::make_unique<Triangle>(name,cords[0], cords[1], cords[2], cords[3], cords[4], cords[5]);
	} else if(type == "rectangle") {
		if(cords.size() == 4) {
			return std::make_unique<Rectangle>(name, cords[0], cords[1], cords[2], cords[3]);
		} else if(cords.size() == 8) {
			return std::make_unique<Rectangle>(name, cords[0], cords[1], cords[2], cords[3], cords[4], cords[5], cords[6], cords[7]);
		} 
	}else if(type == "square") {
		if(cords.size() == 4) {
			return std::make_unique<Square>(name, cords[0], cords[1], cords[2], cords[3]);
		} else if(cords.size() == 8) {
			return std::make_unique<Square>(name, cords[0], cords[1], cords[2], cords[3], cords[4], cords[5], cords[6], cords[7]);
		}
	}
	return nullptr;
}
