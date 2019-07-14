/*
 * Veiculo.h
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#ifndef VEICULO_H_
#define VEICULO_H_

using namespace std;
#include <vector>
#include <string>
#include <iostream>

#include "Publicacao.h"

class Publicacao;
class Qualificacao;

class Veiculo {
	char tipo;
	string nome;
	string sigla;
	string issn;
	double fatorDeImpacto;
	vector<Qualificacao*> qualificacoes;
	vector<Publicacao*> publicacoes;

public:
	//Construtor:
	Veiculo(char tipo2, string nome2, string sigla2, string issn2, double fatorDeImpacto2, vector<Qualificacao*> qualificacoes, vector<Publicacao*> publicacoes);
	
	//Funcoes:
	char getTipo() {	return tipo;	}
	string getNome() {	return nome;	}
	string getSigla() {	return sigla;	}
	string getIssn() {	return issn;	}
	double getFatorDeImpacto() {	return fatorDeImpacto;	}
	vector<Qualificacao*> getQualificacoes() {	return qualificacoes;	}
	vector<Publicacao*> getPublicacoes() {	return publicacoes;	}
	
	void linkaQualificacaoEmVeiculo(Qualificacao *quali);
	void linkaPublicacaoEmVeiculo(Publicacao *publi);

	//Destrutor:
	virtual ~Veiculo();
};

#endif /* VEICULO_H_ */
