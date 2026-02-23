// project library
#include "CheckShapeType.h"


std::vector<ShapeType> CheckShapeType::getPossibleTypes( size_t coordCount ) {
	std::vector<ShapeType> result;

	switch( coordCount ) {
		case 4:
			result.push_back(ShapeType::LINE);
			result.push_back(ShapeType::RECTANGLE);
			result.push_back(ShapeType::SQUARE);
			break;

		case 6:
        	result.push_back(ShapeType::TRIANGLE);
        	break;

        case 8:
            result.push_back(ShapeType::RECTANGLE);
            result.push_back(ShapeType::SQUARE);
            break;
	}
	return result;
}

bool CheckShapeType::isValid( ShapeType etype, size_t coordCount ) {
	auto possible = getPossibleTypes(coordCount);
	for( auto p : possible ) {
		if( p == etype ) return true; 
	}
	return false;
}
