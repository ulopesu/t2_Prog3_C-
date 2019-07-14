/*
 * Publicacao.h
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#ifndef PUBLICACAO_H_
#define PUBLICACAO_H_

using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "Veiculo.h"
#include "Qualis.h"
#include "Qualificacao.h"

class Veiculo;
class Docente;
class Qualis;
class Qualificacao;

class Publicacao {
	int ano;
	int pagInic;
	int pagFim;
	string titulo;
	Veiculo *veiculo;
	vector <Docente*> autores;
	int num;

public:
	//Construtor:
	Publicacao(int ano, int pagInic, int pagFim, string titulo, Veiculo *veiculo,vector <Docente*> autores, int num);
	
	//Funcoes:
	int getAno(){	return ano;	}
	int getPagInic(){	return pagInic;	}
	int getPagFim(){	return pagFim;	}
	string getTitulo(){	return titulo;	}
	Veiculo* getVeiculo(){	return veiculo;	}
	vector <Docente*> getAutores(){	return autores;	}
	int getNum(){	return num;	}
	
	void linkaDocenteEmPublicacao(Docente* autor);
	void linkaVeiculoEmPublicacao(Veiculo* v);

	//Destrutor:
	virtual ~Publicacao();
};

bool comparatorPublicacao(Publicacao* p1, Publicacao* p2);

#endif /* PUBLICACAO_H_ */
