/*
 * Docente.cpp
 *
 *  Created on: 21 de jul de 2017
 *      Author: 2016101767
 */

#include "Docente.h"

using namespace std;
using namespace cpp_util;

Docente::Docente(string nome, time_t nascimento, time_t engresso,
		bool ehCoordenador, vector<Publicacao*> publicacoes, string codigo) {
	this->nome = nome;
	this->nascimento = nascimento;
	this->engresso = engresso;
	this->ehCoordenador = ehCoordenador;
	this->publicacoes = publicacoes;
	this->codigo = codigo;
}

Docente::~Docente() {

}

void Docente::linkaPublicacaoEmDocente(Publicacao* publicacao) {
	this->publicacoes.push_back(publicacao);
	publicacao->linkaDocenteEmPublicacao(this);
}

double Docente::notaDocente(int ano) {

	//DECLARA VARIAVEIS
	double nota = 0;
	time_t data;

	string nomeData = "02/01/";
	stringstream conversor;
	conversor << ano;
	nomeData.append(conversor.str());

	// TRATAR CORRETAMENTE
	try {
		data = parseDate(nomeData, DATE_FORMAT_PT_BR_SHORT);
	} catch (exception& e) {
		cout << "Erro de formatação DATA" << endl;
		return false;
	}

	//PERCORRE PUBLICACOES
	vector<Publicacao*>::iterator p = this->publicacoes.begin();
	while (p != this->publicacoes.end()) {

		Publicacao *p2 = *p;
		int anoP = p2->getAno();

		//PEGA A QUALIFICACAO MAIS RECENTE
		if (anoP < ano) {

			Veiculo* v = p2->getVeiculo();
			Qualificacao* qualif = NULL;
			int maiorAno = 0;

			vector<Qualificacao*> listaQualificao = v->getQualificacoes();
			vector<Qualificacao*>::iterator q = listaQualificao.begin();
			while (q != listaQualificao.end()) {
				Qualificacao *q2 = *q;
				if (q2 != NULL) {
					if (q2->getAno() >= maiorAno) {
						maiorAno = q2->getAno();
						qualif = q2;
					}

				}
				q++;
			}

			if (qualif == NULL) {
				cout << "Publicacao nao qualificado no ano: " << ano << endl;
				return nota;
			}

			//SE FOR PERIODICO
			if (v->getTipo() == 'P') {
				if (qualif != NULL) {

					Qualis* qualis2 = qualif->getQualis();
					vector<Pontuacao*> listaPontuacao2 =
							qualis2->getPontuacoes();

					vector<Pontuacao*>::iterator pont = listaPontuacao2.begin();
					while (pont != listaPontuacao2.end()) {
						Pontuacao *pont2 = *pont;

						if (pont2->getRegra() != NULL) {
							if (difftime(pont2->getRegra()->getDataInic(), data)
									< 0
									&& difftime(pont2->getRegra()->getDataFim(),
											data) > 0) {

								int aux = pont2->getRegra()->getQtdAnos();
								if (p2->getAno() >= ano - aux) {
									nota +=
											(double) pont2->getValor()
													* pont2->getRegra()->getMultPeriodico();
								}

							}
						}
						pont++;
					}
				}

			}
			//SE FOR CONFERENCIA
			else {
				if (qualif != NULL) {

					Qualis* qualis = qualif->getQualis();
					vector<Pontuacao*> listaPontuacao = qualis->getPontuacoes();

					vector<Pontuacao*>::iterator pontuac =
							listaPontuacao.begin();
					while (pontuac != listaPontuacao.end()) {
						Pontuacao *pontuac2 = *pontuac;

						if (pontuac2->getRegra() != NULL) {
							if (difftime(pontuac2->getRegra()->getDataInic(),
									data) < 0
									&& difftime(
											pontuac2->getRegra()->getDataFim(),
											data) > 0) {

								int aux = pontuac2->getRegra()->getQtdAnos();
								if (p2->getAno() >= ano - aux) {
									nota += (double) pontuac2->getValor();
								}
							}
						}
						pontuac++;

					}
				}
			}

		}
		p++;
	}

	return nota;
}

bool ComparadorDocente(Docente *d1, Docente *d2) {
	if (d1->getNome().compare(d2->getNome()) > 0) {
		return false;
	} else {
		return true;
	}
}
