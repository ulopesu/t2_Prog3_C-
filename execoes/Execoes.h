/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Execoes.h
 * Author: guest-bnhbs8
 *
 * Created on 31 de Julho de 2017, 08:35
 */

#ifndef EXECOES_H
#define EXECOES_H
#include <iostream>
#include <exception>
#include <string>
 
using namespace std;
class Execoes : public exception {
    string message;
public:
    //Construtor:
    Execoes(string erro);
    Execoes(const Execoes& orig);
    //Destrutor:
    virtual ~Execoes() throw ();
    //Funcoes:
    virtual string Mensagem() const;
    

private:
};

#endif /* EXECOES_H */
