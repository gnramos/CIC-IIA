#include <iostream>

#include "examples.hpp"
#include "VacuumWorldProblem.h"
#include "VacuumWorldReflexAgent.h"
#include "VacuumWorldSimpleProblemSolvingAgent.h"
#include "VacuumWorldTableDrivenAgent.h"

int main(int argc, char **argv) {
	using namespace IIA::Examples::VacuumWorld;
	ReflexVacuumAgent rva;

	VacuumWorldState initial(VacuumWorldState::A, std::deque<bool>(2, true));
	std::deque<VacuumWorldState> goals;
	goals.push_back(VacuumWorldState(VacuumWorldState::A, std::deque<bool>(2, false)));
	goals.push_back(VacuumWorldState(VacuumWorldState::B, std::deque<bool>(2, false)));

	IIA::Examples::time_agent("ReflexVacuumAgent", rva, initial, goals);

	std::map<VacuumWorldState, const IIA::Action<VacuumWorldState> *> lookup_table;
	std::deque<bool> dirty(2, true);

	lookup_table[VacuumWorldState(VacuumWorldState::A, dirty)] = new Suck();
	lookup_table[VacuumWorldState(VacuumWorldState::B, dirty)] = new Suck();
	dirty[VacuumWorldState::A] = false;
	lookup_table[VacuumWorldState(VacuumWorldState::A, dirty)] = new Move(VacuumWorldState::B);
	lookup_table[VacuumWorldState(VacuumWorldState::B, dirty)] = new Suck();
	dirty[VacuumWorldState::A] = true;
	dirty[VacuumWorldState::B] = false;
	lookup_table[VacuumWorldState(VacuumWorldState::A, dirty)] = new Suck();
	lookup_table[VacuumWorldState(VacuumWorldState::B, dirty)] = new Move(VacuumWorldState::A);

	VacuumWorldTableDrivenAgent tdva(lookup_table);
	initial = VacuumWorldState(VacuumWorldState::A, std::deque<bool>(2, true));
	IIA::Examples::time_agent("TableDrivenVacuumAgent", tdva, initial, goals);

	VacuumWorldProblem problem(initial, goals);

	VacuumWorldSimpleProblemSolvingAgent spsa(problem, IIA::Search::Uninformed::IterativeDeepening::search);
	IIA::Examples::time_agent("VacuumWorldSimpleProblemSolvingAgent", spsa, initial, goals);

	//HeuristicCalc h_calc(&(problem.goal_states));

	IIA::Examples::show_problem_info(problem, "Vacuum World Problem");
	IIA::Examples::run_uniformed_searches(problem);
	//IIA::Examples::run_informed_searches(problem, h_calc);

	IIA::Utils::empty(lookup_table);

	return 0;
}

