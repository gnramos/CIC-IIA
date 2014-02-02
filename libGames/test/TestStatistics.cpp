/** @file TestStatistics.cpp
 * 
 * Implementa testes para a classes Games::Stats.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */
#include <iostream> 
#include <algorithm>
#include <assert.h>

#include "MatchStats.hpp"
#include "PaperRockScissors.h"


namespace Games {
namespace PaperRockScissors {
namespace Test {
namespace {
	
typedef Games::Statistics::PlayerStat<PaperRockScissorsPlayer> PlayerStatistic;
typedef Games::Statistics::PlayerMatchStat<PaperRockScissorsMatch, PaperRockScissorsPlayer> PlayerSingle;
typedef Games::Statistics::PlayerMultipleMatchStat<PaperRockScissorsMatch, PaperRockScissorsPlayer> PlayerMultiple;
typedef Games::Statistics::MatchStat<PaperRockScissorsMatch, PaperRockScissorsPlayer> MatchSingle;
typedef Games::Statistics::MultipleMatchStat<PaperRockScissorsMatch, PaperRockScissorsPlayer> MatchMultiple;

void test_Player_Statistic() {
	try {
		PlayerStatistic(nullptr, 0, -1);
		assert(false);
	} catch(std::invalid_argument e) {}

	RandomPlayer player;
	PlayerStatistic ps(&player, 0, -1);
	assert(ps.player == &player);
	assert(ps.num_moves == 0);
	assert(ps.total_cost == -1);
	
	PlayerStatistic ps2(&player, 5, 10);
	assert(ps2.player == &player);
	assert(ps2.num_moves == 5);
	assert(ps2.total_cost == 10);	
}

void test_Player_PlayerMatchStat() {
	std::set<PaperRockScissorsPlayer *> players;
	PaperPlayer p1("p1");
	RockPlayer r1("r1");
	players.insert(&p1), players.insert(&r1);
	
	PaperRockScissorsMatch match(players);
	
	PlayerSingle stat(match, &p1);
	assert(stat.player == &p1);
	assert(stat.num_moves == 0);
	assert(stat.total_cost == 0);	
	assert(stat.result == Games::UNKNOWN);
	
	stat = PlayerSingle(match, &r1);
	assert(stat.player == &r1);
	assert(stat.num_moves == 0);
	assert(stat.total_cost == 0);	
	assert(stat.result == Games::UNKNOWN);
	
	match.play();
	stat = PlayerSingle(match, &p1);
	assert(stat.player == &p1);
	assert(stat.num_moves == 1);
	assert(stat.total_cost == 1);	
	assert(stat.result == Games::VICTORY);
	
	stat = PlayerSingle(match, &r1);
	assert(stat.player == &r1);
	assert(stat.num_moves == 1);
	assert(stat.total_cost == 1);	
	assert(stat.result == Games::DEFEAT);
}

void test_Player_PlayerMultipleMatchStat() {
	std::deque<PaperRockScissorsMatch *> matches;
	std::set<PaperRockScissorsPlayer *> players;
	
	PaperPlayer p1("p1");
	RockPlayer r1("r1");
	ScissorsPlayer s1("s1");
	
	players.insert(&p1);
	players.insert(&r1);
	matches.push_back(new PaperRockScissorsMatch(players));
	
	players.erase(players.find(&r1)), players.insert(&s1);
	matches.push_back(new PaperRockScissorsMatch(players));
	
	players.erase(players.find(&p1)), players.insert(&r1);
	matches.push_back(new PaperRockScissorsMatch(players));
	
	for(PaperRockScissorsMatch *m : matches) m->play();
	
	PlayerMultiple mmps_p1(matches, &p1);
	assert(mmps_p1.num_moves == 2);
	assert(mmps_p1.total_cost == 2);
	assert(mmps_p1.num_matches == 2);
	assert(mmps_p1.num_victories == 1);
	assert(mmps_p1.num_defeats == 1);
	assert(mmps_p1.num_draws == 0);
	
	IIA::Utils::empty(matches);
}

void test_Match_Single() {
	std::set<PaperRockScissorsPlayer *> players;
	players.insert(new RandomPlayer("p1"));
	players.insert(new RandomPlayer("p2"));
	
	PaperRockScissorsMatch match(players);
	match.play();
	
	MatchSingle stat(match);
	assert(stat.num_moves > 1);
	assert(stat.total_cost > 1);
	assert(stat.player_stats.size() == 2);
	for(PlayerSingle ps : stat.player_stats) {
		assert(players.find(ps.player) != players.end());
		assert(ps.num_moves > 0);
		assert(ps.total_cost > 0);
	}
	
	IIA::Utils::empty(players);
}

void test_Match_Multiple() {
	std::deque<PaperRockScissorsMatch *> matches;
	std::set<PaperRockScissorsPlayer *> players;
	
	PaperPlayer p1("p1");
	RockPlayer r1("r1");
	ScissorsPlayer s1("s1");
	
	players.insert(&p1);
	players.insert(&r1);
	matches.push_back(new PaperRockScissorsMatch(players));
	matches.push_back(new PaperRockScissorsMatch(players));
	
	players.erase(players.find(&r1)), players.insert(&s1);
	matches.push_back(new PaperRockScissorsMatch(players));
	
	players.erase(players.find(&p1)), players.insert(&r1);
	matches.push_back(new PaperRockScissorsMatch(players));
	
	for(PaperRockScissorsMatch *m : matches) m->play();
	
	MatchMultiple stats(matches);
	assert(stats.num_moves == 8);
	assert(stats.total_cost == 8);
	
	for(PlayerMultiple ps : stats.player_stats) {
		if(ps.player == &p1) {
			assert(ps.num_moves == 3);
			assert(ps.total_cost == 3);
			assert(ps.num_matches == 3);
			assert(ps.num_victories == 2);
			assert(ps.num_defeats == 1);
			assert(ps.num_draws == 0);
		} else if(ps.player == &r1) {
			assert(ps.num_moves == 3);
			assert(ps.total_cost == 3);
			assert(ps.num_matches == 3);
			assert(ps.num_victories == 1);
			assert(ps.num_defeats == 2);
			assert(ps.num_draws == 0);
		} else if(ps.player == &s1) {
			assert(ps.num_moves == 2);
			assert(ps.total_cost == 2);
			assert(ps.num_matches == 2);
			assert(ps.num_victories == 1);
			assert(ps.num_defeats == 1);
			assert(ps.num_draws == 0);
		} else assert(false);
	}
	
	IIA::Utils::empty(matches);
}

void test_Sort_Players() {
	RandomPlayer p1("p1");
	RandomPlayer p2("p2");
	RandomPlayer p3("p3");

	std::deque<PlayerStatistic> stats;
	stats.push_back(PlayerStatistic(&p1, 2, 1));
	stats.push_front(PlayerStatistic(&p2, 3, 1));
	
	assert(stats[0].player == &p2);
	std::sort(stats.begin(), stats.end());
	assert(stats[0].player == &p1);
	
	stats.push_back(PlayerStatistic(&p3, 4, 0.5));
	std::sort(stats.begin(), stats.end());
	assert(stats[0].player == &p3);
}

void test_Sort_Match_Single() {
	std::set<PaperRockScissorsPlayer *> players;
	RandomPlayer p1("p1"), p2("p2");
	players.insert(&p1);
	players.insert(&p2);
	
	PaperRockScissorsMatch match(players);
	match.moves.push_back(new PaperRockScissorsMatch::Move(&p1, new PaperRockScissorsAction(PAPER, 1)));
	match.moves.push_back(new PaperRockScissorsMatch::Move(&p2, new PaperRockScissorsAction(ROCK, 1)));
	
	MatchSingle stat(match);
	
	std::sort(stat.player_stats.begin(), stat.player_stats.end());

	assert(stat.player_stats[0].player == &p1);
	assert(stat.player_stats[0].result == Games::VICTORY);

	assert(stat.player_stats[1].player == &p2);
	assert(stat.player_stats[1].result == Games::DEFEAT);
}

void test_Sort_Match_Multiple() {
	std::deque<PaperRockScissorsMatch *> matches;
	std::set<PaperRockScissorsPlayer *> players;
	
	PaperPlayer p1("p1"), p2("p2");
	RockPlayer r1("r1");
	//ScissorPlayer s1("s1");
	
	players.insert(&p1);
	players.insert(&r1);
	matches.push_back(new PaperRockScissorsMatch(players));
	matches.push_back(new PaperRockScissorsMatch(players));
	
	players.erase(players.find(&r1)), players.insert(&p2);
	matches.push_back(new PaperRockScissorsMatch(players));
	
	players.erase(players.find(&p1)), players.insert(&r1);
	matches.push_back(new PaperRockScissorsMatch(players));
	matches.push_back(new PaperRockScissorsMatch(players));
	
	players.erase(players.find(&r1)), players.insert(&p1);
	matches.push_back(new PaperRockScissorsMatch(players));
	
	for(PaperRockScissorsMatch *m : matches) m->play();
	
	MatchMultiple stat(matches);	
	std::sort(stat.player_stats.begin(), stat.player_stats.end());

	std::cout << "\n\n" << stat << "\n\n";
	assert(stat.player_stats[0].player == &p1 || stat.player_stats[0].player == &p2);
	assert(stat.player_stats[2].player == &r1);
	
	IIA::Utils::empty(matches);
}
} // unnamed namespace
} // namespace Test
} // namespace PaperRockScissors
} // namespace Games

int main(int argc, char **argv) {
	using namespace Games::PaperRockScissors::Test;

	test_Player_Statistic();
	test_Player_PlayerMatchStat();
	test_Player_PlayerMultipleMatchStat();
	test_Match_Single();
	test_Match_Multiple();
	test_Sort_Players();
	test_Sort_Match_Single();
	test_Sort_Match_Multiple();
	
	return 0;
}
