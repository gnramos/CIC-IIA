/** @file TestPlayer.cpp
 * 
 * Implementa testes para a classe Games::Player.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */
 
#include <assert.h>

#include "PaperRockScissors.h"

namespace Games {
namespace PaperRockScissors {
namespace Test {

void test_ctor() {
	PaperPlayer pp("pp");	
	assert(IIA::Utils::String::to_string(pp) == "pp");
	
	RockPlayer rp("rp");	
	assert(IIA::Utils::String::to_string(rp) == "rp");
}

void assert_mark(PaperRockScissorsPlayer &player, const PaperRockScissorsState &state, Mark mark) {
	PaperRockScissorsAction *action = static_cast<PaperRockScissorsAction *>(player.decide_action(state));
	assert(action && action->mark == mark);
	delete action;
}

void test_decide_action() {
	PaperPlayer pp;
	RockPlayer rp;
	
	PaperRockScissorsState state;
	
	state.marks.push_back(PAPER);
	assert_mark(pp, state, PAPER), assert_mark(rp, state, ROCK);
	state.marks.back() = ROCK;
	assert_mark(pp, state, PAPER), assert_mark(rp, state, ROCK);
	state.marks.back() = SCISSOR;
	assert_mark(pp, state, PAPER), assert_mark(rp, state, ROCK);
	
	state.marks.push_back(PAPER);
	assert_mark(pp, state, PAPER), assert_mark(rp, state, ROCK);
	state.marks.back() = ROCK;
	assert_mark(pp, state, PAPER), assert_mark(rp, state, ROCK);
	state.marks.back() = SCISSOR;
	assert_mark(pp, state, PAPER), assert_mark(rp, state, ROCK);
}

} // namespace Test
} // namespace PaperRockScissors
} // namespace Games

int main(int argc, char **argv) {
	using namespace Games::PaperRockScissors::Test;
	
	test_ctor();
	test_decide_action();
	
	return 0;
}

