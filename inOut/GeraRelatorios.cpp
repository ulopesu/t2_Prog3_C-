/*
 * GeraRelatorios.cpp
 *
 *  Created on: 30 de jul de 2017
 *      Author: ulopesu
 */

#include "GeraRelatorios.h"

using namespace std;
using namespace cpp_util;

GeraRelatorios::GeraRelatorios() {
    // TODO Auto-generated constructor stub

}

GeraRelatorios::~GeraRelatorios() {
    // TODO Auto-generated destructor stub
}

void GeraRelatorios::recredenciamento(vector<Docente*> docentes, vector<Regra*> regras, int ano) {

    stable_sort(docentes.begin(), docentes.end(), ComparadorDocente);

    //DECLARA VARIAVEIS
    time_t dataRegra;

    string nomeData = "02/01/";
    stringstream conversor;
    conversor << ano;
    nomeData.append(conversor.str());

    // TRATA ERRO - DATA ERRADA
    if (!validDate(nomeData, DATE_FORMAT_PT_BR_SHORT)) {
        throw Execoes("Erro de formatação");
    }
    dataRegra = parseDate(nomeData, DATE_FORMAT_PT_BR_SHORT);

    double pontMin = 0.0;

    //PEGA A REGRA DO ANO DADO
    vector<Regra*>::iterator r = regras.begin();
    while (r != regras.end()) {
        Regra *regra = *r;

        if (difftime(regra->getDataInic(), dataRegra) < 0 && difftime(regra->getDataFim(), dataRegra) > 0) {
            pontMin = (double) regra->getPontMin();
        }
        r++;
    }



    ofstream out("1-recredenciamento.csv");
    if (!out.is_open()) {
        throw Execoes("Erro de I/O");
    }
    out << "Docente;Pontuação;Recredenciado?" << endl;


    //PERCORRE O VECTOR DE DOCENTES
    vector<Docente*>::iterator d = docentes.begin();
    while (d != docentes.end()) {
        Docente *docente = *d;

        out << docente->getNome() << ";" << formatDoubleCurrency(docente->notaDocente(ano), LOCALE_PT_BR, 1) << ";";

        //SE O DOCENTE EH COORDENADOR
        if (docente->isCoordenador()) {
            out << "Coordenador" << endl;
        }//SE DOCENTE TIVER MAIS QUE 60 ANOS
        else if (difftime(dataRegra, docente->getNascimento()) > 1893456000) {
            out << "PPS" << endl;
        }//SE DOCENTE ENTROU NO PROGRAMA MENOS DE 3 ANOS
        else if (difftime(dataRegra, docente->getEngresso()) < 94672800) {
            out << "PPJ" << endl;
        }//DOCENTE AVALIADO POR SUA NOTA
        else {
            if (docente->notaDocente(ano) >= pontMin) {
                out << "Sim" << endl;
            } else {
                out << "Não" << endl;
            }
        }
        d++;
    }
}

void GeraRelatorios::listaPublicacoes(vector<Publicacao*> *publicacoes2) {

    vector<Publicacao*> publicacoes = *publicacoes2;

    //ORDENA O VETOR DE PUBLICACOES
    stable_sort(publicacoes.begin(), publicacoes.end(), comparatorPublicacao);
	
    //ABRE O ARQUIVO
    ofstream out("2-publicacoes.csv");
   
    //TRATA ERRO - I/O
    if (!out.is_open()) {
        throw Execoes("Erro de I/O");
    }

    //ESCREVE NO ARQUIVO
    out << "Ano;Sigla Veículo;Veículo;Qualis;Fator de Impacto;Título;Docentes" << endl;

    //PERCORRE O VETOR DE PUBLICACOES
    vector<Publicacao*>::iterator p = publicacoes.begin();
    while (p != publicacoes.end()) {
        Publicacao *p2 = *p;
        Veiculo *v = p2->getVeiculo();
        Qualis *qualis;

        int maiorAno = 0;

        vector<Qualificacao*> listQualificacao = v->getQualificacoes();
        vector<Qualificacao*>::iterator q = listQualificacao.begin();
	
	//PERCORRE O VETOR DE QUALIFICACOES E ENCONTRA A MAIS RECENTE
        while (q != listQualificacao.end()) {
            Qualificacao *qualif = *q;
            if (qualif != NULL) {
                if (p2->getAno() >= maiorAno) {
                    maiorAno = p2->getAno();
                    qualis = qualif->getQualis();
                }
            }
            q++;
        }
	
        //ESCREVE NO ARQUIVO
        out << p2->getAno() << ";" << v->getSigla() << ";" << v->getNome()
                << ";" << qualis->getNome() << ";" << formatDoubleCurrency(v->getFatorDeImpacto(), LOCALE_PT_BR, 3)
                << ";" << p2->getTitulo() << ";";
	
	//IMPRIME TODOS OS AUTORES DA PUBLICACAO
        out << p2->getAutores()[0]->getNome();
        for (unsigned int i = 1; i < p2->getAutores().size(); i++) {
            out << "," << p2->getAutores()[i]->getNome();
        }
        out << endl;
        p++;
    }
    out.close();
}

void GeraRelatorios::estatisticaPublicacoes(vector<Publicacao*> *publicacoesP, vector<Qualis*> listaQualis) {
    vector<Publicacao*> publicacoes = *publicacoesP;

    //ORDENA O VETOR DE QUALIS
    stable_sort(listaQualis.begin(), listaQualis.end(), ComparadorQualis);
    ofstream out("3-estatisticas.csv");

    if (!out.is_open()) {
        throw Execoes("Erro de I/O");
    }

    //ESCREVE NO ARQUIVO
    out << "Qualis;Qtd. Artigos;Média Artigos / Docente" << endl;
    vector<Qualis*>::iterator q = listaQualis.begin();
    while (q != listaQualis.end()) {
        Qualis *qualis = *q;
        int count = 0;
        double mediaAutores = 0;

	//PERCORRE O VETOR DE PUBLICACOES
        vector<Publicacao*>::iterator p = publicacoes.begin();
        while (p != publicacoes.end()) {
            Publicacao *publicacao = *p;
            Veiculo* v = publicacao->getVeiculo();
            vector<Qualificacao*> listaQualificacao = v->getQualificacoes();
            Qualis* qq;
            int maiorAno = 0;
		
	    //PERCORRE O VETOR DE QUALIFICACOES E ENCONTRA A MAIS RECENTE
            vector<Qualificacao*>::iterator ql = listaQualificacao.begin();
            while (ql != listaQualificacao.end()) {
                Qualificacao* qualificacao = *ql;

                if (publicacao->getAno() >= maiorAno) {
                    maiorAno = publicacao->getAno();
                    qq = qualificacao->getQualis();
                }

                ql++;
            }
	    
	    //CALCULA MEDIA DE AUTORES
            if (!qq->getNome().compare(qualis->getNome())) {
                count++;
                double tam = (double) publicacao->getAutores().size();
                mediaAutores += 1 / tam;
            }

            p++;
        }

        float fmedia = (float) mediaAutores;

        out << qualis->getNome() << ";" << count << ";" << formatDoubleCurrency(fmedia, LOCALE_PT_BR, 2) << endl;

        q++;
    }
}



