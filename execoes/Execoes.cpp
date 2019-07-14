/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Execoes.cpp
 * Author: guest-bnhbs8
 * 
 * Created on 31 de Julho de 2017, 08:35
 */

#include <algorithm>
#include "Execoes.h"

Execoes::Execoes(string erro) {
    this->message = erro;
}

Execoes::Execoes(const Execoes& orig) {
}

Execoes::~Execoes() throw (){
}
// IMPRIME ERRO GERADO NA EXECUCAO
string Execoes::Mensagem() const{
    return this->message;
}
