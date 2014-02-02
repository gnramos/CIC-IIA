/** @file PubPlayer.h
 *
 * Declaração de um jogador do jogo Pub.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_PUB_PLAYER_H
#define GAMES_PUB_PLAYER_H

#include <iostream>

#include "PubAction.h"

namespace Games {
namespace Pub {
/** Define um jogador para o Pub. */
class PubPlayer : public Games::Player<PubState> {
public:
	/** Construtor. */
	PubPlayer(Mark m, /**< a marca do jogador */
			  std::string name /**< nnome do jogador */
			 )
		: Games::Player<PubState>(name), mark(m) {}

	/** Decide a ação a realizar dado o estado. */
	IIA::Action<PubState> *decide_action(const PubState &state) {
		/** Marca o tempo (em nanossegundos) para decisão da jogada e o define
		 * como custo da ação. */
		timespec start_time, end_time;
		int first, second;

		IIA::Utils::Time::get_cpu_time(start_time);
		choose_play(state.last_action, first, second);
		IIA::Utils::Time::get_cpu_time(end_time);

		timespec diff = IIA::Utils::Time::time_diff(start_time, end_time);
		double cost_in_ns = IIA::Utils::Time::to_nano(diff);

		return new PubAction(first, second, mark, cost_in_ns);
	}

	
	/** Indica ao jogador que ele vai participar de uma nova partida. */
	virtual void start_new_match() {}

	// Attributes
	/** A marca deste jogador. */
	Mark mark;

protected:
	/** Define a jogada. */
	virtual void choose_play(const PubAction *last_action, /**< [in] a última ação executada */
							 int &first, /**< [out] a coordenada da coluna onde se deseja jogar primeiro */
							 int &second /**< [out] a coordenada da coluna onde se deseja jogar segundo */
							) = 0;
};
} // namespace Pub
} // namespace Games

#endif // GAMES_PUB_PLAYER_H
