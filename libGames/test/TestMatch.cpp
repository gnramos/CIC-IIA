/** @file TestMatch.cpp
 * 
 * Implementa testes para a classe Games::Game.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */
 
#include <assert.h>

// #include "Match.hpp"	
#include "PaperRockScissors.h"

namespace Games {
namespace PaperRockScissors {
namespace Test {

void test_Mark() {
	Mark mark = PAPER;
	assert(mark != ROCK && mark != SCISSOR && mark != INVALID);
	mark = SCISSOR;
	assert(mark != ROCK && mark != PAPER && mark != INVALID);
	mark = ROCK;
	assert(mark != SCISSOR && mark != PAPER && mark != INVALID);
}

void test_State() {
	PaperRockScissorsState state;
	assert(state.marks.empty());
}

void test_Action() {
	PaperRockScissorsAction action(PAPER, 1);
	assert(action.mark == PAPER && action.cost == 1);
	
	PaperRockScissorsAction *ptr_action = action.clone();
	assert(ptr_action->mark == action.mark && ptr_action->cost == action.cost);

	PaperRockScissorsState state;
	PaperRockScissorsState *result_state = action.result(state);
	assert(result_state);
	assert(result_state->marks.size() == 1 && result_state->marks.back() == action.mark);
	
	ptr_action->execute(*result_state);
	assert(result_state->marks.size() == 2 && result_state->marks.back() == ptr_action->mark);

	delete ptr_action, delete result_state;
}

void test_RandomPlayer() {
	RandomPlayer rp("TestRandomPlayer");
	//assert(rp.id == "TestRandomPlayer");

	try {
		rp.percept();
		assert(false);
	} catch(std::invalid_argument e) {}
	
	PaperRockScissorsState state;
	IIA::Action<PaperRockScissorsState> *action = rp.decide_action(state);
	assert(action && action->cost > 0);
	
	PaperRockScissorsAction *prs_action = static_cast<PaperRockScissorsAction *>(action);
	assert(prs_action->mark == PAPER || prs_action->mark == ROCK || prs_action->mark == SCISSOR);
	delete action;
}

void test_Match() {
	RandomPlayer rp("RandomPlayer");
	RandomPlayer rp2("RandomPlayer2");
	std::set<PaperRockScissorsPlayer *> players;
	players.insert(&rp), players.insert(&rp2);
	
	PaperRockScissorsMatch match(players);
	assert(match.moves.empty());
	/*
	//protected method
	match.setup(players);
	assert(match.moves.empty());
	assert(players.size() == 2 && players[0] == &rp && players[1] == &rp2);
	assert(rp.mark != rp2.mark);
	for(const Pub::Player *player : match.get_players())
		assert(player == &rp || player == &rp2);
	*/
	PaperRockScissorsState game;
	/*
	// protected method
	Games::Match<Pub::Player, Pub::Action, Pub::PaperRockScissorsState>::Move move(&rp, action);
	assert(match.allowed(&move, game)); 
	delete action;
	*/
	assert(match.get_result(&rp) == Games::UNKNOWN);
	
	/*
	//protected method
	action = match.invalid_action(&rp, game);
	assert(action);
	coord.col = action->first;
	for(coord.row = 0; coord.row < game.row_size(); ++coord.row)
		assert(!game.valid(coord));
	coord.col = action->second;
	for(coord.row = 0; coord.row < game.row_size(); ++coord.row)		
	                                                            	assert(!game.valid(coord));
	delete action;
	*/
	match.moves.push_back(new PaperRockScissorsMatch::Move(&rp, new PaperRockScissorsAction(PAPER, 1)));
	match.moves.back()->execute(game);
	match.moves.push_back(new PaperRockScissorsMatch::Move(&rp2, new PaperRockScissorsAction(ROCK, 1)));
	match.moves.back()->execute(game);
	
	/*
	//protected method
	assert(match.over(game));
	
	//protected methods	
	assert(match.count_in_row(game, rp.mark) == (game.row_size())*(game.col_size() - 3 - 1));
	assert(match.count_in_row(game, opponent_mark(rp.mark)) == 0);
	assert(match.count_in_col(game, rp.mark) == game.col_size()*(game.row_size() - 3 - 1));
	assert(match.count_in_col(game, opponent_mark(rp.mark)) == (game.row_size() - 3));
	assert(match.count_in_diag(game, rp.mark) == 2*(game.col_size() - 3 - 1)*(game.row_size() - 3));
	assert(match.count_in_diag(game, opponent_mark(rp.mark)) == 0);
	*/
	assert(match.get_result(&rp) == Games::VICTORY);	
	assert(match.get_result(&rp2) == Games::DEFEAT);
	
	delete match.moves.back(), match.moves.pop_back();
	match.moves.push_back(new PaperRockScissorsMatch::Move(&rp2, new PaperRockScissorsAction(SCISSOR, 1)));
	assert(match.get_result(&rp2) == Games::VICTORY);	
	assert(match.get_result(&rp) == Games::DEFEAT);
	
	delete match.moves.front(), match.moves.pop_front();
	match.moves.push_front(new PaperRockScissorsMatch::Move(&rp, new PaperRockScissorsAction(INVALID, 1)));
	assert(match.get_result(&rp) == Games::UNKNOWN);	
	assert(match.get_result(&rp2) == Games::UNKNOWN);
	
	/*
	//protected method
	match.setup(players);
	*/
	IIA::Utils::empty(match.moves);
	match.play();
	// Não é possível saber como acaba com RandomPlayer, mas a partida não deve 
	// deixar uma exceção subir.
}

} // namespace Test
} // namespace PaperRockScissors
} // namespace Games

int main(int argc, char **argv) {
	using namespace Games::PaperRockScissors::Test;
	
	test_Mark();
	test_State();
	test_Action();
	test_RandomPlayer();
	test_Match();
	
	return 0;
}

