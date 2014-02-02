/** @file PubRandomPlayer.h
 *
 * Implementação do jogador RandomPlayer para Pub.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#ifndef GAMES_PUB_RANDOMPLAYER_H
#define GAMES_PUB_RANDOMPLAYER_H

#include "PubMatch.h"

namespace Games {
namespace Pub {
/** Classe de jogador para Pub. Escolhe as jogadas aleatóriamente. */
class PubRandomPlayer : public PubPlayer {
public:
	/** Construtor. */
	PubRandomPlayer(Mark m, std::string id = "RandomPlayer") 
	: PubPlayer(m, id) {
		IIA::Utils::Random::set_seed_from_system_time();
	}

protected:
	// overload
	virtual void choose_play(const PubAction *last_action, int &first, int &second) {
		PubState game;
		
		first = IIA::Utils::Random::get_random_int(game.col_size() - 1);
		second = IIA::Utils::Random::get_random_int(game.col_size() - 1);
	}
};

/** Classe de jogador para Pub. Escolhe as jogadas aleatóriamente. */
class SlowPubRandomPlayer : public PubRandomPlayer {
public:
	/** Construtor. */
	SlowPubRandomPlayer(Mark m, std::string id = "SlowPubRandomPlayer") 
	: PubRandomPlayer(m, id) {}

protected:
	// overload
	void choose_play(const PubAction *last_action, int &first, int &second) {
		for(double i = 0; i < MAX_TIME_COST_IN_NANOSECONDS; ++i);

		PubRandomPlayer::choose_play(last_action, first, second);
	}
};
} // namespace Pub
} // namespace Games

#endif // GAMES_PUB_RANDOMPLAYER_H
