#include "rectangle.h"
#include "math.h"
#include "figure.h"
#include <cmath>
#include <cstdio>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y){
	w = width;
	h = height;
}

void Rectangle::print() const {
	printf("Rectangle %d x = %d y = %d width = %d height = %d\n", id, x, y, w, h);
}

bool Rectangle::is_inside(int x, int y) const {
	return (std::abs(x - this->x) <= w / 2) && (std::abs(y - this->y) <= h / 2);
}

void Rectangle::zoom(int factor){
	w *= factor;
	h *= factor;
}
Rectangle::~Rectangle(){
}

