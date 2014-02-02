/** @file TestTournament.cpp
 * 
 * Implementa testes para a classe Games::Tournament.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */
 
#include <assert.h>

#include "PaperRockScissors.h"
#include "MatchStats.hpp"
#include "RoundRobinTournament.hpp"
#include "SingleEliminationTournament.hpp"

namespace Games {
namespace PaperRockScissors {
namespace Test {
namespace {
void test_best_out_of() {
	PaperPlayer pp;
	RockPlayer rp;
	std::deque<PaperRockScissorsPlayer *> players;
	try {
		Games::best_out_of<PaperRockScissorsMatch, PaperRockScissorsPlayer>(0, players);
		assert(false);
	} catch (std::invalid_argument e) {}
	
	try {
		Games::best_out_of<PaperRockScissorsMatch, PaperRockScissorsPlayer>(5, players);
		assert(false);
	} catch (std::invalid_argument e) {}
		
	players.push_back(&pp);
	try {
		Games::best_out_of<PaperRockScissorsMatch, PaperRockScissorsPlayer>(5, players);
		assert(false);
	} catch (std::invalid_argument e) {}
	
	players.push_back(&rp);
	try {
		Games::best_out_of<PaperRockScissorsMatch, PaperRockScissorsPlayer>(0, players);
		assert(false);
	} catch (std::invalid_argument e) {}
	
	std::deque<PaperRockScissorsMatch *> matches = Games::best_out_of<PaperRockScissorsMatch, PaperRockScissorsPlayer>(1, players);
	assert(matches.size() == 1);	
	for(PaperRockScissorsMatch *match : matches) {
		assert(match->get_result(&pp) == Games::VICTORY);
		assert(match->get_result(&rp) == Games::DEFEAT);
	}
	
	IIA::Utils::empty(matches);
	
	matches = Games::best_out_of<PaperRockScissorsMatch, PaperRockScissorsPlayer>(2, players);
	assert(matches.size() == 2);
	for(PaperRockScissorsMatch *match : matches) {
		assert(match->get_result(&pp) == Games::VICTORY);
		assert(match->get_result(&rp) == Games::DEFEAT);
	}
	
	IIA::Utils::empty(matches);
	
	matches = Games::best_out_of<PaperRockScissorsMatch, PaperRockScissorsPlayer>(3, players);
	assert(matches.size() == 2);
	for(PaperRockScissorsMatch *match : matches) {
		assert(match->get_result(&pp) == Games::VICTORY);
		assert(match->get_result(&rp) == Games::DEFEAT);
	}
	
	IIA::Utils::empty(matches);

	PaperPlayer pp2;
	players.pop_back(), players.push_back(&pp2);
	matches = Games::best_out_of<PaperRockScissorsMatch, PaperRockScissorsPlayer>(3, players);
	assert(matches.size() == 3);
	for(PaperRockScissorsMatch *match : matches) {
		for(PaperRockScissorsPlayer *player : players) {
			assert(match->get_result(player) == Games::DRAW);
		}
	}
	
	IIA::Utils::empty(matches);
}

void test_RoundRobin() {
	PaperPlayer pp;
	RockPlayer rp;
	ScissorsPlayer sp;
	std::deque<PaperRockScissorsPlayer *> players;
	
	try {
		Games::RoundRobin<PaperRockScissorsMatch, PaperRockScissorsPlayer> tournament(players);
		assert(false);
	} catch (std::invalid_argument e) {}
	
	players.push_back(&pp);
	try {
		Games::RoundRobin<PaperRockScissorsMatch, PaperRockScissorsPlayer> tournament(players);
		assert(false);
	} catch (std::invalid_argument e) {}
	
	players.push_back(&rp);
	Games::RoundRobin<PaperRockScissorsMatch, PaperRockScissorsPlayer> tournament(players);	
	assert(tournament.rounds.empty());
	
	tournament.run();
	assert(tournament.rounds.size() == players.size() - 1);
	
	players.push_back(&sp);
	tournament = Games::RoundRobin<PaperRockScissorsMatch, PaperRockScissorsPlayer>(players);	
	tournament.run(2);
	
	assert(tournament.rounds.size() == players.size());
}

bool tiebreaker(const Games::Statistics::PlayerMultipleMatchStat<PaperRockScissorsMatch, PaperRockScissorsPlayer> &lhs, 
			    const Games::Statistics::PlayerMultipleMatchStat<PaperRockScissorsMatch, PaperRockScissorsPlayer> &rhs) {
	if(lhs.player == rhs.player) return false;
	if(lhs.num_victories != rhs.num_victories) return (lhs.num_victories > rhs.num_victories);
	if(lhs.num_defeats != rhs.num_defeats) return (lhs.num_defeats < rhs.num_defeats);
	if(lhs.num_draws != rhs.num_draws) return (lhs.num_draws > rhs.num_draws);
	/*
	constexpr int max = 10;
	std::deque<Match> matches;
	std::deque<Player *> players(1, lhs.player);
	players.push_back(rhs.player);
			
	while(matches.size() < max) {
		matches.push_back(Match(players));
		matches.back().play();
		Games::Result result = matches.back().get_result(lhs.player);
		if(result != Games::DRAW) {
			return result == Games::VICTORY;
		}
	}*/
	
	if(lhs.total_cost != rhs.total_cost) 
		return (lhs.total_cost < rhs.total_cost);
	return (lhs.num_moves < rhs.num_moves);
}

void test_SingleElimination() {
	PaperPlayer p1("p1");
	std::deque<PaperRockScissorsPlayer *> players;
	
	try {
		Games::RoundRobin<PaperRockScissorsMatch, PaperRockScissorsPlayer> tournament(players);
		assert(false);
	} catch (std::invalid_argument e) {}
	
	players.push_back(&p1);
	try {
		Games::RoundRobin<PaperRockScissorsMatch, PaperRockScissorsPlayer> tournament(players);
		assert(false);
	} catch (std::invalid_argument e) {}
	
	
	RockPlayer r1("r1");
	players.push_back(&r1);
	Games::SingleElimination<PaperRockScissorsMatch, PaperRockScissorsPlayer> tournament(players);	
	assert(tournament.rounds.empty());                                                            	
	
	tournament.run();
	assert(tournament.rounds.size() == 1);
	std::deque<std::deque<PaperRockScissorsMatch *> > dispute = tournament.rounds.front();
	assert(dispute.size() == 1);
	std::deque<PaperRockScissorsMatch *> matches = dispute.front();
	assert(matches.size() == 1);
	PaperRockScissorsMatch *match = matches.front();
	assert(match);
	assert(match->get_result(&p1) == Games::VICTORY);
	assert(match->get_result(&r1) == Games::DEFEAT);
	
	RandomPlayer rp1("rp1"), rp2("rp2"), rp3("rp3");
	players.push_back(&rp1);
	players.push_back(&rp2);
	players.push_back(&rp3);
	
	tournament = Games::SingleElimination<PaperRockScissorsMatch, PaperRockScissorsPlayer>(players);
	tournament.run(tiebreaker);
	
	assert(tournament.rounds.size() == 3);	
	assert(tournament.rounds[0].size() == 1);
	assert(tournament.rounds[1].size() == 2);
	assert(tournament.rounds[2].size() == 1);
	
	RandomPlayer rp4("rp4"), rp5("rp5"), rp6("rp6");
	players.push_back(&rp4);
	players.push_back(&rp5);
	players.push_back(&rp6);
	
	tournament = Games::SingleElimination<PaperRockScissorsMatch, PaperRockScissorsPlayer>(players);
	tournament.run(tiebreaker);
	/** @todo testar resultados diferentes com critérios de desempate diferentes 
	ex: tournament.run(tiebreaker); x tournament.run()*/
	
	assert(tournament.rounds.size() == 3);	
	assert(tournament.rounds[0].size() == 4);
	assert(tournament.rounds[1].size() == 2);
	assert(tournament.rounds[2].size() == 1);
}

} // unnamed namespace
} // namespace Test
} // namespace PaperRockScissors
} // namespace Games

int main(int argc, char **argv) {
	using namespace Games::PaperRockScissors::Test;

	test_best_out_of();
	test_RoundRobin();
	test_SingleElimination();
	return 0;
}

