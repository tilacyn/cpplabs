#include <cstdio>
#include "../include/board.h"
#include <iostream>
#include <cstring>
#include "../include/view.h"

int main(int argc, char **argv){
	Board board = Board();
	View view = View(board);
	if(!strcmp(argv[argc - 1], "silent")){
		view.make_silent();
	}
	bool flag = 0;
	for(int i = 0; i < 100; i++){
		int res = view.doGameCycle();
		if(res == -1){ printf("Draw\n");
			flag = 1;
			break;
		}
		if(res == 2){ printf("O wins\n");
			flag = 1;
			break;
		}
		if(res == 1){ printf("X wins\n");
			flag = 1;			 
			break;
		}	
	}
	if(!flag)
		printf("Draw\n");
	return 0;
}
