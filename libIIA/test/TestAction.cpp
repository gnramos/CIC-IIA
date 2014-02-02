/** @file TestAction.cpp
 * 
 * Implementa testes para a classe IIA::Action.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>

#include "TestAction.h"

using namespace IIA::Test::Action;
typedef IIA::Test::State::Integer Integer;

void test_add_ctor() {
	Add add1(1);
	assert(add1.number == 1 && add1.cost == 0.5);
	
	Add add2(-1, -1.5);
	assert(add2.number == -1 && add2.cost == -1.5);
}

void test_add_clone() {
	Add add(1);
	Add *ptr_add = add.clone();
	
	Integer n1(2), n2(2);
	assert(n1 == n2);
	add.execute(n1), ptr_add->execute(n2);
	assert(n1 == n2);
	
	delete ptr_add;
}

void test_add_execute() {
	Add add(-1);
	Integer number(2);
	add.execute(number), assert(number.number == 1);
	add.execute(number), assert(number.number == 0);
}
	
void test_add_to_string(){
	Add add(1);
	std::string str = add.to_string();
	assert(str == "+1");;
}


void test_multiply_ctor() {
	Multiply multiply1(1);
	assert(multiply1.number == 1 && multiply1.cost == 0.75);
	
	Multiply multiply2(-1, -1.5);
	assert(multiply2.number == -1 && multiply2.cost == -1.5);
}

void test_multiply_clone() {
	Multiply multiply(2);
	Multiply *ptr_multiply = multiply.clone();
	
	Integer n1(2), n2(2);
	assert(n1 == n2);
	multiply.execute(n1), ptr_multiply->execute(n2);
	assert(n1 == n2);
	
	delete ptr_multiply;
}

void test_multiply_execute() {
	Multiply multiply(2);
	Integer number(1);
	multiply.execute(number), assert(number.number == 2);
	multiply.execute(number), assert(number.number == 4);
}
	
void test_multiply_to_string(){
	Multiply multiply(-1);
	std::string str = multiply.to_string();
	assert(str == "*(-1)");
}

void test_donothing_ctor() {
	IIA::DoNothing<Integer> do_nothing;
	assert(do_nothing.cost == 0);
}

void test_donothing_clone() {
	IIA::DoNothing<Integer> do_nothing;
	IIA::DoNothing<Integer> *ptr_do_nothing = do_nothing.clone();
	
	Integer n1(2), n2(2);
	assert(n1 == n2);
	do_nothing.execute(n1), ptr_do_nothing->execute(n2);
	assert(n1 == n2);
	
	delete ptr_do_nothing;
}

void test_donothing_execute() {
	IIA::DoNothing<Integer> do_nothing;
	Integer number(1);
	do_nothing.execute(number), assert(number.number == 1);
	do_nothing.execute(number), assert(number.number == 1);
}

int main(int argc, char **argv)	{
	test_add_ctor();
	test_add_clone();
	test_add_execute();
	test_add_to_string();
	
	test_multiply_ctor();
	test_multiply_clone();
	test_multiply_execute();
	test_multiply_to_string();
	
	test_donothing_ctor();
	test_donothing_clone();
	test_donothing_execute();
	
	return 0;
}

