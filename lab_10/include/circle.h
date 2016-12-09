#pragma once

#include "figure.h"

class Circle : public Figure {
  public:
	Circle(int id, int x, int y, int radius, const char* label);
	bool is_inside(int x, int y) const;
	void print() const;
	void zoom(int factor);
	~Circle();
  private:
	int r;
	char* label;
};

