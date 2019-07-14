/*
 * LeiaCSV.h
 *
 *  Created on: 29 de jul de 2017
 *      Author: ulopesu
 */

#ifndef LEIACSV_H_
#define LEIACSV_H_

#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include "../util/Tokenizer.h"
#include "../util/StringUtils.h"
#include "../util/DateUtils.h"
#include "../util/NumberUtils.h"

#include "../prprof/Docente.h"
#include "../prprof/Publicacao.h"
#include "../prprof/Qualificacao.h"
#include "../prprof/Veiculo.h"
#include "../prprof/Pontuacao.h"
#include "../prprof/Qualis.h"
#include "../prprof/Conferencia.h"
#include "../prprof/Periodico.h"
#include "../prprof/Regra.h"
#include "../execoes/Execoes.h"

using namespace std;

class LeiaCSV {
public:
	//Construtor:
	LeiaCSV();

	//Funcoes:
	void lerDocente(vector<Docente*> *docentes, char *diretorio);

	void lerVeiculos(vector<Veiculo*> *veiculos, char *diretorio);

	void lerQualificacao(vector<Qualificacao*> *qualificacoes, vector<Veiculo*> *veiculos, vector<Qualis*> *listaQualis , char* diretorio);

	void lerPublicacao(vector<Publicacao*> *publicacoes, vector<Veiculo*> *veiculos,vector<Docente*> *docentes, char* diretorio);

	void lerRegras(vector<Regra*> *regras, vector<Qualificacao*> *qualificacoes, vector<Pontuacao*> *pontuacoes, vector<Qualis*> *listaQualis, int ano, char* diretorio);

	bool ehQualisValido(string s);

	//Destrutor:
	virtual ~LeiaCSV();
};

#endif /* LEIACSV_H_ */
