/** @file TestTableDrivenAgent.h
 * 
 * Implementa testes para o agente com tabela de mapeamento estado-ação.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#ifndef IIA_TEST_AGENTS_TABLE_DRIVEN_HPP
#define IIA_TEST_AGENTS_TABLE_DRIVEN_HPP

#include "../TestProblem.h"

#include "TableDrivenAgent.hpp"

typedef IIA::Test::State::Integer Integer;
typedef IIA::Test::Action::Add Add;

namespace IIA {
namespace Agents {
namespace Test {
/** Classe para testar o agente. */
class TableDrivenTestAgent : public IIA::Agents::TableDrivenAgent<Integer, Integer> {
public:
	TableDrivenTestAgent(const std::map<Integer, const IIA::Action<Integer> *> &table) : IIA::Agents::TableDrivenAgent<Integer, Integer>(table) {}

	Integer percept() const	{return Integer(0);}

	Integer interpret_input(const Integer &percept) const {return percept;}
};
} // namespace Test
} // namespace Agents
} // namespace IIA

#endif /* IIA_TEST_AGENTS_TABLE_DRIVEN_HPP */
