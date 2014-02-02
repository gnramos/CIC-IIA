/** @file TicTacToeState.h
 *
 * Implementa um estado para o \link Games::TicTacToe Jogo-da-Velha\endlink.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_TICTACTOE_STATE_H
#define GAMES_TICTACTOE_STATE_H

#include "Game.hpp"
// #include "Games_Match.hpp"
// #include "Games_Player.hpp"
#include "State.hpp"

namespace Games {
/** Define o escopo do \link TicTacToe Jogo-da-Velha\endlink. */
namespace TicTacToe {
/** Enumera os possíveis estados da casa. */
enum Mark {
	EMPTY, 	/**< A casa está vazia. */
	NOUGHT, /**< A casa é 'O'. */
	CROSS	/**< A casa é 'X'. */
};

/** Converte as marcas do jogo em string. */
static std::ostream &operator <<(std::ostream &os, Mark mark) {
	switch(mark) {
	case EMPTY:  os << " "; break;
	case NOUGHT: os << "O"; break;
	case CROSS:  os << "X"; break;
	default: break;
	}
	return os;
}

/** Retorna a marca oposta a dada. */
static Mark opponent_mark(const Mark &mark) {
	switch(mark) {
	case NOUGHT: return CROSS;
	case CROSS:  return NOUGHT;
	default: throw std::invalid_argument("Invalid mark.");
	}
}

/** Define um estado do \link TicTacToe Jogo-da-Velha\endlink. O estado é a representação do tabuleiro,
 * uma matriz de três linhas por três colunas em que cada célula pode assumir os
 * um valor estabelecido por Mark. */
class TicTacToeState : public IIA::State<TicTacToeState>, public Games::Grids::Grid2D<Mark> {
public:
	/** Construtor de um tabuleiro vazio. */
	TicTacToeState() : Games::Grids::Grid2D<Mark>(3, 3, EMPTY) {}
	/** Construtor de um tabuleiro como cópia do dado. */
	TicTacToeState(const TicTacToeState &state) : Games::Grids::Grid2D<Mark>(state) {}

	/** Indica se a instância é menor que o estado dado. */
	bool operator< (const TicTacToeState &that) const {
		if(this == &that) return false;
		return (this->grid < that.grid);
	}

	/** Indica se a instância é igual ao estado dado. */
	bool operator== (const TicTacToeState &that) const {
		if(this == &that) return true;
		return (this->grid == that.grid);
	}

	/** Define a instância como cópia do estado dado. */
	TicTacToeState &operator= (const TicTacToeState &that) {
		if(this != &that) {
			this->grid.assign(that.grid.begin(), that.grid.end());
		}
		return *this;
	}

	/** Converte o estado em string. */
	friend std::ostream &operator <<(std::ostream &os, const TicTacToeState &state) {
		os << static_cast<Games::Grids::Grid2D<Mark> >(state);
		return os;
	}
};
} // namespace TicTacToe
} // namespace Games

#endif // GAMES_TICTACTOE_STATE_H
