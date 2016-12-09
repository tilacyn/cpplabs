#include "../include/circle.h"
#include <cstdio>
#include "math.h"
#include "figure.h"
#include <cstring>
#include "string.h"
#include <cmath>

Circle::Circle(int id, int x, int y, int radius, const char* label) : Figure(id, x, y){
	r = radius;
	this->label = new char[strlen(label) + 1];
	strcpy(this->label, label);
}

void Circle::print() const {
	printf("Circle %d x = %d y = %d radius = %d label = %s\n", id, x, y, r, label);
}

bool Circle::is_inside(int x, int y) const {
	return ((x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <= r *r);
}

void Circle::zoom(int factor){
	r *= factor;
}
Circle::~Circle(){
	delete [] label;
}
