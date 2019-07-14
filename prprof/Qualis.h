/*
 * Qualis.h
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#ifndef QUALIS_H_
#define QUALIS_H_

using namespace std;
#include <string>
#include <iostream>
#include <vector>

class Qualificacao;
class Pontuacao;

class Qualis {
	string nome;
	vector<Qualificacao*> qualificacoes;
	vector<Pontuacao*> pontuacoes;
public:
	//Construtor:
	Qualis(string nome,vector<Qualificacao*> qualificacoes,vector<Pontuacao*> pontuacoes);
	
	//Funcoes:
	string getNome(){	return nome;	}
	vector<Qualificacao*> getQualificacoes(){	return qualificacoes;	}
	vector<Pontuacao*>	getPontuacoes(){	return pontuacoes;	}
	
	void linkaQualificacaoEmQualis(Qualificacao* quali);
	void linkaPontuacaoEmQualis(Pontuacao* p);

	//Destrutor:
	virtual ~Qualis();
};

bool ComparadorQualis(Qualis *q1, Qualis *q2);


#endif /* QUALIS_H_ */
