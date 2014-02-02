#include <iostream>
#include <map>

#include "HeuristicSearchNode.hpp"
#include "examples.hpp"
#include "RomaniaProblem.h"

namespace IIA {
namespace Examples {
namespace Romania {
class SLDtoBucharest : public IIA::Search::Informed::HeuristicCalc<RomaniaState> {
public:
	SLDtoBucharest(std::set<RomaniaState> *goal_states)
		: IIA::Search::Informed::HeuristicCalc<RomaniaState>(goal_states) {
		straight_line_distance["Arad"] = 366;
		straight_line_distance["Bucharest"] = 0;
		straight_line_distance["Craiova"] = 160;
		straight_line_distance["Drobeta"] = 242;
		straight_line_distance["Eforie"] = 161;
		straight_line_distance["Fagaras"] = 176;
		straight_line_distance["Giurgiu"] = 77;
		straight_line_distance["Hirsova"] = 151;
		straight_line_distance["Iasi"] = 226;
		straight_line_distance["Lugoj"] = 244;
		straight_line_distance["Mehadia"] = 241;
		straight_line_distance["Neamt"] = 234;
		straight_line_distance["Oradea"] = 380;
		straight_line_distance["Pitesti"] = 100;
		straight_line_distance["Rimnicu Vilcea"] = 193;
		straight_line_distance["Sibiu"] = 253;
		straight_line_distance["Timisoara"] = 329;
		straight_line_distance["Urziceni"] = 80;
		straight_line_distance["Vaslui"] = 199;
		straight_line_distance["Zerind"] = 374;
	}

	double eval(const RomaniaState &state) const {
		std::map<const std::string, double>::const_iterator it = straight_line_distance.find(state.key);
		if(it == straight_line_distance.end())
			throw std::invalid_argument("Unknown city \"" + state.key + "\".");
		return it->second;
	}
private:
	std::map<const std::string, double> straight_line_distance;
};
} // namespace Romania
} // namespace Examples
} // namespace IIA

int main(int argc, char **argv) {
	using namespace IIA::Examples::Romania;

	RomaniaProblem rp("Arad", "Bucharest");
	SLDtoBucharest h_calc(&(rp.goal_states));

	IIA::Examples::show_problem_info(rp, "Romania Problem");
	IIA::Examples::run_uniformed_searches(rp);
	IIA::Examples::run_informed_searches(rp, h_calc);

	return 0;
}

