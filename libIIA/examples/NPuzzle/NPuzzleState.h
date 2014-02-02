/** @file NPuzzleState.h
 *
 * Descreve o estado para o N-Puzzzle.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 * @date  10/2011 */

#ifndef IIA_EXAMPLES_NPUZZLE_STATE_H
#define IIA_EXAMPLES_NPUZZLE_STATE_H

#include <ostream>
#include <stdexcept>
#include <vector>

#include "State.hpp"

namespace IIA {
namespace Examples {
/** Define o escopo do problema N-Puzzle. */
namespace NPuzzle {
/** Define uma coordenada do tabuleiro do N-Puzzle. */
class Coord {
public:
	/** Construtor. Instancia a coordenada com os valores dados. */
	Coord(int r = 0, /**< coordenada de linha */
	      int c = 0  /**< coordenada de coluna */ 
	     ) : row(r), col(c) {}

	// Attributes
	int row; /**< A linha da coordenada. */
	int col; /**< A coluna da coordenada. */
	
	/** Converte em string. */
	friend std::ostream &operator <<(std::ostream &os, const Coord &coord) {
		os << "(" << coord.row << "," << coord.col << ")";
		return os;
	}
};

/** Define um estado para o problema do N-Puzzle. O estado é a representação do
 * tabuleiro, uma matriz de @em N linhas por @em N colunas em que cada célula
 * pode assumir um valor em [0, @em N - 1], representando a peça que está na casa
 * (0 é o "vazio"). */
class NPuzzleState : public IIA::State<NPuzzleState> {
public:
	/** Construtor de um tabuleiro vazio. */
	NPuzzleState(unsigned int size = 3) {
		if(size < 1)
			throw std::invalid_argument("N-Puzzle must have N > 1.");

		board.resize(size, std::vector<unsigned int>(size, 0));
		for(unsigned int i = 0; i < board.size(); ++i) {
			for(unsigned int j = 0; j < board[i].size(); ++j) {
				board[i][j] = i * size + j;
			}
		}
	}

	/** Indica se a coordenada dada é válida, i.e. dentro dos limites de
	 * tamanho do tabuleiro.
	 *
	 * @param coord a coordenada. */
	bool is_valid(const Coord &coord) const {
		if(0 > coord.row || coord.row >= board.size()) return false;
		if(0 > coord.col || coord.col >= board.size()) return false;
		return true;
	}

	/** Retorna uma coordenada inválida, i.e. fora dos limites de tamanho
	 * do tabuleiro. */
	Coord invalid_coords() const {
		return Coord(-1, -1);
	}

	/** Converte o tabuleiro em uma string. */
	//std::string to_string() const;
	
	friend std::ostream &operator <<(std::ostream &os, const NPuzzleState &state) {
		for(std::vector<unsigned int> row :state.board)
			os << "\n" << Utils::String::join(row);
		return os;
	}

	/** Acessa a marca da coordenada dada. */
	unsigned int &operator[](const Coord &coord) {
		return board[coord.row][coord.col];
	}

	/** Acessa a marca da coordenada dada. */
	const unsigned int operator[](const Coord &coord) const {
		return board[coord.row][coord.col];
	}

	/** Indica se a instância é igual ao objeto dado como argumento. */
	bool operator==(const NPuzzleState &that) const {
		if(this == &that) return true;
		return this->board == that.board;
	}

	/** Indica se a instância é menor que objeto dado como argumento. */
	bool operator<(const NPuzzleState &that) const {
		if(this == &that) return false;
		return this->board < that.board;
	}

	/** Atribui à instância o objeto dado como argumento. */
	NPuzzleState &operator= (const NPuzzleState &that) {
		if(this != &that) {
			this->board.assign(that.board.begin(), that.board.end());
		}

		return *this;
	}

	/** Inica o tamanho do estado. */
	unsigned int size() const {return board.size();}

	/** Busca a coordenada do número na instância. */
	Coord find(unsigned int number) const {
		if(number >= board.size()*board.size())
			throw std::out_of_range("Number out of range.");

		Coord coord;
		for(coord.row = 0; coord.row < board.size(); ++coord.row)
			for(coord.col = 0; coord.col < board.size(); ++coord.col)
				if(board[coord.row][coord.col] == number)
					return coord;

		/** @todo exceção decente em NPuzzle::NPuzzleState::size */
		throw std::logic_error("Unable to find number in board");
	}

private:
	/** Armazena o tabuleiro. */
	std::vector< std::vector<unsigned int> > board;
};
} // namespace NPuzzle
} // namespace Examples
} // namespace IIA

#endif // IIA_EXAMPLES_NPUZZLE_STATE_H
