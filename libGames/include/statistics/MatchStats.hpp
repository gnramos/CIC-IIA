/** @file MatchStats.hpp
 *
 * Declara/define estatíticas para um jogador.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_STATISTICS_MATCH_HPP
#define GAMES_STATISTICS_MATCH_HPP

// #include <set>

#include "PlayerStats.hpp"

namespace Games {
namespace Statistics {
/** Define as estatísticas de uma partida. */
template <class match_t, class player_t>
class MatchStat : public Statistic {
public:
	/** Construtor. */
	MatchStat(const match_t &match /**< [in] partida de onde se extrai as estatísticas */
			 )
	: Statistic(0, 0) {
		for(player_t * player : match.players) {
			player_stats.push_back(PlayerMatchStat<match_t, player_t>(match, player));
			PlayerMatchStat<match_t, player_t> *singlematch = &(player_stats.back());
			num_moves += singlematch->num_moves;
			total_cost += singlematch->total_cost;
		}
	}

	/** Converte em string. */
	friend std::ostream &operator <<(std::ostream &os, const MatchStat &stat) {
		os << ", num_moves: " << stat.num_moves
		   << ", total_cost: " << stat.total_cost
		   << ", \n[" << IIA::Utils::String::join(stat.player_stats, "]\n[")
		   << "]";

		return os;
	}

	// Attributes	
	/** Estatísticas para cada jogador da partida. */
	std::deque<PlayerMatchStat<match_t, player_t> > player_stats;
};

/** Define as estatísticas de múltiplas partida. */
template <class match_t, class player_t>
class MultipleMatchStat : public Statistic {
public:
	/** Construtor.
	 *
	 * @param matches o conjunto de partidas de onde se extrai as estatísticas. */
	MultipleMatchStat(const std::deque<match_t *> &matches) : Statistic(0, 0) {
		std::set<player_t *> players;
		for(match_t *match : matches)
			players.insert(match->players.begin(), match->players.end());
		for(player_t *player : players) {
			player_stats.push_back(PlayerMultipleMatchStat<match_t, player_t>(matches, player));
			PlayerMultipleMatchStat<match_t, player_t> *multimatch = &(player_stats.back());
			num_moves += multimatch->num_moves;
			total_cost += multimatch->total_cost;
		}
	}

	/** Converte em string. */
	friend std::ostream &operator<<(std::ostream &os, const MultipleMatchStat &stat) {
		os << ", num_moves: " << stat.num_moves
		   << ", total_cost: " << stat.total_cost
		   << ", \n[" << IIA::Utils::String::join(stat.player_stats, "]\n[")
		   << "]";

		return os;
	}

	// Attributes	
	/** Estatísticas para cada jogador da partida. */
	std::deque<PlayerMultipleMatchStat<match_t, player_t> > player_stats;
};
} // namespace Statistics
} // namespace Games

#endif // GAMES_STATISTICS_MATCH_HPP
