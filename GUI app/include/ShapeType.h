#ifndef SHAPETYPE_H
#define SHAPETYPE_H

// system/standart library
#include <string>
#include <optional>

enum class ShapeType { 
	LINE,
	TRIANGLE,
	RECTANGLE,
	SQUARE,
	UNKNOWN
};

std::optional<ShapeType> ShapeTypeFromString( const std::string& str);

#endif // SHAPETYPE_H
