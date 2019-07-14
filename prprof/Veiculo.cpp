/*
 * Veiculo.cpp
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#include "Veiculo.h"

Veiculo::Veiculo(char tipo, string nome, string sigla, string issn, double fatorDeImpacto, vector<Qualificacao*> qualificacoes, vector<Publicacao*> publicacoes){
	this->tipo = tipo;
	this->nome = nome;
	this->sigla = sigla;
	this->issn = issn;
	this->fatorDeImpacto = fatorDeImpacto;
	this->qualificacoes = qualificacoes;
	this->publicacoes = publicacoes;
}

Veiculo::~Veiculo(){

}

void Veiculo::linkaQualificacaoEmVeiculo(Qualificacao* quali){
		this->qualificacoes.push_back(quali);
}

void Veiculo::linkaPublicacaoEmVeiculo(Publicacao* publi){
		this->publicacoes.push_back(publi);
		publi->linkaVeiculoEmPublicacao(this);
}
