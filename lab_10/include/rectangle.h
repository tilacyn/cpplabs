#include "figure.h"

class Rectangle : public Figure {
public:
	Rectangle(int id, int x, int y, int width, int height);
	bool is_inside(int x, int y) const;
	void print()const;
	void zoom(int factor);
	~Rectangle();
private:
	int w;
	int h;
};
