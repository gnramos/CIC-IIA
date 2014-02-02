/** @file RoundRobinTournament.hpp
 *
 * Define um campeonato de pontos corridos.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 01/2012 */

#ifndef GAMES_ROUNDROBIN_TOURNAMENT_HPP
#define GAMES_ROUNDROBIN_TOURNAMENT_HPP

#include <algorithm>

#include "Tournament.hpp"

namespace Games {
/** Define um campeonato em que cada jogador enfrenta todos os adversários.
* Mais informações na <a href="http://en.wikipedia.org/wiki/Round-robin_tournament">Wikipedia</a>. */
template <class match_t, class player_t>
class RoundRobin : public Tournament<match_t, player_t> {
public:
	/** Construtor.
	 *
	 * @param p os jogadores do campeonato. */
	RoundRobin(const std::deque<player_t *> &p)
		: Tournament<match_t, player_t> (p) {
			srand (unsigned(time(nullptr))); // para random_shuffle
  	}

protected:
	void setup_players(std::deque<player_t *> &tournament_players) {
		tournament_players.assign(this->players.begin(), this->players.end());
		std::random_shuffle(tournament_players.begin(), tournament_players.end());

		/** Define o 1o elemento como "bye", se necessário" */
		if(tournament_players.size() % 2)
			tournament_players.push_front(nullptr);
	}

	std::deque<std::deque<match_t *> > *push_back_new_round(std::deque<player_t *> &tournament_players, unsigned int num_matches) {
		this->rounds.push_back(std::deque<std::deque<match_t *> >());
		std::deque<std::deque<match_t *> > *new_round = &(this->rounds.back());

		int half = tournament_players.size()/2;
		int j = (tournament_players[0] ? 0 : 1); //"bye" é o 1o

		for(; j < half; ++j) {
			std::deque<player_t *> match_players(1, tournament_players[j]);
			match_players.push_back(tournament_players[j+half]);

			new_round->push_back(best_out_of<match_t, player_t>(num_matches, match_players));
		}

		return new_round;
	}

	void next(std::deque<std::deque<match_t *> > *last_round, std::deque<player_t *> &tournament_players) {
		int half = tournament_players.size()/2;

		/** "Rotates clockwise" */
		tournament_players.insert(tournament_players.begin() + 1, tournament_players[half]);
		tournament_players.erase(tournament_players.begin() + half + 1);
		tournament_players.insert(tournament_players.end(), tournament_players[half]);
		tournament_players.erase(tournament_players.begin() + half);
	}

	bool over(const std::deque<std::deque<match_t *> > *last_round, const std::deque<player_t *> &tournament_players) {
		return (this->rounds.size() >= (tournament_players.size() - 1));
	}
};
} // namespace Games
#endif /* GAMES_ROUNDROBIN_TOURNAMENT_HPP */
