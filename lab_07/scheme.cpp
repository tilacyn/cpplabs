#include "scheme.h"

Scheme::Scheme(int capacity){
	figures_ = new Figure*[capacity];
	size = 0;
}

Scheme::~Scheme(){
	for(int i = 0; i < size; i++){
		delete figures_[i];
	}
}

void Scheme::push_back_figure(Figure* fg){
	figures_[size] = fg;
	size++;
}
	
void Scheme::remove_figure(int id){
	int i = 0;
	for(; i < size; i++){
		if(figures_[i]->get_id() == id){
			break;
		}
	}
	for(int j = i; j < size; j++){
		figures_[j] = figures_[j + 1];
	}
	size--;
}





void Scheme::print_all_figures(){
	for(int i = 0; i < size; i++){
		figures_[i]->print();
	}
}
void Scheme::zoom_figure(int id, int factor){
	for(int i = 0; i < size; i++){
		if(figures_[i]->get_id() == id){
			figures_[i]->zoom(factor);
		}
	}
}
Figure* Scheme::is_inside_figure(int x, int y){
	for(int i = 0; i < size; i++){
		if(figures_[i]->is_inside(x, y)){
			return figures_[i];
		}
	}
	return figures_[0];
}

void Scheme::move(int id, int new_x, int new_y){
	for(int i = 0; i < size; i++){
		if(figures_[i]->get_id() == id){
			figures_[i]->move(new_x, new_y);
		}
	}
}
