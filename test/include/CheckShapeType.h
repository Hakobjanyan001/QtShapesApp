#ifndef CHECKSHAPETYPE_H
#define CHECKSHAPETYPE_H

// project Libraries
#include "ShapeType.h"

// system/standart library
#include <vector>
#include <optional>

class CheckShapeType {
public:
	static std::vector<ShapeType> getPossibleTypes( size_t coordCount );
	static bool isValid( ShapeType etype, size_t coordCount );
};

#endif //CHECKSHAPETYPE_H
