#include <iostream>
#include "ttc.h"

const void print_game(TTC &game) {
    /* Top edge */
    for (int i = 0; i < TTC::BOARD_SIZE; ++i) {
		std::cout << " ___";
    }
	std::cout << std::endl;

    /* Rows */
    for (int i = 0; i < TTC::BOARD_SIZE; ++i) {
		std::cout << "|";
        for (int j = 0; j < TTC::BOARD_SIZE; ++j) {
			std::cout << " ";
			if (game.color_at(i, j) == TTC::WHITE) std::cout << "X";
			if (game.color_at(i, j) == TTC::BLACK) std::cout << "O";
			if (game.color_at(i, j) == TTC::NONE) std::cout << "_";
            std::cout << " |";
        }
		std::cout << std::endl;
		std::cout << "|";
        for (int j = 0; j < TTC::BOARD_SIZE; ++j) {
			std::cout << "___|";
        }
		std::cout << std::endl;
    }
}

int main() {
	TTC game;
	int row, col, row2, col2;
	print_game(game);
	while (!game.over()) {
		if (game.in_placing_phase()) {
			while (true) {
				std::cin >> row;
				std::cin >> col;
				if (game.place(row, col, game.get_current_player())) break;
				else std::cout << "Invalid placement. Please try again." << std::endl;
			}
			print_game(game);
		} else {
			while (true) {
				std::cin >> row;
				std::cin >> col;
				std::cin >> row2;
				std::cin >> col2;
				if(game.move(row, col, row2, col2)) break;
				else std::cout << "Invalid move. Please try again." << std::endl;
			}
			print_game(game);
		}
	}
	std::cout << "Game over!" << std::endl;
	return 0;
}
