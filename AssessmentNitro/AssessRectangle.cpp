#include "stdafx.h"
#include "AssessRectangle.h"

bool AssessRectangle::operator ==(const AssessRectangle& v) const
{
	return ( (x == v.x) && (y == v.y) && (width == v.width) && (height == v.height) );
}

void AssessRectangle::set(int _x, int _y, int _width, int _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
}

bool AssessRectangle::isValid()
{
	return x >= 0 && y >= 0 && width > 0 && height > 0;
}

bool AssessRectangle::intersect(AssessRectangle& comp, AssessRectangle& intersectRect)
{
	int x1 = std::max(x, comp.x);
	int y1 = std::max(y, comp.y);
	int x2 = std::min(x + width, comp.x + comp.width);
	int y2 = std::min(y + height, comp.y + comp.height);

	if (x1 >= x2 || y1 >= y2)
		return false;

	intersectRect.set(x1, y1, x2 - x1, y2 - y1);
	return true;
}

std::string AssessRectangle::dump()
{
	std::stringstream rt;
	rt << "(" << x << ", " << y << "), ";
	rt << "w=" << width << ", ";
	rt << "h=" << height << ".";

	return rt.str();
}
