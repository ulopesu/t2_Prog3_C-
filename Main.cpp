/*
 * Main.cpp
 *
 *  Created on: 24 de jul de 2017
 *      Author: ulopesu
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "util/Tokenizer.h"
#include "util/NumberUtils.h"
#include "util/StringUtils.h"
#include "inOut/LeiaCSV.h"
#include "inOut/GeraRelatorios.h"
#include "string.h"
#include "execoes/Execoes.h"


using namespace std;
using namespace cpp_util;

int main(int argc, char** argv) {
    int ano;
    char *dirDocentes;
    char *dirVeiculos;
    char *dirPublicacoes;
    char *dirQualificacoes;
    char *dirRegras;
	
    //PEGA TODOS OS ARGUMENTOS
    try {
        for (int i = 0; i < argc; i++) {
            if (!strcmp(argv[i], "-d")) {
                dirDocentes = strdup(argv[i + 1]);
            } else if (!strcmp(argv[i], "-v")) {
                dirVeiculos = strdup(argv[i + 1]);
            } else if (!strcmp(argv[i], "-p")) {
                dirPublicacoes = strdup(argv[i + 1]);
            } else if (!strcmp(argv[i], "-q")) {
                dirQualificacoes = strdup(argv[i + 1]);
            } else if (!strcmp(argv[i], "-r")) {
                dirRegras = strdup(argv[i + 1]);
            } else if (!strcmp(argv[i], "-a")) {
                string argano = argv[i + 1];
                if (!isNumber(argano)) {
                    throw Execoes("Erro de Formatacao");
                } else {
                    ano = atoi(argv[i + 1]);
                }
            }
        }

        LeiaCSV *l = new LeiaCSV();
        GeraRelatorios *g = new GeraRelatorios();

        //DECLARA TODOS OS VETORES
        vector<Docente*> docentes;
        vector<Veiculo*> veiculos;
        vector<Qualificacao*> qualificacoes;
        vector<Qualis*> qualis;
        vector<Publicacao*> publicacoes;
        vector<Pontuacao*> pontuacoes;
        vector<Regra*> regras;

        //LE TODOS OS ARQUIVOS
        l->lerDocente(&docentes, dirDocentes);
        l->lerVeiculos(&veiculos, dirVeiculos);
        l->lerQualificacao(&qualificacoes, &veiculos, &qualis, dirQualificacoes);
        l->lerPublicacao(&publicacoes, &veiculos, &docentes, dirPublicacoes);
        l->lerRegras(&regras, &qualificacoes, &pontuacoes, &qualis, ano, dirRegras);

	//GERA TODOS OS RELATORIOS
        g->listaPublicacoes(&publicacoes);
        g->recredenciamento(docentes, regras, ano);
        g->estatisticaPublicacoes(&publicacoes, qualis);

    } catch (Execoes& erro) {
        cout <<  erro.Mensagem() << endl;
    }

    //LIBERA A MEMORIA ARMAZENADA PELOS DIRETORIOS
    free(dirDocentes);
    free(dirVeiculos);
    free(dirPublicacoes);
    free(dirQualificacoes);
    free(dirRegras);

    return 0;
}
