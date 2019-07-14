/*
 * Qualificacao.h
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#ifndef QUALIFICACAO_H_
#define QUALIFICACAO_H_
#include "Qualis.h"
#include "Veiculo.h"

class Veiculo;
class Qualis;

class Qualificacao {
	int ano;
	Qualis *qualis;
	Veiculo *veiculo;
public:
	//Construtor:
	Qualificacao(int ano2, Qualis *qualis2, Veiculo *veiculo2);
	
	//Funcoes:
	int getAno(){	return ano;	}
	Qualis* getQualis(){	return qualis;	}
	Veiculo* getVeiculos(){	return veiculo;	}
	
	void linkaVeiculoEmQualificacao(Veiculo* v);

	void linkaQualisEmQualificacao(Qualis* q);

	//Destrutor:
	virtual ~Qualificacao();
};

#endif /* QUALIFICACAO_H_ */
