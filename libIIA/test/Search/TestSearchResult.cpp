/** @file TestSearchResult.cpp
 * 
 * Implementa testes para a classe IIA::Search::Result.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>
#include <iostream>

#include "../TestProblem.h"
#include "SearchResult.hpp"

using namespace IIA::Search;
typedef IIA::Test::Action::Add Add;
typedef IIA::Test::State::Integer Integer;

void test_ctor(){
	Result<Integer> result;
	assert(result.status == Result<Integer>::FAILURE);
	assert(result.actions.empty());
	assert(result.expanded_nodes == 0);
			
	result = Result<Integer>(Result<Integer>::CUTOFF, nullptr, 15);
	assert(result.status == Result<Integer>::CUTOFF);
	assert(result.actions.empty());
	assert(result.expanded_nodes == 15);
	
	using namespace Uninformed;
	
	Integer number(0);
	Node<Integer> node(number);
	Add add(1);
	Node<Integer> *child = child_node<Integer>(&node, &add);
	Node<Integer> *grandchild = child_node(child, &add);
	result = Result<Integer>(Result<Integer>::SUCCESS, grandchild, 3);
	
	assert(result.status == Result<Integer>::SUCCESS);
	assert(!result.actions.empty());
	assert(result.actions.size() == 2);
	// Integer state = node.state;
	// for(IIA::Action<Integer> *action : result.actions)
	//	action->execute(state);
	// // for(IIA::Action<Integer> *action : result.actions){
	// //	if(action) std::cout << "\n Action " << action->to_string() << "(" << state << ")\n";
	// //	else continue;
	// //	action->execute(state);
	// // }
	// assert(state == grandchild->state);
	
	std::stringstream sstr;
	sstr << result;
	assert(sstr.str() == IIA::Utils::String::to_string(result));

	delete grandchild;
	delete child;
	/** @todo implementar testes de variações no construtor. */
}

void test_operator_equal() {
	/** @todo implementar teste de operador = */
}

	
/** @todo testar contador de nós. */
void test_use() {
	Integer number(0);
	Uninformed::Node<Integer> node(number);
	Add add(1);
	
	using namespace Uninformed;
	Node<Integer> *child = child_node<Integer>(&node, &add);
	Node<Integer> *grandchild = child_node(child, &add);

	Result<Integer> result(Result<Integer>::CUTOFF);
	assert(result.status == Result<Integer>::CUTOFF);
	assert(result.actions.empty());

	result = Result<Integer>(Result<Integer>::SUCCESS, grandchild);
	assert(result.status == Result<Integer>::SUCCESS);
	assert(!result.actions.empty());

	Integer state = node.state;
	for(IIA::Action<Integer> *action : result.actions) action->execute(state);
	assert(state == grandchild->state);

	std::stringstream sstr;
	sstr << result;
	assert(sstr.str() == IIA::Utils::String::to_string(result));

	delete grandchild;
	delete child;
}

int main(int argc, char **argv) {
	test_ctor();
	test_operator_equal();
	test_use();
	
	return 0;
}
