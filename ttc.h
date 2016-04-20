/*	ttc.h
 *
 *	Main class for the game, which is played as follows on a 4x4 grid.
 *	There are two players, each of which has four pieces.
 *	This final objective of the game is to have your pieces
 *	in a row of four, vertically, horizontally, or diagonally.
 *  Play begins with the players take turns placing the pieces on the grid.
 *  After all the pieces have been placed, players can move any one pieces
 *  into any open adjecent space (along either a row or a diagonal).
 *  At any point, including during the placing of the pieces, if a player
 *  has their four pieces aligned, they win.
 *
 *	Vasco Portilheiro, 2016
 */

#ifndef _TTC_H_
#define _TTC_H_

class TTC
{
public:
	
	/* Colors to represent the players and their pieces on the board */
	enum Color {
		WHITE = 1,
		BLACK = -1,
		NONE = 0 
	};

	static const int BOARD_SIZE = 4;
	static const int NUM_PIECES = 4;
	static const int WINNING_NUM = 4;

	/* Constructor */
	TTC();

	/* Destructor */
	~TTC();

	/* Function to place a piece for a player at a given position. Returns true if
	 * the move is successful (valid), and false otherwise */
	bool place(int row, int col, Color player);

	/* Funciton to move a piece from on position to another. Returns
	 * true if the move is successful (valid), and false otherwise. */
	bool move(int start_row, int start_col, int end_row, int end_col);

	/* Returns the player whose turn it is */
	Color get_current_player();

	/* Returns whether the game is in the placing phase */
	bool in_placing_phase();

	/* Returns the color on the board for a given row and column */
	Color color_at(int row, int col);

	/* Returns true when the game is over */
	bool over();

	/* Returns the player who won the game when the game is over,
	 * and NONE otherwise */
	Color get_winner();

private:

	/* Current state of the 4x4 board, where each entry is a piece */	
	Color* board;

	/* Boolean for whether the game is in the placing phase */
	bool placing;

	/* Player whose turn it is */
	Color current_player;

	/* Counts total pieces on board */
	int num_pieces;

	/* Winner of the; NONE if the game is not over */
	Color winner;

	/* True if the game is over */
	bool game_over;

	/* Stores the location of the last changed position */
	int last_row;
	int last_col;

	/* Returns whether a position on the board is empty. Also
	 * returns false if the position is invalid. */
	bool is_empty(int row, int col);

	/* Checks whether a given position is on the board */
	bool is_valid_position(int row, int col);

	/* Checks whether the last move won the game.
	 * If the game is over, the winning player is set,
	 * game_over is set, and the current player in set to NONE. */
	void check_game_over();
	bool check_columns();
	bool check_rows();
	bool check_diagonals();
	
	/* Sets the color in the board for a given row and column */
	void set_color(int row, int col, Color color);
};

#endif
