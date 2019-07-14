/*
 * Conferencia.cpp
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#include "Conferencia.h"

Conferencia::Conferencia(string local, int ano, int pagInic, int pagFim, string titulo, Veiculo *veiculo,vector <Docente*> autores, int num) : Publicacao(ano, pagInic, pagFim, titulo, veiculo,autores, num) {
	this->local = local;
}

Conferencia::~Conferencia(){

}

