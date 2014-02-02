/** @file TicTacToeSimplePlayer.h
 *
 * Descreve/define o jogador SimplePlayer para o \link Games::TicTacToe Jogo-da-Velha\endlink.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_TICTACTOE_SIMPLEPLAYER_H
#define GAMES_TICTACTOE_SIMPLEPLAYER_H

#include "TicTacToeDummyPlayer.h"

namespace Games {
namespace TicTacToe {
/** Jogador SimplePlayer, que tenta ganhar antes de tentar não perder. */
class SimplePlayer : public DummyPlayer {
public:
	/** Construtor. */
	SimplePlayer(Mark mark, /**< marca do jogador */
			     std::string id = "SimplePlayer" /**< identifica o jogador */
				 )
	: DummyPlayer(mark, id) {}

protected:
	/** Escolhe a jogada a ser feita. */
	Games::Grids::Coord2D choose_play(const TicTacToeState &game) {
		Games::Grids::Coord2D coord(1, 1);
		// jogar no meio, onde há "mais possibilidades"...
		if(game[coord] == EMPTY) return coord;

		/** Verifica se há chance de ganhar, depois se há de perder. */
		coord = can_win(game, mark);
		if(game.valid(coord)) return coord;
		// seria o estado de maior utilidade.

		coord = can_win(game, opponent_mark(mark));
		if(game.valid(coord)) return coord;
		//seria o estado de pior utilidade

		/** Se não houver, tenta uma jogada aleatória. */
		/** @todo Implementar uma busca minimamente decente...*/
		/*try {
			coord = RandomPlayer::getValidRandomCoordinate(state);
			return coord;
		} catch (PlayerException *e) {
			// burro!
			delete e;
		}*/

		/** Se não conseguir, joga a primeira casa vazia que encontrar. */
		return DummyPlayer::choose_play(game);
	}
};

/** Jogador SlowSimplePlayer, versão lenta do SimplePlayer. */
class SlowSimplePlayer : public SimplePlayer {
public:
	/** Construtor. */
	SlowSimplePlayer(Mark mark, /**< marca do jogador */
					 std::string id = "SlowSimplePlayer" /**< identifica o jogador */
					)
	: SimplePlayer(mark, id) {}

protected:
	/** Escolhe a jogada a ser feita. */
	Games::Grids::Coord2D choose_play(const TicTacToeState &game){
		/** @todo função sleep ? */
		for(int i = 1; i < 10000; ++i);
		return SimplePlayer::choose_play(game);
	}
};
} // namespace TicTacToe
} // namespace Games

#endif // GAMES_TICTACTOE_SIMPLEPLAYER_H
