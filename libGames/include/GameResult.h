/** @file GameResult.h
 *
 * Este arquivo contem a definição do resultado para um confronto entre 
 * adversários.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date Janeiro, 2012 */

#ifndef GAME_RESULT_H
#define GAME_RESULT_H

#include <ostream>

namespace Games {
/** Enumera os possíveis resultados de um confronto. */
enum GameResult {
	VICTORY,	/**< O confronto foi vencido. */
	DRAW,   		/**< O confronto empatou. */
	DEFEAT, 	/**< O confronto foi perdido. */
	UNKNOWN 	/**< Desconhecido. */
};

/** Converte um MatchResult em string */
static std::ostream &operator <<(std::ostream &os, const GameResult &result) {
	switch(result) {
	case VICTORY: os << "VICTORY";	break;
	case DRAW:    os << "DRAW"; break;
	case DEFEAT:  os << "DEFEAT"; break;
	case UNKNOWN: os << "UNKNOWN"; break;
	default: break;
	}
	return os;
}
} // namespace Games

#endif // GAME_RESULT_H
