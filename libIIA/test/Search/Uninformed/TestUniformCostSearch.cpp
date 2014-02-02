/** @file TestUniformCostSearch.cpp
 * 
 * Implementa testes para a classe IIA::Search::Uniformed::UniformCost
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>

#include "UniformCostSearch.h"
#include "../../TestProblem.h"

using namespace IIA::Search;
typedef IIA::Test::State::Integer Integer;
typedef IIA::Test::Problem::ZeroToFour ZeroToFour;

int main(int argc, char **argv)	{
	ZeroToFour problem;
	Result<Integer> result = Uninformed::UniformCost::search(problem);
		
	assert(result.status == Result<Integer>::SUCCESS);
	assert(!result.actions.empty());
	assert(result.expanded_nodes > 0);

	Integer state = problem.initial_state;
	for(IIA::Action<Integer> *action : result.actions) 
		action->execute(state);
	assert(problem.is_goal(state));
	
	return 0;
}
