/*
 * Conferencia.h
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#ifndef CONFERENCIA_H_
#define CONFERENCIA_H_

using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "Publicacao.h"
#include "Veiculo.h"

class Conferencia : public Publicacao {
	string local;

public:
	//Construtor:
	Conferencia(string local, int ano, int pagInic, int pagFim, string titulo, Veiculo *veiculo,vector <Docente*> autores, int num);
	
	//Funcoes:
	string getLocal(){	return local;	}
	
	//Destrutor:
	virtual ~Conferencia();	
};

#endif /* CONFERENCIA_H_ */
