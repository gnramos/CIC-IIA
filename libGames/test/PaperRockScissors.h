/** @file PaperRockScissors.h
 * 
 * Implementa o jogo Pedra-Tesoura-Papel para testes.
 * 
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date 05/2012 */

#ifndef GAMES_PAPER_ROCK_SCISSORS_H
#define GAMES_PAPER_ROCK_SCISSORS_H

#include "State.hpp"
#include "Action.hpp"

#include "Player.hpp"
#include "Match.hpp"
 
namespace Games {
/** Define o escopo do jogo. */
namespace PaperRockScissors {

/** Enumera os possíveis estados. */
enum Mark {
	PAPER,	/**< Papel. */
	ROCK,	/**< Pedra. */
	SCISSOR,/**< Tesoura. */
	INVALID /**< Desconhecido. */
};

namespace {
Mark defeated_by(Mark mark) {
	switch(mark) {
		case PAPER: return SCISSOR;
		case ROCK: return PAPER;
		case SCISSOR: return ROCK;
		default:
			throw std::invalid_argument("Cannot find mark to defeat " + IIA::Utils::String::to_string(mark) + ".");
	}
}

Mark beats(Mark mark) {
	switch(mark) {
		case PAPER: return ROCK;
		case ROCK: return SCISSOR;
		case SCISSOR: return PAPER;
		default:
			throw std::invalid_argument("Cannot find mark to beat " + IIA::Utils::String::to_string(mark) + ".");
	}
}

/** Converte um MatchResult em string */
std::ostream &operator <<(std::ostream &os, const Mark &mark) {
	switch(mark) {
	case PAPER:   os << "PAPER";	break;
	case ROCK:    os << "ROCK"; break;
	case SCISSOR: os << "SCISSOR"; break;
	case INVALID: os << "INVALID"; break;
	default: break;
	}
	return os;
}
} //unnamed namespace

/** Define um estado do jogo, que representa as opções de cada jogador. */
class PaperRockScissorsState : public IIA::State<PaperRockScissorsState> {
public:
	/** Construtor de um tabuleiro vazio. */
	PaperRockScissorsState() {}
	
	/** Construtor de um tabuleiro como cópia do dado. */
	PaperRockScissorsState(const PaperRockScissorsState &state) : marks(state.marks) {}

	/** Indica se a instância é menor que o estado dado. */
	bool operator< (const PaperRockScissorsState &that) const {return false;}
	/** Indica se a instância é igual ao estado dado. */
	bool operator== (const PaperRockScissorsState &that) const {
		return this->marks == that.marks;
	}
	/** Define a instância como cópia do estado dado. */
	PaperRockScissorsState &operator= (const PaperRockScissorsState &that){
		if(this != &that) this->marks = that.marks;
		return *this;
	}
	
	/** Converte em string. */
	friend std::ostream &operator <<(std::ostream &os, const PaperRockScissorsState &state) {
		os << IIA::Utils::String::join(state.marks);
		return os;
	}

	std::deque<Mark> marks;
};

/** Define a ação. */
class PaperRockScissorsAction : public IIA::Action<PaperRockScissorsState> {
public:
	/** Construtor. Indica onde marcar e a que custo.
	 *
	 * @param m a marca a ser feita.
	 * @param cost o custo associado. */
	PaperRockScissorsAction(Mark m, double cost) : IIA::Action<PaperRockScissorsState>(cost), mark(m) {}

	/** Retorna a referência para uma cópia desta instância. */
	PaperRockScissorsAction *clone() const {return new PaperRockScissorsAction(mark, cost);}

	// No arquivo cpp.
	void execute(PaperRockScissorsState &state) const { state.marks.push_back(mark); }
	
	std::string to_string() const {
		return "Marcar " + IIA::Utils::String::to_string(mark);
	}

	/** A marca a fazer. */
	Mark mark;
};

class PaperRockScissorsPlayer : public Games::Player<PaperRockScissorsState> {
public:
	PaperRockScissorsPlayer(std::string name = "PaperRockScissorsPlayer") 
	: Games::Player<PaperRockScissorsState>(name) {}
};

/** Define um jogador que só escolhe PAPER.*/
class PaperPlayer : public PaperRockScissorsPlayer {
public:
	/** Construtor. */
	PaperPlayer(std::string name = "PaperPlayer") : PaperRockScissorsPlayer(name) {}

	/** Retorna a ação. */
	IIA::Action<PaperRockScissorsState> *decide_action(const PaperRockScissorsState &state) {
		return new PaperRockScissorsAction(PAPER, 1);
	}
};

/** Define um jogador que só escolhe ROCK.*/
class RockPlayer : public PaperRockScissorsPlayer {
public:
	/** Construtor. */
	RockPlayer(std::string name = "RockPlayer") : PaperRockScissorsPlayer(name) {}

