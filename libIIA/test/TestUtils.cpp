/** @file TestUtils.cpp
 * 
 * Implementa testes para o escopo IIA::Utils.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */
 
#ifndef IIA_TEST_UTILS_H
#define IIA_TEST_UTILS_H

#include <assert.h>
#include <deque>

#include "Utils.h"

using namespace IIA::Utils;

void test_empty() {
	/** @todo Implementar teste de IIA::Utils::empty() */
}

void test_contains() {
	std::deque<int> deque;
	assert(!contains(deque, 0));
	deque.push_back(0);
	assert(contains(deque, 0));

	assert(!contains(deque, 1));
	deque.push_back(1);
	assert(contains(deque, 0));
	assert(contains(deque, 1));
}

void test_Random() {
	using namespace Random;
	
	set_seed_from_system_time();

	constexpr int i_u_bound = 100, i_l_bound = -1;
	constexpr double d_u_bound = 0.85, d_l_bound = 0.05;
	//int last_i = i_u_bound + 1;
	int last_d = d_u_bound + 1;
	for(int j = 0; j < 1000; ++j) {
		int i = get_random_int(i_u_bound, i_l_bound);
		assert(i_l_bound <= i && i <= i_u_bound);
		//assert(i != last_i), last_i = i;

		double d = get_random_dbl(d_u_bound, d_l_bound);
		assert(d_l_bound <= d && d <= d_u_bound);
		assert(d != last_d), last_d = d;
	}
}

void test_String() {
	using namespace String;

	int i = 1;
	assert(to_string(i) == "1");
	i = -1, assert(to_string(i) == "-1");
	double d = 1.5;
	assert(to_string(d) == "1.5");
	d = -3.1415, assert(to_string(d) == "-3.1415");

	std::deque<char> deque;
	deque.push_back('a'), deque.push_back('b'), deque.push_back('c');
	assert(join(deque) == "a, b, c");
	assert(join(deque, "") == "abc");
	assert(join(deque, "&") == "a&b&c");

	std::deque<char *> ptr_d;
	ptr_d.push_back(new char('a')), ptr_d.push_back(new char('b')), ptr_d.push_back(new char('c'));
	assert(join_ptrs(ptr_d) == "a, b, c");
	assert(join_ptrs(ptr_d, "") == "abc");
	assert(join_ptrs(ptr_d, "&") == "a&b&c");
	IIA::Utils::empty(ptr_d);
}

void test_Time() {
	using namespace Time;

	timespec start_time, end_time;
	get_cpu_time(start_time);
	for(int i = 0; i < 10000; ++i);
	get_cpu_time(end_time);
	assert(end_time.tv_sec > start_time.tv_sec ||
		   end_time.tv_nsec > start_time.tv_nsec);

	constexpr double THOUSAND = 1000;
	constexpr double MILLION = THOUSAND*THOUSAND;
	constexpr double BILLION = THOUSAND*MILLION;

	start_time.tv_sec = 0, start_time.tv_nsec = MILLION;
	end_time.tv_sec = 1, end_time.tv_nsec = 0;
	timespec diff = time_diff(start_time, end_time);
	assert(diff.tv_sec == 0 && diff.tv_nsec == BILLION - MILLION);

	diff.tv_sec = 60, diff.tv_nsec = 0;
	assert(to_nano(diff) == 60*BILLION);
	assert(to_micro(diff) == 60*MILLION);
	assert(to_mili(diff) == 60*THOUSAND);
	assert(to_sec(diff) == 60);
	assert(to_min(diff) == 1);
}

int main(int argc, char **argv)	{
	test_empty();
	test_contains();
	
	test_Random();
	test_String();
	test_Time();
	
	return 0;
}

#endif // IIA_TEST_UTILS_H
