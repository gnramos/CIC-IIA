/** @file NPuzzleProblem.h
 *
 * Descreve o problema do N-Puzzzle.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

#ifndef IIA_EXAMPLES_NPUZZLE_PROBLEM_H
#define IIA_EXAMPLES_NPUZZLE_PROBLEM_H

#include "Problem.hpp"
#include "NPuzzleAction.h"

namespace IIA {
namespace Examples {
namespace NPuzzle {
/** Define o problema. Dado um tabuleiro, como movimentar as peças para que 
 * fiquem ordenadas? */
class NPuzzleProblem : public IIA::Problem<NPuzzleState> {
public:
	/** Construtor. */
	NPuzzleProblem(const NPuzzleState &state, const NPuzzleState &goal)
		: IIA::Problem<NPuzzleState>(state, goal) {}

	/** Define as ações possíveis conforme o estado. */
	std::deque<Action<NPuzzleState> *> actions(const NPuzzleState &state) const {
		std::deque<IIA::Action<NPuzzleState> *> actions;

		Coord coord = state.find(0);
		if(coord.col > 0)
			actions.push_back(new Left());
		if(coord.col < state.size() - 1)
			actions.push_back(new Right());
		if(coord.row > 0)
			actions.push_back(new Up());
		if(coord.row < state.size() - 1)
			actions.push_back(new Down());

		return actions;
	}
	
	/** Define os possíveis pares estado/ação de modo que a ação aplicada ao 
	 * estado associado resultaria no estado dado como parâmetro. */
	std::deque<std::pair<NPuzzleState, Action<NPuzzleState> *> > predecessors(const NPuzzleState &state) const {
		std::deque<std::pair<NPuzzleState, Action<NPuzzleState> *> >pairs;

		Coord coord = state.find(0);
		if(coord.col > 0) {
			Left left;
			NPuzzleState new_state = state;
			left.execute(new_state);
			pairs.push_back(std::pair<NPuzzleState, Action<NPuzzleState> *> (new_state, new Right()));
		}
		if(coord.col < state.size() - 1){
			Right right;
			NPuzzleState new_state = state;
			right.execute(new_state);
			pairs.push_back(std::pair<NPuzzleState, Action<NPuzzleState> *> (new_state, new Left()));
		}
		if(coord.row > 0){
			Up up;
			NPuzzleState new_state = state;
			up.execute(new_state);
			pairs.push_back(std::pair<NPuzzleState, Action<NPuzzleState> *> (new_state, new Down()));
		}
		if(coord.row < state.size() - 1){
			Down down;
			NPuzzleState new_state = state;
			down.execute(new_state);
			pairs.push_back(std::pair<NPuzzleState, Action<NPuzzleState> *> (new_state, new Up()));
		}

		return pairs;
	}
};
} // namespace NPuzzle
} // namespace Examples
} // namespace IIA

#endif // IIA_EXAMPLES_NPUZZLE_PROBLEM_H
