/*
 * Periodico.h
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#ifndef PERIODICO_H_
#define PERIODICO_H_
#include "Publicacao.h"
#include <vector>

class Periodico : public Publicacao {
	int volume;

public:
	//Construtor;
	Periodico(int volume, int ano, int pagInic, int pagFim, string titulo, Veiculo *veiculo, vector <Docente*> autores, int num);
	
	//Funcoes:
	int getVolume(){	return volume;	}
	
	//Destrutor:
	virtual ~Periodico();
};

#endif /* PERIODICO_H_ */
