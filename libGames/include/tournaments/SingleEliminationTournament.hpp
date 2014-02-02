/** @file SingleEliminationTournament.hpp
 *
 * Este arquivo contem a definição da classe abstrata Tournament, que define
 * a implementação de um campeonato (múltiplos jogadores competindo entre si).
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 01/2012 */

#ifndef GAMES_SINGLE_ELIMINATION_TOURNAMENT_HPP
#define GAMES_SINGLE_ELIMINATION_TOURNAMENT_HPP

#include <algorithm>

#include "MatchStats.hpp"
#include "Tournament.hpp"

namespace Games {
namespace {
template <class match_t, class player_t>
bool simple_tiebreaker(const Statistics::PlayerMultipleMatchStat<match_t, player_t> &lhs, 
					   const Statistics::PlayerMultipleMatchStat<match_t, player_t> &rhs) {
	return lhs < rhs;
}
}

/** Define um campeonato em que um jogador é eliminado em caso de derrota ("morte
* súbita"). Mais informações na <a href="http://en.wikipedia.org/wiki/Single-elimination_tournament">Wikipedia</a>. */
template <class match_t, class player_t>
class SingleElimination : public Tournament<match_t, player_t> {
public:
	/** Construtor. */
	SingleElimination(const std::deque<player_t *> &p /**< jogadores do campeonato */)
		: Tournament<match_t, player_t> (p), tiebreaker(simple_tiebreaker) {
			srand (unsigned(time(nullptr))); // para random_shuffle
	}
	
	using Tournament<match_t, player_t>::run;
	
	/** Implementa o campeonato, organizando as rodadas entre os jogadores
	 * inscritos. */
	void run(bool (*cmp)(const Statistics::PlayerMultipleMatchStat<match_t, player_t> &lhs, 
						   const Statistics::PlayerMultipleMatchStat<match_t, player_t> &rhs),
					unsigned int num_matches = 1) {

		bool (*old_tiebreaker)(const Statistics::PlayerMultipleMatchStat<match_t, player_t> &lhs, 
					  const Statistics::PlayerMultipleMatchStat<match_t, player_t> &rhs) = tiebreaker;
		tiebreaker = cmp;
		run(num_matches);
		tiebreaker = old_tiebreaker;
	}

protected:
	void setup_players(std::deque<player_t *> &tournament_players) {
		tournament_players.assign(this->players.begin(), this->players.end());
		std::random_shuffle(tournament_players.begin(), tournament_players.end());

		int missing_players = 2;
		while(missing_players < tournament_players.size()) missing_players *= 2;
		missing_players -= tournament_players.size();
		tournament_players.insert(tournament_players.end(), missing_players, nullptr);
	}

	std::deque<std::deque<match_t *> > *push_back_new_round(std::deque<player_t *> &tournament_players, unsigned int num_matches) {
		this->rounds.push_back(std::deque<std::deque<match_t *> >());
		std::deque<std::deque<match_t *> > *new_round = &(this->rounds.back());

		player_t *null_player = nullptr;
		int fwd = 0, bwd = tournament_players.size() - 1;
		while(fwd < bwd) {
			std::deque<player_t *> match_players(1, tournament_players[fwd]);
			match_players.push_back(tournament_players[bwd]);

			if(!IIA::Utils::contains(match_players, null_player))
				new_round->push_back(best_out_of<match_t, player_t>(num_matches, match_players));

			++fwd, --bwd;
		}

		return new_round;
	}
	
	void next(std::deque<std::deque<match_t *> > *last_round, std::deque<player_t *> &tournament_players) {
		while(!tournament_players.back()) tournament_players.pop_back();
		
		std::deque<Statistics::PlayerMultipleMatchStat<match_t, player_t> > winner_stats;
	
		for(std::deque<match_t *> dispute : *last_round) {
			Statistics::MultipleMatchStat<match_t, player_t> stat(dispute);
			std::sort(stat.player_stats.begin(), stat.player_stats.end(), tiebreaker);

			winner_stats.push_back(stat.player_stats.front());
			for(auto st : stat.player_stats) {
				for(auto it = tournament_players.begin(); it != tournament_players.end(); ++it) {
					if(*it == st.player) {
						tournament_players.erase(it);
						break;
					}
				}
			}
		}
		
		std::sort(winner_stats.begin(), winner_stats.end(), tiebreaker);
		for(typename std::deque<Statistics::PlayerMultipleMatchStat<match_t, player_t> >::reverse_iterator it = winner_stats.rbegin(); it != winner_stats.rend(); ++it)
			tournament_players.push_front(it->player);
	}

	bool over(const std::deque<std::deque<match_t *> > *last_round, const std::deque<player_t *> &tournament_players) {
		return (tournament_players.size() == 1);
	}
	
	// Attributes
	
	/** Referência para uma função que define um vencedor em caso de empate. */
	bool (*tiebreaker)(const Statistics::PlayerMultipleMatchStat<match_t, player_t> &lhs, 
					  const Statistics::PlayerMultipleMatchStat<match_t, player_t> &rhs);
};
} // namespace Games
#endif /* GAMES_SINGLE_ELIMINATION_TOURNAMENT_HPP */
