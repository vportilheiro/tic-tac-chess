/*	ttc.cpp
 *
 *	Main class for game. See ttc.h for more.
 *
 *	Vasco Portilheiro, 2016
 */

#include <iostream>
#include "ttc.h"

/* Constructor. Sets the game to be in the placing phase,
 * allowing pieces to be placed on the board, and initializes
 * the board to be empty. */
TTC::TTC() {
	board = new Color[BOARD_SIZE * BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			set_color(i, j, Color::NONE);
		}
	}
	placing = true;
	num_pieces = 0;
	current_player = Color::WHITE;
	game_over = false;
	winner = Color::NONE;
	last_row = -1;
	last_col = -1;
}

/* Destructor */
TTC::~TTC() {
	delete[] board;
}

/* Places a piece at a given location for the player.
 * Returns false if the game is past the placing phase
 * (both players have placed all their pieces), if the location
 * is already occupied, or if it is not the player's turn.
 * Finally, checks if the piece placed was the final piece,
 * in which case placing is set to false.
 */
bool TTC::place(int row, int col, TTC::Color player) {
	if (	!placing ||
			!is_valid_position(row, col) ||
			!is_empty(row, col) ||
			current_player != player )
		return false;

	/* Place the piece, and update state */
	set_color(row, col, player);
	last_row = row;
	last_col = col;
	check_game_over();


	/* If the game is not over, switch players and increment
	 * the number of pieces. Otherwise, the winner is set, and
	 * current player will be NONE. */
	if (!game_over) {
		if (current_player == Color::WHITE)
			current_player = Color::BLACK;
		else if (current_player == Color::BLACK)
			current_player = Color::WHITE;
		++num_pieces;

		if (num_pieces == 2*NUM_PIECES)
			placing = false;
	}
	return true;
}

/* Moves a piece from one position to another, returning true
 * if the move was valid and successful. */
bool TTC::move(int start_row, int start_col, int end_row, int end_col) {
	if (placing || !is_valid_position(start_row, start_col) ||
				   !is_valid_position(end_row, end_col) ||
				   is_empty(start_row, start_col) ||
				   !is_empty(end_row, end_col))
		return false;
	set_color(end_row, end_col, color_at(start_row, start_col));
	set_color(start_row, start_col, Color::NONE);
	last_row = end_row;
	last_col = end_col;
	check_game_over();
	if (game_over) {
		if (current_player == Color::WHITE)
			current_player = Color::BLACK;
		else if (current_player == Color::BLACK)
			current_player = Color::WHITE;
	}
	return true;
}

/* Returns the current player */
TTC::Color TTC::get_current_player() {
	return current_player;
}

/* Returns whether the game is in the placing phase */
bool TTC::in_placing_phase() {
	return placing;
}

/* Returns the approproiate index into the board for
 * a given position */
TTC::Color TTC::color_at(int row, int col) {
	return board[row*BOARD_SIZE + col];
}

/* Returns true when the game is over */
bool TTC::over() {
	return game_over;
}

/* Returns the winner of the game */
TTC::Color TTC::get_winner() {
	return winner;
}	

/* ===== Private functions ===== */

/* Returns true if a position has no piece on it */
bool TTC::is_empty(int row, int col) {
	return (is_valid_position(row, col) && color_at(row, col) == Color::NONE);
}

/* Returns true is a position is on the board (in bounds) */
bool TTC::is_valid_position(int row, int col) {
	return (row < BOARD_SIZE && col < BOARD_SIZE);
}

/* Checks whether the last move won the game.
 * If the game is over, the winning palyer is set,
 * and the current player variable is set to NONE. */
void TTC::check_game_over() {
	if (check_columns() || check_rows() ||
		check_diagonals()) {
		winner = color_at(last_row, last_col);
		game_over = true;
		current_player = Color::NONE;
	}
}

/* Check whether any of the columns contains
 * the winnining number of consecutive pieces. */
bool TTC::check_columns() {
    bool res = false;
	for (int col = 0; col < BOARD_SIZE && !res;  ++col) {
		int consec_pieces = 0;
		Color color = Color::NONE;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			if (color_at(i, col) == color && color != Color::NONE) {
				if (++consec_pieces == WINNING_NUM) {
					res = true;
					break;
				}
			} else {
				consec_pieces = 1;
				color = color_at(i, col);
			}
		}
	}
	return res;
}

/*
bool find_hit_in_a_raw( int i) {
	bool res = 0;
	assert( i >= 0 && i <= BOARD_SIZE);
    int j = 1;
	while (!res) {
		int n = 1;
		while (j < BOARD_SIZE && color_at(i,j) == color_at(i,j-1)) {
			j++;
			n++;
		}
		if (n >= WINNING_NUM && color_at(i,j-1) != Color::NONE) res = true;
	}
}
*/
/* Check whether any of the rows contains
 * the winnining number of consecutive pieces. */
bool TTC::check_rows() {
	for (int row = 0; row < BOARD_SIZE; ++row) {
		int consec_pieces = 0;
		Color color = Color::NONE;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			if (color_at(row, i) == color && color != Color::NONE) {
				if (++consec_pieces == WINNING_NUM) {
					return true;
				}
			} else {
				consec_pieces = 1;
				color = color_at(row, i);
			}
		}
	}
	return false;
}

/* Check whether either diagonal has
 * the winning number of consecutive pieces. */
bool TTC::check_diagonals() {
	int consec_pieces = 0;
	Color color = Color::NONE;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (color_at(i, i) == color && color != Color::NONE) {
			if (++consec_pieces == WINNING_NUM) {
			   	return true;
			}
		} else {
			consec_pieces = 1;
			color = color_at(i, i);
		}
	}
	consec_pieces = 0;
	color = Color::NONE;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (color_at(BOARD_SIZE - i, i) == color && color != Color::NONE) {
			if (++consec_pieces == WINNING_NUM) {
				return true;
			}
		} else {
			consec_pieces = 1;
			color = color_at(BOARD_SIZE - i, i);
		}
	}
	return false;
}

/* Sets the color in the given position
 * in the board. */
void TTC::set_color(int i, int j, TTC::Color color) {
	board[i*BOARD_SIZE + j] = color;
}
