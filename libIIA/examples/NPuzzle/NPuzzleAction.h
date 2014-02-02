/** @file NPuzzleAction.h
 *
 * Descreve as ações para o N-Puzzzle.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

#ifndef IIA_EXAMPLES_NPUZZLE_ACTION_H
#define IIA_EXAMPLES_NPUZZLE_ACTION_H

#include "Action.hpp"
#include "NPuzzleState.h"

namespace IIA {
namespace Examples {
namespace NPuzzle {
/** Define a ação de mover o espaço. */
class Move : public IIA::Action<NPuzzleState>, public Coord {
public:
	/** Instancia a ação.
	 *
	 * @param row a linha da coordenada para onde mover.
	 * @param col a coluna da coordenada para onde mover.
	 * @param cost o custo da ação. */
	Move(int row, int col, const double cost = 1) : IIA::Action<NPuzzleState>(cost), Coord(row, col) {}
	
	/** Construtor. */
	Move(const Move &move) : IIA::Action<NPuzzleState>(move.cost), Coord(move.row, move.col) {}

	/** Executa a ação no estado dado. */
	void execute(NPuzzleState &state) const {
		Coord old_coord = state.find(0);
		Coord new_coord(old_coord.row + this->row, old_coord.col + this->col);
		if(!state.is_valid(new_coord))
			throw std::invalid_argument("Cannot execute N-Puzzle action.");
		std::swap(state[old_coord], state[new_coord]);
	}
};

/** Define a ação de mover o espaço para cima. */
class Up : public Move {
public:
	/** Instancia a ação.
	 *
	 * @param cost o custo da ação. */
	Up(const double cost = 1) : Move(-1, 0, cost) {}
	
	/** Construtor. */
	Up(const Up &up) : Move(up) {}
	
	/** Retorna a referência para uma cópia da instância. */
	Up *clone() const { return new Up(*this); }

	/** Converte a instância em string. */
	std::string to_string() const { return "up"; };
};

/** Define a ação de mover o espaço para baixo. */
class Down : public Move {
public:
	/** Instancia a ação.
	 *
	 * @param cost o custo da ação. */
	Down(const double cost = 1) : Move(1, 0, cost) {}
	
	/** Construtor. */
	Down(const Down &down) : Move(down) {}
	
	/** Retorna a referência para uma cópia da instância. */
	Down *clone() const { return new Down(*this); }

	/** Converte a instância em string. */
	std::string to_string() const { return "down"; };
};

/** Define a ação de mover o espaço para direita. */
class Right : public Move {
public:
	/** Instancia a ação.
	 *
	 * @param cost o custo da ação. */
	Right(const double cost = 1) : Move(0, 1, cost) {}
	
	/** Construtor. */
	Right(const Right &right) : Move(right) {}
	
	/** Retorna a referência para uma cópia da instância. */
	Right *clone() const { return new Right(*this); }

	/** Converte a instância em string. */
	std::string to_string() const { return "right"; };
};

/** Define a ação de mover o espaço para esquerda. */
class Left : public Move {
public:
	/** Instancia a ação.
	 *
	 * @param cost o custo da ação. */
	Left(const double cost = 1) : Move(0, -1, cost) {}
	
	/** Construtor. */
	Left(const Left &left) : Move(left) {}
	
	/** Retorna a referência para uma cópia da instância. */
	Left *clone() const { return new Left(*this); }

	/** Converte a instância em string. */
	std::string to_string() const { return "left"; };
};
} // namespace NPuzzle
} // namespace Examples
} // namespace IIA

#endif // IIA_EXAMPLES_NPUZZLE_ACTION_H
