/** @file TestSimpleProblemSolvingAgent.h
 * 
 * Implementa testes para o agente simples.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */
 
#ifndef IIA_TEST_AGENTS_SIMPLE_PROBLEM_SOLVING_H
#define IIA_TEST_AGENTS_SIMPLE_PROBLEM_SOLVING_H

#include "TableDrivenAgent.hpp"
#include "UninformedSearch.h"
#include "../TestProblem.h"

typedef IIA::Test::State::Integer Integer;
typedef IIA::Test::Action::Add Add;

namespace IIA {
namespace Test {
namespace Agents {
/** Classe para testar o agente. */
class SimpleProblemSolvingAgent : public IIA::Agents::TableDrivenAgent<Integer, Integer> {
public:
	SimpleProblemSolvingAgent(const IIA::Problem<Integer> &problem)
		: TableDrivenAgent<Integer, Integer>(std::map<Integer, const IIA::Action<Integer> *>()) {
		using namespace IIA::Search;
		
		Result<Integer> result = Uninformed::IterativeDeepening::search(problem);
		if(result.status != Result<Integer>::SUCCESS) throw std::runtime_error("Unable to find solution.");

		Integer state = problem.initial_state;
		for(IIA::Action<Integer> *action: result.actions) {
			lookup_table[state] = action->clone();
			action->execute(state);
		}
	}

	Integer percept() const	{return Integer(0);}

	Integer interpret_input(const Integer &percept) const {return percept;}
};
} // namespace Agents
} // namespace Test
} // namespace IIA

#endif /* IIA_TEST_AGENTS_SIMPLE_PROBLEM_SOLVING_H */
