/** @file PubState.h
 *
 * Descrição de um estado do jogo Pub.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_PUB_STATE_H
#define GAMES_PUB_STATE_H

#include <ostream>
#include <stdexcept>

#include "State.hpp"
#include "Game.hpp"

namespace Games {
/** Define o escopo do jogo Pub. Por sorteio decide-se quem iniciará a partida e
 * posteriormente os jogadores se alternam nas jogadas.
 *
 * Objetivo: enfileirar 4 de suas bolas na sequência horizontal, vertical ou
 * diagonal.
 *
 * Movimentação: A cada vez o jogador pega 2 de suas bolas deixando-as cair
 * dentro de qualquer buraco da torre. Os jogadores podem colocar as 2 bolas no
 * mesmo buraco ou em buracos diferentes. Em cada buraco cabem 8 bolas. Quando a
 * torre estiver completa com as 40 bolas, é hora de contar os pontos.
 *
 * Vencedor: Cada jogador conta quantas sequências de 4 bolas nas direções foram
 * feitas. Quem tiver feito mais sequências ganha o jogo.
 *
 * Observação: O jogador pode e deve observar a jogada do adversário. */
namespace Pub {

/** Enumera os possíveis estados da casa. */
enum Mark {
	WHITE,	/**< Bola branca. */
	BLACK,	/**< Bola preta. */
	EMPTY	/**< Vazio. */
};

/** Converte as marcas do jogo em string. */
inline static std::ostream &operator <<(std::ostream &os, Mark mark) {
	switch(mark) {
	case WHITE: os << "O"; break;
	case BLACK: os << "X"; break;
	default: os << " "; break;
	}
	return os;
}

/** Retorna a marca oposta a dada. */
inline static Mark opponent_mark(const Mark &mark) {
	switch(mark) {
	case WHITE: return BLACK;
	case BLACK: return WHITE;
	default: throw std::invalid_argument("Invalid mark.");
	}
}

class PubAction;
/** Define um estado do jogo Pub. O estado é a representação do tabuleiro, uma
 * matriz de oito linhas por cinco colunas em que cada célula pode assumir os
 * um valor estabelecido por Mark. */
class PubState : public IIA::State<PubState>, public Games::Grids::Grid2D<Mark> {
public:
	/** Construtor de um tabuleiro vazio. */
	PubState();
	/** Construtor de um tabuleiro como cópia do dado. */
	PubState(const PubState &state);
	/** Destrutor. */
	~PubState();

	/** Indica se a instância é menor que o estado dado. */
	bool operator< (const PubState &that) const;
	/** Indica se a instância é igual ao estado dado. */
	bool operator== (const PubState &that) const;
	/** Define a instância como cópia do estado dado. */
	PubState &operator= (const PubState &that);

	/** Converte a grade em string. */
	friend std::ostream &operator <<(std::ostream &os, const PubState &state) {
		os << static_cast<Games::Grids::Grid2D<Mark> >(state);
		return os;
	}

	/** Indica a última ação executada no estado. */
	PubAction *last_action;
};
} // namespace Pub
} // namespace Games

#endif // GAMES_PUB_STATE_H
