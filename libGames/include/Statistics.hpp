/** @file Statistics.hpp
 *
 * Este arquivo contem comparações entre jogadores para ordená-los.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_STATISTICS_HPP
#define GAMES_STATISTICS_HPP

// #include <deque>
// #include <set>
// #include <stdexcept>
#include <iostream>

// #include "GameResult.h"
// #include "Utils.h"

namespace Games {
/** Limita o escopo de estatísticas. */
namespace Statistics {
/** Classe base. */
class Statistic {
public:
	/** Construtor. */
	Statistic(unsigned int n = 0, /**< número de jogadas realizadas pelo jogador */
			  double tc = 0		  /**< custo total das jogadas realizadas */
			  )
	: num_moves(n), total_cost(tc) {}

	/** Retorna o custo médio de cada jogada (total_cost/num_moves). */
	virtual double avg_cost() const {
		return (num_moves != 0 ? total_cost / num_moves : total_cost);
	}

	/** Indica se as estatísticas dadas como primeiro argumento são melhores que as
	 * dadas como segundo argumento. Menor custo é melhor, em caso de custos
	 * iguais, indica a que realizou menos jogadas. */
	bool operator<(const Statistic &that) const {
		if(this->total_cost != that.total_cost)
			return (this->total_cost < that.total_cost);
		return (this->num_moves < that.num_moves);
	}

	/** Converte em string. */
	friend std::ostream &operator <<(std::ostream &os, const Statistic &stat) {
		os << "num_moves: " << stat.num_moves
		   << ", total_cost: " << stat.total_cost;

		return os;
	}
	
