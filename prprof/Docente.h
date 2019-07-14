/*
 * Docente.h
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#ifndef DOCENTE_H_
#define DOCENTE_H_

using namespace std;
#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include "../util/Tokenizer.h"
#include "../util/StringUtils.h"
#include "../util/DateUtils.h"
#include "../util/NumberUtils.h"


#include "Publicacao.h"
#include "Qualificacao.h"
#include "Regra.h"
#include "Qualis.h"
#include "Pontuacao.h"

class Publicacao;

class Docente {
	string nome;
	time_t nascimento;
	time_t engresso;
	bool ehCoordenador;
	vector<Publicacao*> publicacoes;
	string codigo;

public:
	//Construtor:
	Docente(string nome, time_t nascimento, time_t engresso, bool ehCoordenador, vector<Publicacao*> publicacoes, string codigo);
	
	//Funcoes:
	string getNome(){	return nome;	}
	time_t getNascimento(){	return nascimento;	}
	time_t getEngresso(){	return engresso;	}
	bool isCoordenador(){ return ehCoordenador;	}
	vector<Publicacao*> getPublicaoes(){	return publicacoes;	}
	string getCodigo(){	return this->codigo;}

	double notaDocente(int ano);

	void linkaPublicacaoEmDocente(Publicacao* publicacao);


    //Destrutor:
    virtual ~Docente();
};

bool ComparadorDocente(Docente *d1, Docente *d2);

#endif /* DOCENTE_H_ */
