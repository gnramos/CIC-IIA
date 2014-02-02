/** @file TestBestFirstSearch.cpp
 *
 * Implementa testes para a classe IIA::Search::Informed::BestFirst
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>

#include "../../TestProblem.h"
#include "BestFirstSearch.h"

typedef IIA::Test::State::Integer Integer;
typedef IIA::Test::Problem::ZeroToFour ZeroToFour;

namespace IIA {
namespace Search {
namespace Informed {
/** Especialização de heuristic. */
class OutraIntegerHeuristic :  public HeuristicCalc<Integer> {
public:
	OutraIntegerHeuristic(const std::set<Integer> *goal_states) : HeuristicCalc<Integer>(goal_states) {}
	
	double eval(const Integer &state) const {
		// heurística admissível
		int minimum = std::numeric_limits<int>::max();
		for(const Integer &number : *goals)
			minimum = std::min(minimum, abs(std::max(number.number, state.number) - std::min(number.number, state.number)));
		return minimum;
	}
};
} // namespace Informed
} // namespace Search
} // namespace IIA

int main(int argc, char **argv)	{
	using namespace IIA::Search;

	ZeroToFour problem;
	Informed::OutraIntegerHeuristic h_calc(&problem.goal_states);
	Result<Integer> result = Informed::BestFirst::search(problem, h_calc);

	assert(result.status == Result<Integer>::SUCCESS);
	assert(!result.actions.empty());
	assert(result.expanded_nodes > 0);

	Integer state = problem.initial_state;
	for(IIA::Action<Integer> *action : result.actions)
		action->execute(state);
	assert(problem.is_goal(state));

	return 0;
}
