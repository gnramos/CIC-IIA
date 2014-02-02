/** @file TestDepthLimitedSearch.cpp
 * 
 * Implementa testes para a classe IIA::Search::Uniformed::DepthLimited
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>

#include "DepthLimitedSearch.h"
#include "../../TestProblem.h"

typedef IIA::Test::State::Integer Integer;
typedef IIA::Test::Problem::ZeroToFour ZeroToFour;

int main(int argc, char **argv)	{
	using namespace IIA::Search;
	
	ZeroToFour problem;
	Result<Integer> result = Uninformed::DepthLimited::search(problem);
		
	assert(result.status == Result<Integer>::SUCCESS);
	assert(!result.actions.empty());
	assert(result.expanded_nodes > 0);

	Integer state = problem.initial_state;
	for(IIA::Action<Integer> *action : result.actions) 
		action->execute(state);
	assert(problem.is_goal(state));
	
	return 0;
}
