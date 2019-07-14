/*
 * Regra.cpp
 *
 *  Created on: 24 de jul de 2017
 *      Author: ulopesu
 */

#include "Regra.h"

Regra::Regra(time_t dataInic, time_t dataFim, double multPeriodico, int qtdAnos, int pontMin, vector<Pontuacao*> pontuacoes){
	this->dataInic = dataInic;
	this->dataFim = dataFim;
	this->multPeriodico = multPeriodico;
	this->qtdAnos = qtdAnos;
	this->pontMin = pontMin;
	this->pontuacoes = pontuacoes;
}

Regra::~Regra(){

}

void Regra::linkaPontuacoesEmRegra(vector<Pontuacao*> pontuacoes) {
	this->pontuacoes = pontuacoes;

	vector<Pontuacao*>::iterator p = pontuacoes.begin();
	while (p != pontuacoes.end()) {
		Pontuacao *p2 = *p;
		p2->linkaRegraEmPontuacao(this);
		p++;
	}
}