	// Attributes
	unsigned int num_moves; /**< Número de jogadas. */
	double total_cost;		/**< Custo total das jogadas realizadas. */
};

// /** Define o escopo da estatística para um jogador. */
// namespace Player {
// /** Define a estatística de um jogador. */
// template <class player_t>
// class PlayerStat : public Statistic {
// public:
//	/** Construtor. */
//	PlayerStat(player_t *p,                /**< jogador ao qual a estatística se refere */
//			   unsigned int num_moves = 0, /**< número de jogadas realizadas pelo jogador */
//			   double total_cost = 0	   /**< custo total das jogadas realizadas */
//			   )
//	 : Statistic(num_moves, total_cost), player(p) {
//		if(!player)
//			throw std::invalid_argument("Cannot have statistics for player nullptr.");
//	}

//	/** Indica se as estatísticas dadas como primeiro argumento são melhores que as
//	 * dadas como segundo argumento. */
//	bool operator<(const PlayerStat &that) const {
//		if(this->player == that.player) return false;
//		return (static_cast<Statistic>(*this) < static_cast<Statistic>(that));
//	}

//	/** Converte em string. */
//	friend std::ostream &operator <<(std::ostream &os, const PlayerStat &stat) {
//		os << "player: " << *(stat.player)
//		   << ", " << static_cast<Statistic>(stat);

//		return os;
//	}

//	// Attributes
//	/** O jogador. */
//	player_t *player;
// };

// /** Define a estatística de um jogador para uma partida. */
// template <class match_t, class player_t>
// class PlayerMatchStat : public PlayerStat<player_t> {
// public:
//	/** Construtor.
//	 *
//	 * @param match a partida de onde se extrai as estatísticas.
//	 * @param player o jogador. */
//	PlayerMatchStat(const match_t &match, player_t *player) : PlayerStat<player_t>(player) {
//		for(typename match_t::Move *move : match.moves) {
//			if(move->player == player) {
//				this->num_moves++;
//				this->total_cost += move->action->cost;
//			}
//		}

//		result = match.get_result(player);
//	}

//	/** Indica se as estatísticas dadas como primeiro argumento são melhores que as
//	 * dadas como segundo argumento. */
//	bool operator<(const PlayerMatchStat &that) const {
//		if(this->result != that.result) return (this->result == VICTORY);
//		return ((*this) <  that);
//	}

//	/** Converte em string. */
//	friend std::ostream &operator <<(std::ostream &os, const PlayerMatchStat &stat) {
//		os << "player: " << *(stat.player)
//		   << ", result: " << stat.result
//		   << ", " << static_cast<PlayerStat<player_t> >(stat);

//		return os;
//	}

//	// Attributes
//	/** Resultado da partida para o jogador. */
//	GameResult result;
// };

// /** Define a estatística de um jogador para diversas partida. */
// template <class match_t, class player_t>
// class PlayerMultipleMatchStat : public PlayerStat<player_t> {
// public:
//	/** Construtor.
//	 *
//	 * @param matches o conjunto de partidas de onde se extrai as estatísticas.
//	 * @param player o jogador. */
//	PlayerMultipleMatchStat(const std::deque<match_t *> &matches, player_t *player)
//		: PlayerStat<player_t>(player),
//		  num_matches(0), num_victories(0), num_defeats(0), num_draws(0) {
//		if(matches.empty())
//			throw std::invalid_argument("Cannot have multi-match player statistics with no matches.");

//		for(match_t *match : matches) {
//			if(IIA::Utils::contains(match->players, player)) {
//				PlayerMatchStat<match_t, player_t> stat(*match, player);
//				this->num_moves += stat.num_moves;
//				this->total_cost += stat.total_cost;
//				this->num_matches++;
//				switch(stat.result) {
//				case VICTORY:
//					this->num_victories++;
//					break;
//				case DEFEAT:
//					this->num_defeats++;
//					break;
//				case DRAW:
//					this->num_draws++;
//					break;
//				default: break;
//				}
//			}
//		}
//	}
  	
//	/** Custo médio por partida. */
//	virtual double avg_cost() const {
//		int den = (num_matches != 0 ? num_matches : 1);
//		return (PlayerStat<player_t>::avg_cost() / den);
//	}

//	/** Indica se as estatísticas dadas como primeiro argumento são melhores que as
//	 * dadas como segundo argumento. */
//	bool operator<(const PlayerMultipleMatchStat &that) const {
//		if(this->player == that.player) 
//			return false;
//		if(this->num_victories != that.num_victories)
//			return (this->num_victories > that.num_victories);
//		if(this->num_defeats != that.num_defeats)
//			return (this->num_defeats < that.num_defeats);
//		if(this->num_draws != that.num_draws)
//			return (this->num_draws > that.num_draws);
//		if(this->total_cost != that.total_cost) 
//			return (this->total_cost < that.total_cost);
//		return (this->num_moves < that.num_moves);
//	}

//	/** Converte em string. */
//	friend std::ostream &operator<<(std::ostream &os, const PlayerMultipleMatchStat &stat) {
//		os << static_cast<Player::PlayerStat<player_t> >(stat)
//		<< ", num_matches: " << stat.num_matches
//		<< ", num_victories: " << stat.num_victories
//		<< ", num_defeats: " << stat.num_defeats
//		<< ", num_draws: " << stat.num_draws;
  		
//		return os;
//	}

//	// Attributes
//	/** Indica quantas partidas estão envolvidas. */
//	unsigned int num_matches;
//	/** Indica quantas partidas foram vencidas. */
//	unsigned int num_victories;
//	/** Indica quantas partidas foram perdidas. */
//	unsigned int num_defeats;
//	/** Indica quantas partidas foram empatadas. */
//	unsigned int num_draws;
// };
// } // namespace Player

// /** Defie o escopo de estatísticas para partida(s). */
// namespace Match {
// /** Define as estatísticas de uma partida. */
// template <class match_t, class player_t>
// class Single : public Statistic {
// public:
//	/** Construtor.
//	 *
//	 * @param match a partida de onde se extrai as estatísticas. */
//	Single(const match_t &match) : Statistic(0, 0) {
//		for(player_t * player : match.players) {
//			player_stats.push_back(Player::PlayerMatchStat<match_t, player_t>(match, player));
//			Player::PlayerMatchStat<match_t, player_t> *singlematch = &(player_stats.back());
//			num_moves += singlematch->num_moves;
//			total_cost += singlematch->total_cost;
//		}
//	}

//	/** Converte em string. */
//	friend std::ostream &operator <<(std::ostream &os, const Single &stat) {
//		os << ", num_moves: " << stat.num_moves
//		   << ", total_cost: " << stat.total_cost
//		   << ", \n[" << IIA::Utils::String::join(stat.player_stats, "]\n[")
//		   << "]";

//		return os;
//	}

//	// Attributes
  	
//	/** Estatísticas para cada jogador da partida. */
//	std::deque<Player::PlayerMatchStat<match_t, player_t> > player_stats;
// };

// /** Define as estatísticas de múltiplas partida. */
// template <class match_t, class player_t>
// class Multiple : public Statistic {
// public:
//	/** Construtor.
//	 *
//	 * @param matches o conjunto de partidas de onde se extrai as estatísticas. */
//	Multiple(const std::deque<match_t *> &matches) : Statistic(0, 0) {
//		std::set<player_t *> players;
//		for(match_t *match : matches)
//			players.insert(match->players.begin(), match->players.end());
//		for(player_t *player : players) {
//			player_stats.push_back(Player::PlayerMultipleMatchStat<match_t, player_t>(matches, player));
//			Player::PlayerMultipleMatchStat<match_t, player_t> *multimatch = &(player_stats.back());
//			num_moves += multimatch->num_moves;
//			total_cost += multimatch->total_cost;
//		}
//	}

//	/** Converte em string. */
//	friend std::ostream &operator<<(std::ostream &os, const Multiple &stat) {
//		os << ", num_moves: " << stat.num_moves
//		   << ", total_cost: " << stat.total_cost
//		   << ", \n[" << IIA::Utils::String::join(stat.player_stats, "]\n[")
//		   << "]";

//		return os;
//	}

//	// Attributes
  	
//	/** Estatísticas para cada jogador da partida. */
//	std::deque<Player::PlayerMultipleMatchStat<match_t, player_t> > player_stats;
// };
// } // namespace Match
} // namespace Statistics
} // namespace Games

#endif // GAMES_STATISTICS_HPP
