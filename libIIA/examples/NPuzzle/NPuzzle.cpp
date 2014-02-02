#include <iostream>

#include "examples.hpp"

#include "HeuristicSearchNode.hpp"
#include "NPuzzleProblem.h"

namespace IIA {
namespace Examples {
namespace NPuzzle {
class ManhattanDistance : public IIA::Search::Informed::HeuristicCalc<NPuzzleState> {
public:
	ManhattanDistance(const std::set<NPuzzleState> *goal_states) : IIA::Search::Informed::HeuristicCalc<NPuzzleState>(goal_states) {}
	double eval(const NPuzzleState &state) const {
		double dist = 0;
		for(unsigned int r = 0; r < state.size(); ++r) {
			for(unsigned int c = 0; c < state.size(); ++c) {
				Coord coord = state.find(r * state.size() + c);
				// Manhattan distance
				dist += abs(coord.row - r) + abs(coord.col - c);
			}
		}
		return dist;
	}
};

class WrongTiles : public IIA::Search::Informed::HeuristicCalc<NPuzzleState> {
public:
	WrongTiles(const std::set<NPuzzleState> *goal_states) : IIA::Search::Informed::HeuristicCalc<NPuzzleState>(goal_states) {}
	double eval(const NPuzzleState &state) const {

		double dist = 0;
		for(unsigned int r = 0; r < state.size(); ++r) {
			for(unsigned int c = 0; c < state.size(); ++c) {
				Coord coord = state.find(r * state.size() + c);
				dist += ((coord.row == r) && (coord.col == c) ? 0 : 1);
			}
		}
		return dist;
	}
};

class Hybrid : public IIA::Search::Informed::HeuristicCalc<NPuzzleState> {
public:
	Hybrid(const std::set<NPuzzleState> *goal_states) : IIA::Search::Informed::HeuristicCalc<NPuzzleState>(goal_states) {}
	double eval(const NPuzzleState &state) const {
		ManhattanDistance md(goals);
		WrongTiles wt(goals);

		return std::max(md.eval(state), wt.eval(state));
	}
};
} // namespace NPuzzle
} // namespace Examples
} // namespace IIA

int main(int argc, char **argv) {
	using namespace IIA::Examples::NPuzzle;

	NPuzzleState initial(3), goal(3);

	Right right;
	Down down;
	NPuzzleState nps = initial;
	right.execute(nps);
	down.execute(nps);

	NPuzzleProblem problem(nps, goal);
	Hybrid h_calc(&(problem.goal_states));

	IIA::Examples::show_problem_info(problem, "N-Puzzle Problem");
	IIA::Examples::run_uniformed_searches(problem);
	IIA::Examples::run_informed_searches(problem, h_calc);

	return 0;
}

