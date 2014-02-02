/** @file Tournament.hpp
 *
 * Este arquivo contem a definição da classe abstrata Tournament, que define
 * a implementação de um campeonato (múltiplos jogadores competindo entre si).
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 01/2012 */

#ifndef GAMES_TOURNAMENT_HPP
#define GAMES_TOURNAMENT_HPP

#include <set>

#include "Statistics.hpp"

namespace Games {
namespace {
/** @cond DOXYGEN_SHOULD_SKIP_THIS */
// Para o código ficar mais legível
template <class match_t, class player_t>
const player_t *get_winner(const match_t *match) {
	for(const player_t *player : match->get_players())
		if(match->get_result(player) == VICTORY)
			return player;
	return nullptr;
}

// Para o código ficar mais legível
template <class player_t>
void rotate(std::deque <player_t *> &players) {
	players.push_back(players.front());
	players.pop_front();
}
/** @endcond DOXYGEN_SHOULD_SKIP_THIS */

} //  namespace
/** Executa o mínimo número de partidas neessárias para definir o melhor jogador
 * em, no máximo, <i>num_matches</i> partidas. Por exemplo, supondo uma
 * disputa do "melhor de 3 partidas", se um jogador <i>A</i> vencer as duas
 * primeiras partidas, a terceira não será necessária.
 *
 * @param num_matches número máximo de partidas.
 * @param players os jogadores envolvidos na partida */
template <class match_t, class player_t>
std::deque<match_t *> best_out_of(unsigned int num_matches, const std::deque<player_t *> &players) {
	if(num_matches < 1)
		throw std::invalid_argument("Must have at least one match per dispute.");
	if(players.size() < 2)
		throw std::invalid_argument("Not enough players for dispute.");

	std::deque<match_t *> matches;

	unsigned int best_player_wins = 0;
	const unsigned int necessary_wins = num_matches / 2 + 1;

	std::map<const player_t *, unsigned int> victories;
	for(player_t *player : players) victories[player] = 0;

	std::deque<player_t *> dispute_players(players);

	do {
		match_t *match = new match_t(dispute_players);
		matches.push_back(match);

		match->play();

		const player_t *winner = get_winner<match_t, player_t>(match);

		if(winner) {
			++(victories[winner]);
			best_player_wins = std::max(best_player_wins, victories[winner]);
		}

		rotate(dispute_players);
	} while(best_player_wins < necessary_wins && matches.size() < num_matches);

	return matches;
}

/** Classe abstrata para implementação de um campeonato. */
template <class match_t, class player_t>
class Tournament {
public:
	/** Construtor.
	 *
	 * @param p os jogadores do campeonato. */
	Tournament(const std::deque<player_t *> &p)
	: players(p.begin(), p.end()) {
		if(players.size() < 2)
			throw std::invalid_argument("Not enough players for tournament.");
	}

	/** Destrutor. */
	virtual ~Tournament() { clear_rounds();	}

	/** Converte a rodada em string. */
	friend std::ostream &operator <<(std::ostream &os,
									 const Tournament &tournament) {
		os << IIA::Utils::String::join_ptrs(tournament.players);

		for(std::deque<std::deque<match_t *> > round : tournament.rounds)
			for(std::deque<match_t *> dispute : round)
				os << "\n" << IIA::Utils::String::join_ptrs(dispute, "\n");

		return os;
	}

	/** Implementa o campeonato, organizando as rodadas entre os jogadores
	 * inscritos. */
	virtual void run(unsigned int num_matches = 1 /**< [in] número mínimo de partidas a realizar */) {
		if(num_matches == 0)
			throw std::invalid_argument("Invalid number of matches per dispute in Tournament.");

		clear_rounds();

		std::deque<player_t *> tournament_players;
		std::deque<std::deque<match_t *> > *round;

		setup_players(tournament_players);
		do {
			round = push_back_new_round(tournament_players, num_matches);

			play(round);

			next(round, tournament_players);
		} while(!over(round, tournament_players));
	}

protected:
	/** Define os jogadores que iniciarão o campeonato. */
	virtual void setup_players(std::deque<player_t *> &tournament_players) {
		tournament_players.assign(players.begin(), players.end());
	}

	/** Acrescenta uma nova rodada ao final de rounds (definindo todas as
	 * disputas), e retorna a referência para esta. */
	virtual std::deque<std::deque<match_t *> > *push_back_new_round(
		std::deque<player_t *> &tournament_players, /**< [in] jogadores envolvidos */
		unsigned int num_matches 					/**< [in] número máximo de partidas */
		) = 0;

	/** Executa todas as partidas da rodada. */
	virtual void play(std::deque<std::deque<match_t *> > *round) {
		for(std::deque<match_t *> dispute : *round)
			for(match_t *match : dispute)
				match->play();
	}

	/** Atualiza o conjunto de jogadores em função da rodada disputada. */
	virtual void next(
		std::deque<std::deque<match_t *> > *last_round, /**< [in] última rodada disputada */
		std::deque<player_t *> &tournament_players 		/**< [in] jogadores envolvidos */
		) = 0;

	/** Indica se o campeonato terminou.*/
	virtual bool over(
		const std::deque<std::deque<match_t *> > *last_round, /**< [in] última rodada disputada */
		const std::deque<player_t *> &tournament_players 	  /**< [in] jogadores que disputarão a próxima rodada */
		) = 0;

private:
	void clear_rounds() {
		for(std::deque<std::deque<match_t *> > round : rounds) {
			for(std::deque<match_t *> dispute : round)
				IIA::Utils::empty(dispute);
			round.clear();
		}
		rounds.clear();
	}
	
public:
	// Attributes
	/** Jogadores participantes do campeonato. */
	std::set<player_t *> players;

	/** Armazena a sequencia de rodadas realizadas no torneio. Uma rodada é
	 * composta por um conjunto de disputas, que são um conjunto de partidas
	 * entre jogadores. */
	std::deque<std::deque<std::deque<match_t *> > >rounds;
};
} // namespace Games
#endif /* GAMES_TOURNAMENT_HPP */
