/** @file TestPub.cpp
 * 
 * Implementa as funções de teste para o jogo Pub.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#include <assert.h>

#include "Utils.h"
#include "PubRandomPlayer.h"

using namespace Games::Pub;

void test_Mark() {
	Mark mark = WHITE;
	assert(mark != EMPTY && mark != BLACK);
	mark = BLACK;
	assert(mark != EMPTY && mark != WHITE);
	mark = EMPTY;
	assert(mark != BLACK && mark != WHITE);

	assert(opponent_mark(WHITE) == BLACK);
	assert(opponent_mark(BLACK) == WHITE);
	try {
		opponent_mark(EMPTY);
		assert(false);
	} catch(std::invalid_argument e) {}

	std::stringstream sstr;
	sstr << mark;
	assert(sstr.str() == " ");
	sstr << WHITE << BLACK;
	assert(sstr.str() == " OX");
}

void test_invalid_coord(PubState &state, const Games::Grids::Coord2D &coord) {
	try {
		state[coord] = WHITE;
		assert(false);
	} catch(std::invalid_argument e) {}
}

void test_State() {
	PubState state;
	assert(state.row_size() == 8 && state.col_size() == 5);

	Games::Grids::Coord2D coord;
	std::string str;
	for(; coord.row < state.row_size(); ++coord.row) {
		str += "\n";
		for(coord.col = 0; coord.col < state.col_size(); ++coord.col) {
			assert(state[coord] == EMPTY);
			str += IIA::Utils::String::to_string(EMPTY);
			if(coord.col < state.col_size()-1) str += " ";
		}
	}

	coord.row = 0, coord.col = 0;
	state[coord] = WHITE;
	assert(state[coord] == WHITE);
	state[coord] = EMPTY;
	assert(state[coord] == EMPTY);

	coord.row = state.row_size(), test_invalid_coord(state, coord);
	coord.col = state.col_size(), test_invalid_coord(state, coord);
	coord.row = 0, test_invalid_coord(state, coord);

	std::stringstream sstr;
	sstr << state;
	assert(sstr.str() == str);
}

void test_action_constructor(const unsigned int first, const unsigned int second, Mark mark, double cost) {
	PubAction action(first, second, mark, cost);
	assert(action.first == first && action.second == second && action.mark == mark && action.cost == cost);
}

void test_Action() {
	unsigned int first = 0, second = 0;
	Mark mark = WHITE;
	double cost = 1;

	test_action_constructor(first, second, mark, cost);
	first = 5, mark = EMPTY, cost = 0;
	test_action_constructor(first, second, mark, cost);
	second = 8, mark = BLACK, cost = -1;
	test_action_constructor(first, second, mark, cost);
	first = 0, mark = BLACK, cost = 1;
	test_action_constructor(first, second, mark, cost);


	PubAction action(0, 0, mark, cost);
	PubAction *ptr_action = action.clone();
	assert(ptr_action->first == action.first && ptr_action->second == action.second);
	assert(ptr_action->mark == action.mark && ptr_action->cost == action.cost);

	PubState state;
	Games::Grids::Coord2D coord(0, action.first);
	PubState *result_state = action.result(state);
	assert(result_state && (*result_state)[coord] == action.mark);
	coord.col = action.second;
	assert(result_state && (*result_state)[coord] == action.mark);
	
	coord.row = 1;
	ptr_action->execute(state);
	assert(state[coord] == ptr_action->mark);
	coord.col = ptr_action->first;
	assert(state[coord] == ptr_action->mark);

	delete ptr_action, delete result_state;
}

void test_PlayerBase(PubPlayer *player, Mark mark, std::string name) {
	//assert(player->mark == mark && player->id == name);

	try {
		player->percept();
		assert(false);
	} catch(std::invalid_argument e) {}
/*
	Games::Grids::Coord2D coord;
	Pub::State state;
	for(coord.row = 0; coord.row < state.row_size(); ++coord.row)
		for(coord.col = 0; coord.col < state.col_size(); ++coord.col)
			state[coord] = player->mark;
	try {
		delete player->decide_action(state);
		assert(false);
	} catch(std::ios_base::failure e) {}
	*/
}

void test_PubRandomPlayer() {
	PubRandomPlayer rp(WHITE, "TestPubRandomPlayer");
	test_PlayerBase(&rp, WHITE, "TestPubRandomPlayer");
	
	PubState state;
	IIA::Action<PubState> *action = rp.decide_action(state);
	assert(action && action->cost > 0);
	
	PubAction *pub_action = static_cast<PubAction *>(action);
	assert(0 <= pub_action->first && pub_action->first < state.col_size());
	assert(0 <= pub_action->second && pub_action->second < state.col_size());
	delete action;
}

void test_Match() {	
                   	PubRandomPlayer rp(WHITE, "PubRandomPlayer");
                   	PubRandomPlayer rp2(rp.mark, "PubRandomPlayer2");
                   	std::deque<PubPlayer *> players;
                   	players.push_back(&rp), players.push_back(&rp2);
                   	
                   	PubMatch match(players);
                   	assert(match.players == players);
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
                   	PubState game;
                   	Games::Grids::Coord2D coord;
                   	/*
                   	// protected method
                   	Games::Match<Pub::Player, Pub::Action, Pub::State>::Move move(&rp, action);
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
                   	coord.row = 0;
                   	for(coord.col = 0; coord.col < game.col_size() - 1; ++coord.col) {
                   		for(coord.row = 0; coord.row < game.row_size(); coord.row += 2) {
                   			match.moves.push_back(new PubMatch::Move(&rp, new PubAction(coord.col, coord.col, rp.mark, 1)));
                   			match.moves.back()->execute(game);
                   		}
                   	}

	// ultima coluna completa para rp2
	rp2.mark = opponent_mark(rp.mark); // seria ajustado na função setup
	match.moves.push_front(new PubMatch::Move(&rp2, new PubAction(coord.col, coord.col, rp2.mark, 1)));
	match.moves.front()->execute(game); // frente para passar na função "over"
	
	for(coord.row = 2; coord.row < game.row_size(); coord.row += 2) {
		match.moves.push_back(new PubMatch::Move(&rp2, new PubAction(coord.col, coord.col, rp2.mark, 1)));
		match.moves.back()->execute(game);
	}
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
	/*
	//protected method
	match.setup(players);
	*/
	match.play();
	// Não é possível saber como acaba com PubRandomPlayer, mas a partida não deve 
	// deixar uma exceção subir.
}

int main(int argc, char **argv) {
	test_Mark();
	test_State();
	test_Action();
	test_PubRandomPlayer();
	test_Match();
	
	return 0;
}

