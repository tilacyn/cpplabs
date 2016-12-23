#include "board.h"

class View {
	public:
		View(Board &board);
		void showBoard() const;
		int doGameCycle();
		void make_silent();
	private:
		Board* board_;	
		int done_moves_;
		bool silent_;
};
