/** @file TicTacToe_SimplePlayer.h
 *
 * Descreve/define o jogador SimplePlayer para o \link TicTacToe Jogo-da-Velha\endlink.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 07/2012 */

#ifndef GAMES_TICTACTOE_DUMMYPLAYER_H
#define GAMES_TICTACTOE_DUMMYPLAYER_H

#include "TicTacToe_Player.hpp"

namespace Games {
/** Define o escopo do \link TicTacToe Jogo-da-Velha\endlink. */
namespace TicTacToe {
/** Enumera os possíveis estados da casa. */
enum Mark {
	EMPTY, 	/**< A casa está vazia. */
	NOUGHT, /**< A casa é 'O'. */
	CROSS	/**< A casa é 'X'. */
};

/** Converte as marcas do jogo em string. */
static std::ostream &operator <<(std::ostream &os, Mark mark) {
	switch(mark) {
	case EMPTY:  os << " "; break;
	case NOUGHT: os << "O"; break;
	case CROSS:  os << "X"; break;
	default: break;
	}
	return os;
}

/** Retorna a marca oposta a dada. */
static Mark opponent_mark(const Mark &mark) {
	switch(mark) {
	case NOUGHT: return CROSS;
	case CROSS:  return NOUGHT;
	default: throw std::invalid_argument("Invalid mark.");
	}
}

/** Define um estado do \link TicTacToe Jogo-da-Velha\endlink. O estado é a representação do tabuleiro,
 * uma matriz de três linhas por três colunas em que cada célula pode assumir os
 * um valor estabelecido por Mark. */
class State : public IIA::State<State>, public Games::Grids::Grid2D<Mark> {
public:
	/** Construtor de um tabuleiro vazio. */
	State();
	/** Construtor de um tabuleiro como cópia do dado. */
	State(const State &state);

	/** Indica se a instância é menor que o estado dado. */
	bool operator< (const State &that) const;
	/** Indica se a instância é igual ao estado dado. */
	bool operator== (const State &that) const;
	/** Define a instância como cópia do estado dado. */
	State &operator= (const State &that);

	/** Converte o estado em string. */
	friend std::ostream &operator <<(std::ostream &os, const State &state) {
		os << static_cast<Games::Grids::Grid2D<Mark> >(state);
		return os;
	}
};

/** Define a ação de marcar uma célula no \link TicTacToe Jogo-da-Velha\endlink. */
class Action : public IIA::Action<State> {
public:
	/** Construtor. Indica onde marcar e a que custo.
	 *
	 * @param coord a coordenada a marcar.
	 * @param mark a marca a ser feita.
	 * @param cost o custo associado. */
	Action(const Games::Grids::Coord2D &coord, Mark mark, double cost);

	/** Retorna a referência para uma cópia desta instância. */
	Action *clone() const;

	/** Marca a coordenada armazenada no estado dado. */
	void execute(State &game) const;
	
	/** Retorna uma string que descreve a ação. */
	std::string to_string() const;

	// Attributes
	/** A coordenada onde marcar. */
	Games::Grids::Coord2D coord;
	/** A marca a fazer. */
	Mark mark;
};

/** Define um jogador para o \link TicTacToe Jogo-da-Velha\endlink */
class Player : public Games::Player<State> {
public:
	/** Construtor. */
	Player(Mark mark, std::string name);

	/** Retorna a percepção do jogador. */
	virtual State percept() const;

	/** Decide a ação a realizar dado o estado. */
	IIA::Action<State> *decide_action(const State &state);

	// Attributes
	/** A marca deste jogador. */
	Mark mark;

protected:
	/** Define a jogada em função do estado dado.
	 *
	 * @param state [in] o estado do jogo.
	 * @return Games::Grids::Coord2D a coordenada onde marcar. */
	virtual Games::Grids::Coord2D choose_play(const State &state) = 0;
	/** Verifica se há possibilidade de ganhar em uma linha.
	 *
	 * @param game o estado atual do jogo.
	 * @param mark o jogador a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário. */
	Games::Grids::Coord2D can_win_in_row(const State &game, const Mark mark) const;

	/** Verifica se há possibilidade de ganhar na coluna dada.
	 *
	 * @param game o estado atual do jogo.
	 * @param mark símbolo a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário. */
	Games::Grids::Coord2D can_win_in_col(const State &game, const Mark mark) const;

	/** Verifica se há possibilidade de ganhar na diagonal que vai do canto
	 * superior direito ao inferior esquerdo.
	 *
	 * @param game estado atual do jogo.
	 * @param mark símbolo a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário. */
	Games::Grids::Coord2D can_win_in_d1(const State &game, const Mark mark) const;

	/** Verifica se há possibilidade de ganhar na diagonal que vai do
	 * canto inferior esquerdo ao superior direito.
	 *
	 * @param game estado atual do jogo.
	 * @param mark símbolo a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário. */
	Games::Grids::Coord2D can_win_in_d2(const State &game, const Mark mark) const;

