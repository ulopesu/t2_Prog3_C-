/*
 * Regra.h
 *
 *  Created on: 24 de jul de 2017
 *      Author: ulopesu
 */

#ifndef REGRA_H_
#define REGRA_H_

using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include "Pontuacao.h"

class Pontuacao;

class Regra {
	time_t dataInic;
	time_t dataFim;
	double multPeriodico;
	int qtdAnos;
	int pontMin;
	vector<Pontuacao*> pontuacoes;

public:
	//Construtor:
	Regra(time_t dataInic, time_t dataFim, double multPeriodico, int qtdAnos, int pontMin, vector<Pontuacao*> pontuacoes);

	//Funcoes:
	time_t getDataInic(){	return dataInic;	}
	time_t getDataFim(){	return dataFim;	}
	double getMultPeriodico(){	return multPeriodico;	}
	int getQtdAnos(){	return qtdAnos;	}
	int getPontMin(){	return pontMin;	}
	vector<Pontuacao*> getPontuacoes(){	return pontuacoes;	}

	void linkaPontuacoesEmRegra(vector<Pontuacao*> pontuacoes);

	//Destrutor:
	virtual ~Regra();
};

#endif /* REGRA_H_ */
