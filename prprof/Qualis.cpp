/*
 * Qualis.cpp
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#include "Qualis.h"

Qualis::Qualis(string nome,vector<Qualificacao*> qualificacoes,vector<Pontuacao*> pontuacoes){
	this->nome = nome;
	this->pontuacoes = pontuacoes;
	this->qualificacoes = qualificacoes;
}

Qualis::~Qualis(){

}

void Qualis::linkaQualificacaoEmQualis(Qualificacao* quali){
		this->qualificacoes.push_back(quali);
	}
void Qualis::linkaPontuacaoEmQualis(Pontuacao* p){
		this->pontuacoes.push_back(p);
}

bool ComparadorQualis(Qualis *q1, Qualis *q2){
	if(q1->getNome().compare(q2->getNome()) > 0){
		return false;
	} else if (q1->getNome().compare(q2->getNome()) == 0){
		return false;
	} else {
		return true;
	}
}

