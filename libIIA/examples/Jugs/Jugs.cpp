#include <iostream>

#include "JugsAction.h"
#include "JugsProblem.h"

#include "HeuristicSearchNode.hpp"
#include "examples.hpp"

namespace IIA {
namespace Examples {
namespace Jugs {
class JugsHeuristicCalc : public IIA::Search::Informed::HeuristicCalc<JugsState> {
public:
	JugsHeuristicCalc(std::set<JugsState> *goal_states) : IIA::Search::Informed::HeuristicCalc<JugsState>(goal_states) {}
	double eval(const JugsState &state) const {
		if(Utils::contains(*goals, state)) return 0;

		double min_h = 0;
		for(const JugsState goal : *goals) {
			double h = 0;
			for(unsigned int i = 0; i < state.jugs.size(); ++i)
				h += abs(state.jugs[i].get_volume() - goal.jugs[i].get_volume());
			min_h = std::min(min_h, h);
		}
		return min_h;
	}
};
} // namespace Jugs
} // namespace Examples
} // namespace IIA

int main(int argc, char **argv) {
	using namespace IIA::Examples::Jugs;

	JugsState initial_jugstate, goal_jugstate;
	initial_jugstate.jugs.push_back(Jug(3, 0));
	initial_jugstate.jugs.push_back(Jug(4, 0));

	goal_jugstate.jugs.push_back(Jug(3, 2));
	goal_jugstate.jugs.push_back(Jug(4, 0));

	std::deque<JugsState> jug_goals;
	for(int v = 0; v <= goal_jugstate.jugs[1].get_capacity(); ++v) {
		goal_jugstate.jugs[1].empty();
		goal_jugstate.jugs[1].put(v);
		jug_goals.push_back(goal_jugstate);
	}
	goal_jugstate.jugs[1] = Jug(4, 2);
	goal_jugstate.jugs[0].empty();

	for(int v = 0; v <= goal_jugstate.jugs[0].get_capacity(); ++v) {
		goal_jugstate.jugs[0].empty();
		goal_jugstate.jugs[0].put(v);
		jug_goals.push_back(goal_jugstate);
	}

	JugsProblem jugProblem(initial_jugstate, jug_goals);
	JugsHeuristicCalc h_calc(&(jugProblem.goal_states));

	IIA::Examples::show_problem_info(jugProblem, "Jug Problem");
	IIA::Examples::run_uniformed_searches(jugProblem);
	IIA::Examples::run_informed_searches(jugProblem, h_calc);

	return 0;
}

