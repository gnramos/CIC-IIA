#include <iostream>

#include "examples.hpp"

#include "HeuristicSearchNode.hpp"
#include "MissionariesAction.h"
#include "MissionariesProblem.h"

// namespace IIA {
// namespace Examples {
// namespace Missionaries {
// class HeuristicCalc : public IIA::Search::Informed::HeuristicCalc<State> {
// public:
//	HeuristicCalc(std::set<State> *goal_states) : IIA::Search::Informed::HeuristicCalc<State>(goal_states) {}
//	double eval(const State &state) const {
//		if(Utils::contains(*goals, state)) return 0;

//		double min_h = 0;
//		for(const State goal : *goals) {
//			double h = 0;
//			for(unsigned int i = 0; i < state.Missionaries.size(); ++i)
//				h += abs(state.Missionaries[i].get_volume() - goal.Missionaries[i].get_volume());
//			min_h = std::min(min_h, h);
//		}
//		return min_h;
//	}
// };
// } // namespace Missionaries
// } // namespace Examples
// } // namespace IIA

int main(int argc, char **argv) {
	using namespace IIA::Examples::Missionaries;

	MissionariesState initial(Margin(3,3,true), Margin(0,0,false));
	MissionariesState goal(Margin(0,0,false), Margin(3,3,true));

	std::deque<MissionariesState> goals;
	goals.push_back(goal);
	goal.left.canoe = true, goal.right.canoe = false;
	goals.push_back(goal);

	MissionariesProblem missionariesProblem(initial, goals);
	//HeuristicCalc h_calc(&(missionariesProblem.goal_states));

	IIA::Examples::show_problem_info(missionariesProblem, "Missionários e Canibais");
	IIA::Examples::run_uniformed_searches(missionariesProblem);
	//IIA::Examples::run_informed_searches(missionariesProblem, h_calc);

	return 0;
}

