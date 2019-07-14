/*
 * Pontuacao.cpp
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#include "Pontuacao.h"

Pontuacao::Pontuacao(int valor, Qualis* qualis, Regra *regra){
	this->valor = valor;
	this->qualis = qualis;
	this->regra = regra;
}

Pontuacao::~Pontuacao(){

}
void Pontuacao::linkaQualisEmPontuacao(Qualis* qualis){
	this->qualis = qualis;

	qualis->linkaPontuacaoEmQualis(this);
}

void Pontuacao::linkaRegraEmPontuacao(Regra *regra){
	this->regra = regra;
}


