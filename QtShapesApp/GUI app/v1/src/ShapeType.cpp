// project libraries
#include "ShapeType.h"

// system/standart library
#include <algorithm>
#include <cctype>

std::optional<ShapeType> ShapeTypeFromString( const std::string& str ) { 
	std::string lower = str;  // poqratar sarqenq 
	std::transform(lower.begin(), lower.end(), lower.begin(), 
				   [](unsigned char c) { return std::tolower(c); });

	if ( lower == "line" ) return ShapeType::LINE;
	if ( lower == "triangle" ) return ShapeType::TRIANGLE;
	if ( lower == "rectangle" ) return ShapeType::RECTANGLE;
	if ( lower == "square" ) return ShapeType::SQUARE;
	
	return ShapeType::UNKNOWN;
}
