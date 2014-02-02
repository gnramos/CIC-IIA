/** @file TestState.cpp
 * 
 * Implementa testes para a classe IIA::State.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>

#include "TestState.h"

using namespace IIA::Test::State;

// Testa o construtor.
void test_ctor() {	
	Integer state1(1);
	assert(state1.number == 1);
	Integer state2(-1);
	assert(state2.number == -1);
}

// Testa o operador <.
void test_operator_lt() {
	Integer state1(1);
	Integer state2(2);
	assert(state1 < state2);
	assert(!(state2 < state1));
}

// Testa o operador ==.
void test_operator_eq() {
	Integer state1(1);
	Integer state2(1);
	assert(state1 == state2);
	
	state2.number = 2;
	assert(state2 != state1);
}

// Testa o operador =.
void test_operator_attr() {
	Integer state1(1);
	Integer state2(2);
	assert(state1 != state2);
	state1 = state2;
	
	assert(state1.number == state2.number);
	assert(state1 == state2);
}

int main(int argc, char **argv)	{
	test_ctor();
	test_operator_lt();
	test_operator_eq();
	test_operator_attr();
	
	return 0;
}