	/** Retorna a ação. */
	IIA::Action<PaperRockScissorsState> *decide_action(const PaperRockScissorsState &state) {
		return new PaperRockScissorsAction(ROCK, 1);
	}
};

/** Define um jogador que só escolhe ROCK.*/
class ScissorsPlayer : public PaperRockScissorsPlayer {
public:
	/** Construtor. */
	ScissorsPlayer(std::string name = "ScissorsPlayer") : PaperRockScissorsPlayer(name) {}

	/** Retorna a ação. */
	IIA::Action<PaperRockScissorsState> *decide_action(const PaperRockScissorsState &state) {
		return new PaperRockScissorsAction(SCISSOR, 1);
	}
};

/** Define um jogador aleatório. */
class RandomPlayer : public PaperRockScissorsPlayer {
public:
	/** Construtor. */
	RandomPlayer(std::string name = "PaperRockScissorRandomPlayer") : PaperRockScissorsPlayer(name) {
		IIA::Utils::Random::set_seed_from_system_time();
	}

	/** Decide a ação a realizar dado o estado. */
	IIA::Action<PaperRockScissorsState> *decide_action(const PaperRockScissorsState &state) {
		switch(IIA::Utils::Random::get_random_int(100)%3) {
		case 0: return new PaperRockScissorsAction(PAPER, 1);
		case 1: return new PaperRockScissorsAction(ROCK, 1);
		default: return new PaperRockScissorsAction(SCISSOR, 1);
		}
	}
};

/** Define uma partida do jogo. */
class PaperRockScissorsMatch : public Games::Match<PaperRockScissorsPlayer, PaperRockScissorsAction, PaperRockScissorsState> {
public:
	/** Construtor. */
	PaperRockScissorsMatch(const std::deque<PaperRockScissorsPlayer *> &players) : Games::Match<PaperRockScissorsPlayer, PaperRockScissorsAction, PaperRockScissorsState>(players) {}
	/** Construtor. */
	PaperRockScissorsMatch(const std::set<PaperRockScissorsPlayer *> &players) : Games::Match<PaperRockScissorsPlayer, PaperRockScissorsAction, PaperRockScissorsState>(players) {}

	/** Retorna o resultado da atual sequência de ações para o jogador dado.
	 *
	 * @see GameResult get_result(const PaperRockScissorsState &, const PaperRockScissorsPlayer *) */
	GameResult get_result(const PaperRockScissorsPlayer *player) const {
		if(moves.size() < 1 || (moves.size() % players.size()) > 0) return UNKNOWN;
		
		std::map<Mark, int> marks;
		marks[PAPER] = 0, marks[ROCK] = 0, marks[SCISSOR] = 0, marks[INVALID] = 0;
		
		Mark player_mark;
		for(auto it = moves.rbegin(); it < moves.rbegin() + players.size(); ++it) {
			marks[(*it)->action->mark]++;
			if((*it)->player == player) player_mark = (*it)->action->mark;
		}
		
		if(marks[INVALID] > 0) return UNKNOWN;
		
		if(marks[defeated_by(player_mark)] > 0) {
			if(marks[beats(player_mark)] > 0) return DRAW;
			else return DEFEAT;
		} else  {
			if(marks[beats(player_mark)] > 0) return VICTORY;
			else return DRAW;
		}
	}

protected:
	/** Chamada para preparativos necessários (se houver) antes do início de uma
	 * partida .  */
	void setup(const std::deque<PaperRockScissorsPlayer *> &players) {
		if(players.size() < 2)
			throw std::invalid_argument("Cannot setup PaperRockScissorsMatch with " + IIA::Utils::String::to_string(players.size()) + " player(s).");
			
		attempts = 0;
	}

	/** Indica se a partida dada terminou. */
	bool over(const PaperRockScissorsState &state) {
		++attempts;
		if(attempts >= 10*(players.size())) return true;
		GameResult result = get_result(*(players.begin()));
		return (result == VICTORY || result == DEFEAT);
	}

	/** Retorna a referência para uma nova ação, que é inválida para o
	 * jogador e estado dados. */
	PaperRockScissorsAction *invalid_action(const PaperRockScissorsPlayer *player, const PaperRockScissorsState &game) const {
		return new PaperRockScissorsAction(INVALID, 0);
	}

	/** Verifica se a jogada, feita pelo jogador, é válida para o estado atual. */
	bool allowed(const Move *move, const PaperRockScissorsState &state) const {
		if(!move || !move->action) return false;
		return (move->action->mark != INVALID);
	}
private:
	unsigned int attempts;
};
} // namespace PaperRockScissors
} // namespace Games

#endif /* GAMES_PAPER_ROCK_SCISSORS_H */
