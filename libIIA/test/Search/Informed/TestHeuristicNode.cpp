/** @file TestHeuristicNode.cpp
 *
 * Implementa testes para a classe HeuristicNode.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>
#include <deque>
#include <limits>

#include "HeuristicSearchNode.hpp"

#include "../../TestAction.h"
#include "../../TestProblem.h"

namespace IIA {
namespace Search {
namespace Informed {
class IntegerHeuristic :  public HeuristicCalc<Integer> {
public:
	IntegerHeuristic(std::set<Integer> *goal_states) : HeuristicCalc<Integer>(goal_states) {}
	double eval(const Integer &state) const {
		int min = std::numeric_limits<int>::max();
		for(const Integer &s : *goals)
			min = std::min(min, std::abs(s.number - state.number));
		return min;
	}
};
} // namespace Informed
} // namespace Search
} // namespace IIA

using namespace IIA::Search::Informed;
typedef IIA::Test::Action::Add Add;
typedef IIA::Test::State::Integer Integer;
typedef IIA::Test::Problem::ZeroToFour ZeroToFour;

void test_ctor() {
	Integer number(0);
	ZeroToFour problem;
	IntegerHeuristic h_calc(&(problem.goal_states));
	HeuristicNode<Integer> node(number, nullptr, nullptr, 0, h_calc.eval(number));

	assert(node.state == number);
	assert(node.parent == nullptr);
	assert(node.action == nullptr);
	assert(node.path_cost == 0);
	assert(node.h_cost == 4);
	assert(node.f_cost() == node.path_cost + node.h_cost);

	/** @todo implementar testes de variações no construtor. */
}

void test_operator_equal() {
	/** @todo implementar teste de operador = */
}

void test_child_node() {
	Integer number(0);
	ZeroToFour problem;
	IntegerHeuristic h_calc(&(problem.goal_states));
	HeuristicNode<Integer> node(number, nullptr, nullptr, 0, h_calc.eval(number));

	Add add(1);
	HeuristicNode<Integer> *child = child_node(&node, &add, h_calc);

	assert(child);
	assert(child->state.number == 1);
	assert(child->parent == &node);
	assert(child->action);
	assert(child->path_cost == add.cost);
	assert(child->h_cost == 3);
	assert(child->f_cost() == child->h_cost + add.cost);

	delete child;
}

void test_children_nodes() {
	Integer number(1);
	ZeroToFour problem;
	IntegerHeuristic h_calc(&(problem.goal_states));
	HeuristicNode<Integer> node(number, nullptr, nullptr, 0, h_calc.eval(number));

	Add add(1);
	Add sub(-1);
	std::deque<IIA::Action<Integer> *> actions;

	actions.push_back(&add), actions.push_back(&sub);

	std::deque<HeuristicNode<Integer> *> children = children_nodes(&node, actions, h_calc);
	assert(children.size() == actions.size());
for(HeuristicNode<Integer> *ptr_node : children) {
		assert(ptr_node->parent == &node);
		assert(ptr_node->state.number == 2 || ptr_node->state.number == 0);
		assert(ptr_node->path_cost == node.path_cost + add.cost || ptr_node->path_cost == node.path_cost + sub.cost);
	}

	IIA::Utils::empty(children);
}

void test_in_parent_node() {
	Integer number(1);
	ZeroToFour problem;
	IntegerHeuristic h_calc(&(problem.goal_states));
	HeuristicNode<Integer> node(number, nullptr, nullptr, 0, h_calc.eval(number));

	Add add(1);

	HeuristicNode<Integer> *n1 = child_node(&node, &add, h_calc);
	assert(n1);
	assert(!in_parent_node(n1->parent, n1->state));
	assert(in_parent_node(n1->parent, node.state));

	HeuristicNode<Integer> *n2 = child_node(n1, &add, h_calc);
	assert(n2);
	assert(!in_parent_node(n2->parent, n2->state));
	assert(in_parent_node(n2->parent, n1->state));
	assert(in_parent_node(n2->parent, node.state));

	delete n1, delete n2;
}

void test_to_string() {
	Integer number(0);
	ZeroToFour problem;
	IntegerHeuristic h_calc(&(problem.goal_states));
	HeuristicNode<Integer> node(number, nullptr, nullptr, 0, h_calc.eval(number));
	std::stringstream sstr;

	sstr << node;
	assert(sstr.str() == "state: 0 parent: 0 action: 0 path_cost: 0 h_cost: 4");
}

int main(int argc, char **argv) {
	test_ctor();
	test_operator_equal();
	test_child_node();
	test_children_nodes();
	test_in_parent_node();
	test_to_string();

	return 0;
}
