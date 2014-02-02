/** @file TicTacToeAction.h
 *
 * Implementa as ações para o \link Games::TicTacToe Jogo-da-Velha\endlink.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_TICTACTOE_ACTION_H
#define GAMES_TICTACTOE_ACTION_H

#include "TicTacToeState.h"
#include "Action.hpp"

namespace Games {
/** Define o escopo do \link TicTacToe Jogo-da-Velha\endlink. */
namespace TicTacToe {
/** Define a ação de marcar uma célula no \link TicTacToe Jogo-da-Velha\endlink. */
class TicTacToeAction : public IIA::Action<TicTacToeState> {
public:
	/** Construtor. Indica onde marcar e a que custo. */
	TicTacToeAction(const Games::Grids::Coord2D &c, /**< coordenada a marcar */
				    Mark m, /**< marca a ser feita */
				    double cost /**< custo associado */
				    )
	: IIA::Action<TicTacToeState>(cost), coord(c), mark(m) {}

	/** Retorna a referência para uma cópia desta instância. */
	TicTacToeAction *clone() const{
		return new TicTacToeAction(coord, mark, cost);
	}

	/** Marca a coordenada armazenada no estado dado. */
	void execute(TicTacToeState &game) const {
		if(!game.valid(coord))
			throw std::invalid_argument("Invalid coordinate to mark.");

		game[coord] = mark;
	}

	/** Retorna uma string que descreve a ação. */
	std::string to_string() const{
		return "Marcar " + IIA::Utils::String::to_string(mark) + " " + IIA::Utils::String::to_string(coord);
	}

	// Attributes
	/** A coordenada onde marcar. */
	Games::Grids::Coord2D coord;
	/** A marca a fazer. */
	Mark mark;
};
} // namespace TicTacToe
} // namespace Games

#endif // GAMES_TICTACTOE_ACTION_H