	/** Verifica se há possibilidade do jogador definido pela marca dada vencer
	 * a partida representada pelo estado na próxima jogada.
	 *
	 * @param game estado atual do jogo.
	 * @param mark símbolo a ser verificado.
	 *
	 * @return Games::Grids::Coord2D coordenada em que há condição de vitória,
	 * inválida caso contrário.
	 *
	 * @see Games::Grids::Coord2D can_win_in_row(const State &, const Mark)
	 * @see Games::Grids::Coord2D can_win_in_col(const State &, const Mark)
	 * @see Games::Grids::Coord2D can_win_in_d1(const State &, const Mark)
	 * @see Games::Grids::Coord2D can_win_in_d2(const State &, const Mark) */
	Games::Grids::Coord2D can_win(const State &game, const Mark mark);
};

/** Jogador DummyPlayer, que escolhe a primeira casa vazia disponível. */
class DummyPlayer : public Player {
public:
	/** Construtor.
	 *
	 * @param m a marca do jogador.
	 * @param id identifica o jogador. */
	DummyPlayer(Mark m, std::string id = "DummyPlayer");

protected:
	/** Escolhe a jogada a ser feita. */
	Games::Grids::Coord2D choose_play(const State &game);
};

/** Jogador SimplePlayer, que tenta ganhar antes de tentar não perder. */
class SimplePlayer : public DummyPlayer {
public:
	/** Construtor.
	 *
	 * @param m a marca do jogador.
	 * @param id identifica o jogador. */
	SimplePlayer(Mark m, std::string id = "SimplePlayer");

protected:
	/** Escolhe a jogada a ser feita. */
	Games::Grids::Coord2D choose_play(const State &game);
};

/** Jogador SlowSimplePlayer, versão lenta do SimplePlayer. */
class SlowSimplePlayer : public SimplePlayer {
public:
	/** Construtor.
	 *
	 * @param m a marca do jogador.
	 * @param id identifica o jogador. */
	SlowSimplePlayer(Mark m, std::string id = "SlowSimplePlayer");

protected:
	/** Escolhe a jogada a ser feita. */
	Games::Grids::Coord2D choose_play(const State &game);
};

/** Define uma partida do \link TicTacToe Jogo-da-Velha\endlink. As regras são
 * simples: dois jogadores escolhem uma marcação cada um, geralmente um círculo
 * (O) e um xis (X), e se alternam para marcar um espao vazio no tabuleiro
 * (3x3). Vence o primeiro a conseguir três círculos ou três xis em linha, quer
 * horizontal, vertical ou diagonal. Não havendo possibilidade de vitória,
 * deve-se impedir o adversário de ganhar na próxima jogada. */
class Match : public Games::Match<Player, Action, State> {
public:
	/** Construtor. */
	Match(const std::deque<Player *> &players);
	
	/** Construtor. */
	Match(const std::set<Player *> &players);

	/** Retorna o resultado da atual sequência de ações para o jogador dado.
	 *
	 * @see Result get_result(const State &, const Player *) */
	Result get_result(const Player *player) const;

protected:
	/** Verifica se o estado dado como argumento possui uma linha vitoriosa para
	 * o jogador especificado. A linha é vitoriosa se todas as casas estiverem
	 * marcadas com o mesmo símbolo.
	 *
	 * @param game jogo a ser verificado
	 * @param mark símbolo a ser verificado.
	 *
	 * @return bool verdadeiro, se há uma linha vitoriosa, falso caso contrário. */
	bool has_winning_row(const State &game, const Mark mark) const;

	/** Verifica se o estado dado como argumento possui uma coluna vitoriosa
	 * para o jogador especificado. A coluna é vitoriosa se todas as casas
	 * estiverem marcadas com o mesmo símbolo.
	 *
	 * @param game jogo a ser verificado
	 * @param mark símbolo a ser verificado.
	 *
	 * @return bool verdadeiro, se há uma coluna vitoriosa, falso caso contrário. */
	bool has_winning_column(const State &game, const Mark mark) const;

	/** Verifica se o estado dado como argumento possui uma diagonal vitoriosa
	 * para o jogador especificado. A diagonal é vitoriosa se todas as casas
	 * estiverem marcadas com o mesmo símbolo.
	 *
	 * @param game jogo a ser verificado
	 * @param mark símbolo a ser verificado.
	 *
	 * @return bool verdadeiro, se há uma diagonal vitoriosa, falso caso contrário. */
	bool has_winning_diagonal(const State &game, const Mark mark) const;

	/** Retorna o resultado da atual sequência de ações para o jogador dado.
	 *
	 * @see Result get_result(const State &, const Player *) */
	Result get_result(const State &game, const Mark mark) const;

	/** Chamada para preparativos necessários (se houver) antes do início de uma
	 * partida .  */
	void setup(const std::deque<Player *> &players);

	/** Indica se a partida dada terminou. */
	bool over(const State &game);

	/** Retorna a referência para uma nova ação, que é inválida para o
	 * jogador e estado dados. */
	Action *invalid_action(const Player *player, const State &game) const;

	/** Verifica se a jogada, feita pelo jogador, é válida para o estado atual. */
	bool allowed(const Move *move, const State &state) const;
};
} // namespace TicTacToe
} // namespace Games

#endif // GAMES_TICTACTOE_H
