/** @file libIIA.h
 *
 * Definição de algoritmos/classes/funções relacionados à disciplina <b>Introdução a
 * Inteligência Artificial</b>.
 *
 * @author Guilherme Ramos
 * @date October, 2012 */

#ifndef IIA_LIB_H
#define IIA_LIB_H

#include "Action.hpp"
#include "Agents/Agents.h"
#include "Problem.hpp"
#include "Search/Informed/InformedSearch.h"
#include "Search//Local/LocalSearch.h"
#include "Search/SearchResult.hpp"
#include "Search/Uninformed/UninformedSearch.h"
#include "State.hpp"
#include "Utils/Utils.h"

#endif	/* IIA_LIB_H */

/**
 * @mainpage Projeto IIA
 *
 * A ideia é implementar os algoritmos relacionados à disciplina <b>Introdução a
 * Inteligência Artificial</b> (<a href="http://www.serverweb.unb.br/matriculaweb/graduacao/oferta dados.aspx?cod=116653&dep=116">116653</a>),
 * conforme a principal referência: <i><a href="http://www.pearson.com.br/produtos_detalhes.asp?id_p=0&livro_cod=9780136042594&pag_id=78&area_pai=21">
 * Artificial Intelligence: A Modern Approach</a></i>.
 *
 * @par Inteligência Artificial
 * O termo foi definido por John McCarthy em 1955 como: "ciência e engenharia de
 * criar máquinas inteligentes, especialmente programas de computador
 * inteligentes", sendo que <i>inteligência</i> é a parte computacional da
 * habilidade de atingir objetivos.
 *
 * @section sec_chap1 Capítulo 1 - Introdução
 * Introduz o assunto, apresentando os tópicos:
 * 	- O que é IA
 * 	- Fundamentos de IA
 * 	- História
 * 	- Estado da Arte
 *
 * @section sec_chap2 Capítulo 2 - Agentes Inteligentes
 * Apresenta agentes inteligentes, com os tópicos:
 *	- \link IIA::Agents Agentes \endlink e Ambiente
 *	- Bom Comportamento
 *	- Natureza do Ambiente
 *	- Estrutura de Agentes
 *
 * @section sec_chap3 Capítulo 3 - Busca e Resolução de Problemas
 * Introduz a busca por soluções, apresentando os tópicos:
 *	- \link IIA::Examples Exemplos de Problemas\endlink
 *	- \link IIA::Search Busca por Soluções\endlink
 *	- \link IIA::Search::Uninformed Busca sem Informações \endlink
 *	- \link IIA::Search::Informed Busca com Informações \endlink
 *
 * @section sec_chap4 Capítulo 4 - Além da Busca Clássica
 * Apresenta abordagens diferentes para buscar soluções, com os tópicos:
 *	- \link IIA::Search::Local Busca Local \endlink e Otimização
 *	- Busca Local em Espacos Contínuos
 *	- Busca Estocástica
 *	- Busca com Observação Parcial
 *	- Busca Online
 *
 * @section sec_chap5 Capítulo 5 - Busca com Adversários
 * Mostra como lidar com agentes inteligentes adversários, apresentando os tópicos:
 *	- Jogos
 *	- Decisões Ótimas
 *	- Poda
 *	- Decisões Imperfeitas
 *	- Jogos Probabilísticos
 *	- Jogos Parcialmente Observáveis
 *	- Estado da Arte
 *	- Alternativas
 *
 * @section sec_chap6 Capítulo 6 - Problemas de Satisfação de Restrições
 * Apresenta outra abordagem para formulação de problemas, com os seguintes tópicos:
 *	- Problemas de Satisfação de Restrições
 *	- Propagação de Restrições
 *	- Retrocesso
 *	- Busca Local
 *	- Estrutura de Problemas
 *
 * @todo Implementar os capítulos 4, 5 6
 * @todo Implementar testes de unidade. */
