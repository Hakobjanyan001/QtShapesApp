// Project Libraries
#include "ShapeFactory.h"
#include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Square.h"


std::unique_ptr<Shape> ShapeFactory::createShape( ShapeType etype, 
														 const std::string& name, 
														 const std::vector<double>& coords ) {
	switch ( etype ) {
		case ShapeType::LINE:
	    	if( coords.size() != 4 ) return nullptr;
			return std::make_unique<Line>( name,
										   coords[0],
										   coords[1], 
										   coords[2], 
										   coords[3]);
		case ShapeType::TRIANGLE:
			if( coords.size() != 6 ) return nullptr;
	    	return std::make_unique<Triangle>( name,
										   coords[0],
										   coords[1], 
										   coords[2], 
										   coords[3],
										   coords[4],
										   coords[5]);
       case ShapeType::RECTANGLE:
			if( coords.size() == 4 ) {
            	return std::make_unique<Rectangle>( name, 
													coords[0], 
													coords[1], 
													coords[2], 
													coords[3]);
			} else if( coords.size() == 8) {
            	return std::make_unique<Rectangle>( name, 
												coords[0], 
												coords[1], 
												coords[2], 
												coords[3],
												coords[4],
												coords[5],
												coords[6],
												coords[7]);
	   		} 
			return nullptr;
		   
	   case ShapeType::SQUARE:
				if( coords.size() == 4 ) {
		        	return std::make_unique<Square>( name, 
													 coords[0], 
													 coords[1], 
													 coords[2], 
													 coords[3]);
				} else if( coords.size() == 8) {
    		       	return std::make_unique<Square>( name, 
													coords[0], 
													coords[1], 
													coords[2], 
													coords[3],
													coords[4],
													coords[5],
													coords[6],
													coords[7]);
			   }
				return nullptr;
	   
		default:
	        return nullptr;
	        
	}
}
