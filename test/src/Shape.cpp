#include "Shape.h"

Shape::Shape(const std::string& name) : m_name(name) {}

virtual Shape::~Shape() {}

std::string Shape::getName() const {return m_name;}

