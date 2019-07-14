/*
 * GeraRelatorios.h
 *
 *  Created on: 30 de jul de 2017
 *      Author: ulopesu
 */

#ifndef GERARELATORIOS_H_
#define GERARELATORIOS_H_


#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include <sstream>
#include <iomanip>
#include <locale>
#include "../util/Tokenizer.h"
#include "../util/StringUtils.h"
#include "../util/DateUtils.h"
#include "../util/NumberUtils.h"

#include "../prprof/Publicacao.h"
#include "../prprof/Docente.h"
#include "../prprof/Regra.h"
#include "../execoes/Execoes.h"
#include <stdio.h>

using namespace std;
class Publicacao;
class Docente;

class GeraRelatorios {
public:
	//Construtor:
	GeraRelatorios();

	//Destrutor:
	virtual ~GeraRelatorios();

	//Funcoes:
	void listaPublicacoes(vector<Publicacao*> *publicacoes);
	void recredenciamento(vector<Docente*> docentes, vector<Regra*> regras, int ano);
	void estatisticaPublicacoes(vector<Publicacao*> *publicacoesP, vector<Qualis*> listaQualis);

};



#endif /* GERARELATORIOS_H_ */
