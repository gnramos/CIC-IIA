/** @file TestProblem.cpp
 * 
 * Implementa testes para a classe IIA::Search::Problem.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>

#include "TestProblem.h"

using namespace IIA::Test;

typedef Problem::ZeroToFour ZeroToFour;

void test_ctor() {
	ZeroToFour problem;
	
	assert(problem.initial_state.number == 0);
	assert(!problem.is_goal(State::Integer(0)));
	assert(!problem.is_goal(State::Integer(-1)));
	assert(problem.goal_states.size() == 2);
	assert(problem.is_goal(State::Integer(-4)));
	assert(problem.is_goal(State::Integer(4)));
}

void test_actions() {
	ZeroToFour problem;
	State::Integer state(2);
	
	std::deque<IIA::Action<State::Integer> *> actions = problem.actions(state);
	assert(actions.size() == 3);
	for(IIA::Action<State::Integer> * action : actions) {
		assert(action);
		state.number = 2;
		action->execute(state);
		assert(state.number == 1 || state.number == 3 || state.number == 4);
	}
	IIA::Utils::empty(actions);
}

int main(int argc, char **argv)	{
	test_ctor();
	test_actions();
	
	return 0;
}

