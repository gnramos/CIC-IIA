/** @file TestNode.cpp
 * 
 * Implementa testes para a classe Node.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */
 
#include <assert.h>
#include <deque>

#include "../../TestAction.h"
#include "UninformedSearchNode.hpp"

using namespace IIA::Search::Uninformed;
typedef IIA::Test::Action::Add Add;
typedef IIA::Test::State::Integer Integer;

void test_ctor() {
	Integer number(0);
	Node<Integer> node(number);
	
	assert(node.state == number);
	assert(node.parent == nullptr);
	assert(node.action == nullptr);
	assert(node.path_cost == 0);

  	/** @todo testar as variações do construtor. */
//	node = Node<Integer>();
//	const state_t &s, 
//		 Node *p = nullptr, 
//		 const Action<state_t> *a = nullptr,
//		 const double cost = 0) :
}

void test_operator_equal() {
	Integer x(0), y(1);
	Add add(1);
	Node<Integer> n1(x), n2(y, &n1, &add, -1);

	n2 = n1;
	assert(n2.state == n1.state);
	assert(n2.parent == n1.parent);
	assert(n2.action == n1.action);
	assert(n2.path_cost == n1.path_cost);

	Node<Integer> n3 = Node<Integer>(y, &n1, &add, -1);

	n2 = n3;
	assert(n2.state == n3.state);
	assert(n2.parent == n3.parent);
	assert(n2.action->to_string() == n3.action->to_string());
	assert(n2.path_cost == n3.path_cost);
}

void test_child_node() {
	Integer number(0);
	Node<Integer> node(number);
	Add add(1);
	Node<Integer> *child = child_node(&node, &add);
	
	assert(child);
	assert(child->state.number == 1);
	assert(child->parent == &node);
	assert(child->action);
	assert(child->path_cost == add.cost);	
	assert(IIA::Utils::String::to_string(*child) == "state: 1 parent: " + IIA::Utils::String::to_string(child->parent) + " action: " + add.to_string() + " path_cost: 0.5");
	
	delete child;
}

void test_children_nodes() {
	Integer number(1);
	Node<Integer> node(number);	
	Add add(1);
	Add sub(-1);
	std::deque<IIA::Action<Integer> *> actions;
	std::deque<Node<Integer> *> children;

	actions.push_back(&add), actions.push_back(&sub);

	children = children_nodes(&node, actions);
	assert(children.size() == actions.size());
	for(Node<Integer> *ptr_node : children) {
		assert(ptr_node->parent == &node);
		assert(ptr_node->state.number == 2 || ptr_node->state.number == 0);
		assert(ptr_node->path_cost == node.path_cost + add.cost || ptr_node->path_cost == node.path_cost + sub.cost);
	}
	
	IIA::Utils::empty(children);
}

void test_in_parent_node() {
	Integer number(1);
	Node<Integer> node(number);		
	assert(!in_parent_node(node.parent, node.state));
	
	Add add(1);
	
	Node<Integer> *n1 = child_node(&node, &add);
	assert(n1);
	assert(!in_parent_node(n1->parent, n1->state));
	assert(in_parent_node(n1->parent, node.state));		
	
	Node<Integer> *n2 = child_node(n1, &add);
	assert(n2);
	assert(!in_parent_node(n2->parent, n2->state));
	assert(in_parent_node(n2->parent, n1->state));
	assert(in_parent_node(n2->parent, node.state));
	
	delete n1, delete n2;
}

void test_to_string() {
	Integer number(0);
	Node<Integer> node(number);
	std::stringstream sstr;
	
	sstr << node;
	assert(sstr.str() == "state: 0 parent: 0 action: 0 path_cost: 0");
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
