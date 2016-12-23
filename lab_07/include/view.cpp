#include <cstdio>
#include "../include/board.h"
#include <iostream>
#include "../include/view.h"

using namespace std;

View::View(Board &board){
	board_ = &board;
	done_moves_ = 0;
	silent_ = 0;
}

void View::showBoard() const{
	int** arr = board_->get_board();
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(arr[i][j] == 1) printf("X ");
			if(arr[i][j] == 2) printf("O ");
			if(arr[i][j] == 0) printf(". ");
		}
		printf("\n");
	}
}

int View::doGameCycle(){
	if(done_moves_) printf("\n");
	
	if(!silent_)
		this->showBoard();
	if(done_moves_ % 2 == 0) printf("O Move: ");
	else printf("X Move: ");
	string instr;
	getline(cin, instr);
	bool flag = 0;
	//string check
	if(instr.length() != 3 && instr.length() != 5) flag = 1;

	if(!flag && instr.length() == 5){
		if(instr.substr(0, 5) == "-1 -1") return -1;
		else flag = 1;
	}

	if(!flag && instr[0] - '0' >= 0 && instr[0] - '0' <=9) flag = 0;
	else flag = 1;
	if(!flag && instr[2] - '0' >= 0 && instr[2] - '0' <=9) flag = 0;
	else flag = 1;
	if(!flag && instr[1] == ' ') flag = 0;
	else flag = 1;

	//end of the string check
	int x = instr[0] - '0';
	int y = instr[2] - '0';

	if(flag || !board_->canMove(x, y)){
		printf("Bad Move");
		return 0;
	}
	
	if(done_moves_ % 2 == 0){
		board_->makeMove_o(x, y);
	} else{
		board_->makeMove_x(x, y);
	}
	
	if(board_->isWin(x, y) || done_moves_ == 100){
		if(board_->isWin(x, y) == 1) return 1;
		else if(board_->isWin(x, y) == 2) return 2;
		else return 3;
	}
	done_moves_++;
	return 0;
}

void View::make_silent(){
	silent_ = 1;
}



