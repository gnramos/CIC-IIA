/** @file TestTicTacToe.cpp
 *
 * Implementa as funções de teste para o Jogo-da-Velha.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */


#include <assert.h>

#include "TicTacToeSimplePlayer.h"
#include "TicTacToeMatch.h"

namespace Games {
namespace TicTacToe {
namespace Test {
// using namespace Games::TicTacToe;

void test_Mark() {
	Mark mark = CROSS;
	assert(mark != EMPTY && mark != NOUGHT);
	mark = NOUGHT;
	assert(mark != EMPTY && mark != CROSS);
	mark = EMPTY;
	assert(mark != NOUGHT && mark != CROSS);

	assert(opponent_mark(CROSS) == NOUGHT);
	assert(opponent_mark(NOUGHT) == CROSS);
	try {
		opponent_mark(EMPTY);
		assert(false);
	} catch(std::invalid_argument e) {}

	std::stringstream sstr;
	sstr << mark;
	assert(sstr.str() == " ");
	sstr << CROSS << NOUGHT;
	assert(sstr.str() == " XO");
}

void test_invalid_coord(TicTacToeState &state, const Games::Grids::Coord2D &coord) {
	try {
		state[coord] = CROSS;
		assert(false);
	} catch(std::invalid_argument e) {}
}

void test_State() {
	TicTacToeState state;
	assert(state.row_size() == 3 && state.col_size() == 3);

	Games::Grids::Coord2D coord;
	for(; coord.row < 3; ++coord.row)
		for(coord.col = 0; coord.col < 3; ++coord.col)
			assert(state[coord] == EMPTY);
	
	std::stringstream sstr;
	sstr << state;
	assert(sstr.str() == "\n     \n     \n     ");

	coord.row = 0, coord.col = 0;
	state[coord] = CROSS;
	assert(state[coord] == CROSS);
	sstr.str(std::string()), sstr << state;
	assert(sstr.str() == "\nX    \n     \n     ");
	state[coord] = EMPTY;
	assert(state[coord] == EMPTY);
	sstr.str(std::string()), sstr << state;
	assert(sstr.str() == "\n     \n     \n     ");

	coord.row = 3, test_invalid_coord(state, coord);
	coord.col = 3, test_invalid_coord(state, coord);
	coord.row = 1, test_invalid_coord(state, coord);
}

void test_action_constructor(Games::Grids::Coord2D &coord, Mark mark, double cost) {
	TicTacToeAction action(coord, mark, cost);
	assert(action.coord == coord && action.mark == mark && action.cost == cost);
}

void test_Action() {
	Games::Grids::Coord2D coord;
	Mark mark = CROSS;
	double cost = 1;
	TicTacToeAction action(coord, mark, cost);

	test_action_constructor(coord, mark, cost);
	coord.row = 3, mark = EMPTY, cost = 0;
	test_action_constructor(coord, mark, cost);
	coord.col = 3, mark = NOUGHT, cost = -1;
	test_action_constructor(coord, mark, cost);

	TicTacToeAction *ptr_action = action.clone();
	assert(ptr_action->coord == action.coord && ptr_action->mark == action.mark && ptr_action->cost == action.cost);

	TicTacToeState state;
	TicTacToeState *result_state = action.result(state);
	assert(result_state && (*result_state)[action.coord] == action.mark);
	assert(state[ptr_action->coord] != ptr_action->mark);
	ptr_action->execute(state);
	assert(state[ptr_action->coord] == ptr_action->mark);

	delete ptr_action, delete result_state;
}

void test_PlayerBase(TicTacToePlayer *player, Mark mark, std::string name) {
	//assert(player->mark == mark && player->id == name);

	try {
		player->percept();
		assert(false);
	} catch(std::ios_base::failure e) {}

	Games::Grids::Coord2D coord;
	TicTacToeState state;
	for(coord.row = 0; coord.row < 3; ++coord.row)
		for(coord.col = 0; coord.col < 3; ++coord.col)
			state[coord] = player->mark;

	try {
		delete player->decide_action(state);
		assert(false);
	} catch(std::invalid_argument e) {}
}

void test_DummyPlayer() {
	DummyPlayer dp(CROSS, "TestDummyPlayer");
	test_PlayerBase(&dp, CROSS, "TestDummyPlayer");

	TicTacToeState state;
	Games::Grids::Coord2D coord;
	for(; coord.row < 3; ++coord.row) {
		for(coord.col = 0; coord.col < 3; ++coord.col) {
			IIA::Action<TicTacToeState> *action = dp.decide_action(state);
			assert(action && action->cost > 0);
			TicTacToeAction *ttt_action = static_cast<TicTacToeAction *>(action);
			assert(ttt_action->coord == coord);
			action->execute(state);
			delete action;
		}
	}
}

void test_SimplePlayer() {
	SimplePlayer sp(CROSS, "SimplePlayer");
	test_PlayerBase(&sp, CROSS, "SimplePlayer");

	SlowSimplePlayer ssp(CROSS, "SlowSimplePlayer");
	test_PlayerBase(&ssp, CROSS, "SlowSimplePlayer");

	Games::Grids::Coord2D coord;
	TicTacToeState state;
	coord.row = 0, coord.col = 0, state[coord] = NOUGHT;
	coord.row = 0, coord.col = 1, state[coord] = NOUGHT;
	coord.row = 0, coord.col = 2, state[coord] = CROSS;
	coord.row = 1, coord.col = 1; state[coord] = CROSS;

	// Try to win
	IIA::Action<TicTacToeState> *sp_action = sp.decide_action(state);
	IIA::Action<TicTacToeState> *ssp_action = ssp.decide_action(state);

	assert(sp_action && sp_action->cost > 0);
	assert(ssp_action && ssp_action->cost > 0);
	assert(sp_action->cost < ssp_action->cost);

	TicTacToeAction *ttt_sp_action = static_cast<TicTacToeAction *>(sp_action);
	TicTacToeAction *ttt_ssp_action = static_cast<TicTacToeAction *>(ssp_action);

	assert(ttt_sp_action->coord.row == 2 && ttt_sp_action->coord.col == 0);
	assert(ttt_ssp_action->coord.row == 2 && ttt_ssp_action->coord.col == 0);

	delete sp_action, delete ssp_action;

	// Block opponent
	coord.row = 2, coord.col = 0; state[coord] = NOUGHT;
	sp_action = sp.decide_action(state);
	ssp_action = ssp.decide_action(state);

	assert(sp_action && sp_action->cost > 0);
	assert(ssp_action && ssp_action->cost > 0);
	assert(sp_action->cost < ssp_action->cost);

	ttt_sp_action = static_cast<TicTacToeAction *>(sp_action);
	ttt_ssp_action = static_cast<TicTacToeAction *>(ssp_action);
	assert(ttt_sp_action->coord.row == 1 && ttt_sp_action->coord.col == 0);
	assert(ttt_ssp_action->coord.row == 1 && ttt_ssp_action->coord.col == 0);

	delete sp_action, delete ssp_action;
}

void test_Match() {
	SimplePlayer sp(CROSS, "SimplePlayer");
	SlowSimplePlayer ssp(NOUGHT, "SlowSimplePlayer");
	
	std::deque<TicTacToePlayer *> players;
	players.push_back(&sp), players.push_back(&ssp);
	TicTacToeMatch match(players);
	assert(match.moves.empty());

	TicTacToeState game;

	Games::Grids::Coord2D coord;
	TicTacToeAction *action = new TicTacToeAction(coord, sp.mark, 1);//= new DoNothing<TicTacToeState>();
	Games::Match<TicTacToePlayer, TicTacToeAction, TicTacToeState>::Move move(&sp, action);
	//assert(match.allowed(&move, game));
	assert(match.get_result(&sp) == Games::UNKNOWN);
	assert(match.get_result(&ssp) == Games::UNKNOWN);

	delete action;
	//action = match.invalid_action();
	//assert(action && !game.valid(action->coord));
	//delete action;

	for(coord.row = 0; coord.row < 3; ++coord.row)
		for(coord.col = 0; coord.col < 3; ++coord.col)
			game[coord] = sp.mark;

	// assert(match.over(game));
	// match.setup();

	match.play();

	// SimplePlayer x SimplePlayer match always ends like this (X starts):
	// O X X
	// O X
	// O O X
	assert(match.moves.size() == 8);
	assert(match.get_result(&sp) == Games::DEFEAT);
	assert(match.get_result(&ssp) == Games::VICTORY);

	players.push_back(players.front()), players.pop_front();
	
	TicTacToeMatch m2(players);
	m2.play();
	assert(m2.moves.size() == 8);
	assert(m2.get_result(&sp) == Games::VICTORY);
	assert(m2.get_result(&ssp) == Games::DEFEAT);

	for(const TicTacToePlayer *player : m2.get_players())
		assert(player == &sp || player == &ssp);
}
} // namespace Test
} // namespace TicTacToe
} // namespace Games

int main(int argc, char **argv) {
	using namespace Games::TicTacToe::Test;
	test_Mark();
	test_State();
	test_Action();
	test_DummyPlayer();
	test_SimplePlayer();
	test_Match();

	return 0;
}

