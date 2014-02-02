/** @file TestProblem.h
 * 
 * Define um problema para testes.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */
 
#ifndef IIA_TEST_PROBLEM_H
#define IIA_TEST_PROBLEM_H

#include "Problem.hpp"

#include "TestAction.h"

typedef IIA::Test::State::Integer Integer;

namespace IIA {
namespace Test {
namespace Problem {

/** Define o problema de se partir de um valor e chegar a outro(s). */
class ZeroToFour : public IIA::Problem<Integer> {
public:
	/** O estado inicial é 0 e os objetivos são 4 e -4 (hardcoded). */
	ZeroToFour() : IIA::Problem<Integer>(Integer(0), Integer(0)) {
		goal_states.clear();
		goal_states.insert(Integer(4));
		goal_states.insert(Integer(-4));
	}

	/** Apenas 3 ações possíveis para simplificar, +1, -1, *2. */
	std::deque<IIA::Action<Integer> *> actions(const Integer &state) const {
		std::deque<IIA::Action<Integer> *> actions;
		
		actions.push_back(new Action::Add(1));
		actions.push_back(new Action::Add(-1));
		actions.push_back(new Action::Multiply(2));
		
		return actions;
	}
	std::deque<std::pair<Integer, IIA::Action<Integer> *> > predecessors(const Integer &state) const {
		std::deque<std::pair<Integer, IIA::Action<Integer> *> > result;
		
		if((state.number%2) == 0)
			result.push_back(std::pair<Integer, IIA::Action<Integer> *>(Integer(state.number/2), new Action::Multiply(2)));
		result.push_back(std::pair<Integer, IIA::Action<Integer> *>(Integer(state.number+1), new Action::Add(-1)));
		result.push_back(std::pair<Integer, IIA::Action<Integer> *>(Integer(state.number-1), new Action::Add(1)));
	
		return result;
	}
};
} // namespace Problem
} // namespace Test
} // namespace IIA

#endif // IIA_TEST_PROBLEM_H
