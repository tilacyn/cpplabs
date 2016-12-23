#include <cstdio>
#include "../include/board.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

Board::Board(){
	arr_ = new int* [10];
	for(int i = 0; i < 10; i++){
		arr_[i] = new int[10];
		for(int j = 0; j < 10; j++){
			arr_[i][j] = 0;
		}
	}
	n_ = 0;
}

Board::~Board(){
	for(int i = 0; i < 10; i++){
		delete [] arr_[i];
	}
	delete [] arr_;
}

void Board::makeMove_x(const int x, const int y){
	arr_[x][y] = 1;	
}

void Board::makeMove_o(const int x, const int y){
	arr_[x][y] = 2;	
}

int Board::isWin(const int x, const int y) const{
	int rcount = 1;
	for(int curx = max(1, x - 3); curx <= min(9, x + 4); curx++){
		if(arr_[curx][y] && arr_[curx][y] == arr_[curx - 1][y]){
			rcount++;
		} else rcount = 1;
		if(rcount == 5) return arr_[curx][y];
	}
	rcount = 1;
	printf("kek");
	for(int cury = max(1, y - 3); cury <= min(9, y + 4); cury++){
		if(arr_[x][cury] && arr_[x][cury] == arr_[x][cury - 1]){
			rcount++;
		} else rcount = 1;
		//printf("\n%d\n", rcount);
		if(rcount == 5) return arr_[x][cury];
	}
	rcount = 1;
	for(int cur = max(- 3, -min(x, y) + 1); cur <= min(4, min(9 - y, 9 - x)); cur++){
		if(arr_[x + cur][y + cur] && arr_[x + cur][cur + y] == arr_[x + cur - 1][cur + y - 1]){
			rcount++;
		} else rcount = 1;
		if(rcount == 5) return arr_[x][y];
	}

	for(int cur = max(- 3, -min(x, 9 - y) + 1); cur <= min(4, min(y, 9 - x)); cur++){
		if(arr_[x + cur][y - cur] && arr_[x + cur][y - cur] == arr_[x + cur - 1][y - cur + 1]){
			rcount++;
		} else rcount = 1;
		//printf("\n%d\n", rcount);
		if(rcount == 5) return arr_[x][y];
	}
	return 0;
}

bool Board::canMove(const int x, const int y) const{
	bool temp = x < 0 || y < 0 || x >= 10 || y >= 10;
	if(temp) return 0;
	else return !arr_[x][y];
}

int** Board::get_board() const{
	return arr_;
}




