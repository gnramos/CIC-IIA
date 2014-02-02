/** @file TestBreadthFirstSearch.cpp
 * 
 * Implementa testes para a classe IIA::Search::Uniformed::BreadthFirst
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>

#include "../../TestProblem.h"
#include "BreadthFirstSearch.h"

using namespace IIA::Search;
typedef IIA::Test::State::Integer Integer;
typedef IIA::Test::Problem::ZeroToFour ZeroToFour;

void test_search(const ZeroToFour &problem, IIA::Search::Result<Integer> (*search)(const IIA::Problem<Integer> &)) {
	Result<Integer> result = search(problem);
		
	assert(result.status == Result<Integer>::SUCCESS);
	assert(!result.actions.empty());
	assert(result.expanded_nodes > 0);

	Integer state = problem.initial_state;
	for(IIA::Action<Integer> *action : result.actions)
		if(action) action->execute(state);
	assert(problem.is_goal(state));
}

int main(int argc, char **argv) {
	using namespace Uninformed::BreadthFirst;
	
	ZeroToFour problem;
	
	test_search(problem, search_tree);
	test_search(problem, search_graph);

	return 0;
}
