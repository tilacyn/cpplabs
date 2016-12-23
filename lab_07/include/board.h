#pragma once

class Board {
	public:
		Board();
		~Board();
		void makeMove_x(const int x, const int y);
		void makeMove_o(const int x, const int y);
		int** get_board() const;
		bool canMove(const int x, const int y) const;
		int isWin(const int x, const int y) const;		

	protected:
		int** arr_;
		int n_;
};
