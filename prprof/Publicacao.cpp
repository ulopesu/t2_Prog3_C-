/*
 * Publicacao.cpp
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#include "Publicacao.h"

Publicacao::Publicacao(int ano, int pagInic, int pagFim, string titulo, Veiculo *veiculo,vector <Docente*> autores, int num){
	this->ano = ano;
	this->pagInic = pagInic;
	this->pagFim = pagFim;
	this->titulo = titulo;
	this->veiculo = veiculo;
	this->num = num;
	this->autores= autores;
}

Publicacao::~Publicacao(){

}

void Publicacao::linkaDocenteEmPublicacao(Docente* autor){
	this->autores.push_back(autor);
}

void Publicacao::linkaVeiculoEmPublicacao(Veiculo* v){
	this->veiculo = v;
}

bool comparatorPublicacao(Publicacao* p1, Publicacao* p2) {
	Veiculo *v1 = p1->getVeiculo();
	Veiculo *v2 = p2->getVeiculo();
	Qualis *q1 = NULL;
	Qualis *q2 = NULL;

	int maiorAno = 0;

	vector<Qualificacao*> listaQulif1 = v1->getQualificacoes();
	vector<Qualificacao*>::iterator qi1 = listaQulif1.begin();
	while (qi1 != listaQulif1.end()) {
		Qualificacao *qualif1 = *qi1;
		if (p1->getAno() >= maiorAno) {
			maiorAno = p1->getAno();
			q1 = qualif1->getQualis();
		}
		qi1++;
	}

	maiorAno = 0;

	vector<Qualificacao*> listaQulif2 = v2->getQualificacoes();
	vector<Qualificacao*>::iterator qi2 = listaQulif2.begin();
	while (qi2 != listaQulif2.end()) {
		Qualificacao *qualif2 = *qi2;
		if (p2->getAno() >= maiorAno) {
			maiorAno = p2->getAno();
			q2 = qualif2->getQualis();
		}
		qi2++;
	}

	if (q1->getNome().compare(q2->getNome()) > 0) {
		return false;
	} else if (q1->getNome().compare(q2->getNome()) < 0) {
		return true;
	} else {
		if (p1->getAno() < p2->getAno()) {
			return false;
		} else if (p1->getAno() > p2->getAno()) {
			return true;
		} else {
			if (v1->getSigla().compare(v2->getSigla()) > 0) {
				return false;
			} else if (v1->getSigla().compare(v2->getSigla()) < 0) {
				return true;
			} else {
				if (p1->getTitulo().compare(p2->getTitulo()) > 0) {
					return false;
				} else if (p1->getTitulo().compare(p2->getTitulo()) < 0) {
					return true;
				} else {
					return false;
				}
			}
		}
	}
}
