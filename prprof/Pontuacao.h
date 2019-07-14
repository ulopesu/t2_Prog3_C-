/*
 * Pontuacao.h
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#ifndef PONTUACAO_H_
#define PONTUACAO_H_

using namespace std;
#include <vector>
#include "Qualis.h"

class Qualis;
class Regra;

class Pontuacao {
	Qualis* qualis;
	Regra *regra;
	int valor;
public:
	//Construtor;
	Pontuacao(int valor, Qualis* qualis, Regra *regra);
	
	//Funcoes:
	Qualis* getQualis(){	return qualis;	}
	Regra* getRegra(){	return regra;	}
	int getValor(){	return valor;	}

	void linkaQualisEmPontuacao(Qualis* qualis);
	void linkaRegraEmPontuacao(Regra* regra);
	
	//Destrutor:
	virtual ~Pontuacao();
};

#endif /* PONTUACAO_H_ */
