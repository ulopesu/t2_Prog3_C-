/*
 * Qualificacao.cpp
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#include "Qualificacao.h"

Qualificacao::Qualificacao(int ano, Qualis *qualis, Veiculo *veiculo) {
	this->ano = ano;
	this->qualis = qualis;
	this->veiculo = veiculo;
}

Qualificacao::~Qualificacao(){


}

void Qualificacao::linkaVeiculoEmQualificacao(Veiculo* v){
		this->veiculo = v;
		v->linkaQualificacaoEmVeiculo(this);
}
void Qualificacao::linkaQualisEmQualificacao(Qualis* q){
		this->qualis = q;
		q->linkaQualificacaoEmQualis(this);
}
