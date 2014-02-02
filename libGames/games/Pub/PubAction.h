/** @file PubAction.h
 *
 * Declaração de uma ação no jogo Pub.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_PUB_ACTION_H
#define GAMES_PUB_ACTION_H

#include "Game.hpp"
#include "Match.hpp"
#include "Player.hpp"
#include "PubState.h"

namespace Games {
namespace Pub {
/** Define a ação de marcar posicionar duas marcas no jogo Pub. */
class PubAction : public IIA::Action<PubState> {
public:
	/** Construtor. Indica onde marcar e a que custo. */
	PubAction(const unsigned int &first_mark, /**< a primeira coluna a marcar */
			  const unsigned int &second_mark, /**< a segunda coluna a marcar */ 
			  Mark m, /**< a marca a ser feita */
			  double cost /**< o custo associado a ação */)
		: IIA::Action<PubState>(cost), first(first_mark), second(second_mark), mark(m) {}

	/** Retorna a referência para uma cópia desta instância. */
	PubAction *clone() const {
		return new PubAction(first, second, mark, cost);
	}

	/** Executa a ação, libera a memória da última ação, se houver, armazena uma
	 * cópia desta ação como última executada no estado.
	 *
	 * @param game estado em que a ação será executada. */
	void execute(PubState &game) const {
		mark_column(game, first, mark);
		mark_column(game, second, mark);
		if(game.last_action) delete game.last_action;
		game.last_action = clone();
	}
	
	/** Retorna uma string que descreve a ação. */
	std::string to_string() const {
		return "Marcar " + IIA::Utils::String::to_string(mark) + " (" + IIA::Utils::String::to_string(first) + ", " + IIA::Utils::String::to_string(second) + ")";
	}

	/** Converte a ação em string. */
	friend std::ostream &operator <<(std::ostream &os, const PubAction &action) {
		os << action.to_string();
		return os;
	}

	// Attributes
	/** A primeira coluna a marcar. */
	const unsigned int first;
	/** A segunda coluna a marcar. */
	const unsigned int second;
	/** A marca a fazer. */
	Mark mark;
private: 
	// Funções auxiliares
	int get_empty_row(const PubState &game, const int col) const {
		Games::Grids::Coord2D coord(0, col);
		while(game.valid(coord) && game[coord] != EMPTY) ++coord.row;
		return coord.row;
	}

	void mark_column(PubState &game, const int column, Mark mark) const {
		Games::Grids::Coord2D coord(get_empty_row(game, column), column);
		if(!game.valid(coord))
			throw std::invalid_argument("Invalid column to mark.");

		game[coord] = mark;
	}
};
} // namespace Pub
} // namespace Games

#endif // GAMES_PUB_ACTION_H
