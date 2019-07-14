/*
 * LeiaCSV.cpp
 *
 *  Created on: 29 de jul de 2017
 *      Author: ulopesu
 */

#include "LeiaCSV.h"

using namespace std;
using namespace cpp_util;

LeiaCSV::LeiaCSV() {
	// TODO Auto-generated constructor stub

}

LeiaCSV::~LeiaCSV() {
	// TODO Auto-generated destructor stub
}

void LeiaCSV::lerDocente(vector<Docente*> *docentes, char *diretorio) {
	//DECLARA AS VARIAVEIS
	string nome;
	string codigo;
	time_t nascimento;
	time_t engresso;
	bool ehCoordenador;

	ifstream in(diretorio);

	if (!in.is_open()) {
		throw Execoes("Erro de I/O");
	}

	string linha;

	//LE ARQUIVO
	getline(in, linha);
	while (getline(in, linha)) {

		//SEPARA A LINHA EM UM VECTOR DE STRINGS
		Tokenizer tok(linha, ';');
		vector<string> leitura = tok.remaining();

		nome = trim(leitura[1]);

		if (isNumber(trim(leitura[0]))) {
			codigo = trim(leitura[0]);
		} else {
			throw Execoes("Erro de formatação");
		}

		vector<Docente*>::iterator d = docentes->begin();
		while (d != docentes->end()) {
			Docente *d2 = *d;
			string codigoD = d2->getCodigo();

			if (!codigoD.compare(codigo)) {
				throw Execoes("Código repetido para docente: " + codigoD + ".");
			}
			d++;
		}

		//FAZER TRATAMENTO DE EXCEPTION

		if (!validDate(trim(leitura[2]), DATE_FORMAT_PT_BR_SHORT)
				|| !validDate(trim(leitura[3]), DATE_FORMAT_PT_BR_SHORT)) {
			throw Execoes("Erro de formatação");
		} else {
			nascimento = parseDate(trim(leitura[2]), DATE_FORMAT_PT_BR_SHORT);
			engresso = parseDate(trim(leitura[3]), DATE_FORMAT_PT_BR_SHORT);
		}

		if (leitura[4][0] != 'X')
			ehCoordenador = false;
		else {
			ehCoordenador = true;
		}
		vector<Publicacao*> p;

		Docente *docente = new Docente(nome, nascimento, engresso,
				ehCoordenador, p, codigo);
		docentes->push_back(docente);

	}
	in.close();
}

void LeiaCSV::lerVeiculos(vector<Veiculo*> *veiculos, char* diretorio) {

	//DECLARA VARIAVEIS
	string nome;
	string sigla;
	char tipo;
	string issn;
	double fatorDeImpacto = 0;

	ifstream in(diretorio);

	//TRATA ERRO - I/O
	if (!in.is_open()) {
		throw Execoes("Erro de I/O");
	}

	string linha = "";

	//LE ARQUIVO
	getline(in, linha);
	while (getline(in, linha)) {

		//SEPARA A LINHA EM UM VECTOR DE STRINGS
		Tokenizer tok(linha, ';');
		vector<string> leitura = tok.remaining();

		sigla = trim(leitura[0]);
		tipo = leitura[2][0];
		nome = trim(leitura[1]);

		if (tipo != 'C' && tipo != 'P') {
			string s;
			stringstream conversor;
			conversor << tipo;
			conversor >> s;
			throw Execoes(
					"Tipo de veículo desconhecido para veículo " + sigla + ": "
							+ s + ".");
		}

		vector<Veiculo*>::iterator v = veiculos->begin();
		while (v != veiculos->end()) {
			Veiculo *v2 = *v;
			string siglaV = v2->getSigla();

			if (!sigla.compare(siglaV)) {
				throw Execoes("Código repetido para veículo: " + siglaV + ".");
			}
			v++;
		}

		if (!isNumber(trim(leitura[3]))) {
			throw Execoes("Erro de formatação");
		} else {
			fatorDeImpacto = parseDouble(trim(leitura[3]), LOCALE_PT_BR);
		}

		if (leitura.size() > 4) {

			issn = trim(leitura[4]);
		}

		vector<Qualificacao*> q;
		vector<Publicacao*> p;

		Veiculo* veiculo = new Veiculo(tipo, nome, sigla, issn, fatorDeImpacto,
				q, p);

		veiculos->push_back(veiculo);
	}

}

void LeiaCSV::lerQualificacao(vector<Qualificacao*> *qualificacoes,
		vector<Veiculo*> *veiculos, vector<Qualis*> *listaQualis,
		char* diretorio) {

	//DECLARA VARIAVEIS
	int ano;

	ifstream in(diretorio);

	if (!in.is_open()) {
		throw Execoes("Erro de I/O");
	}

	string linha = "";

	//LE ARQUIVO
	getline(in, linha);
	while (getline(in, linha)) {

		//SEPARA A LINHA EM UM VECTOR DE STRINGS
		Tokenizer tok(linha, ';');
		vector<string> leitura = tok.remaining();

		if (isNumber(trim(leitura[0]))) {
			ano = atoi(leitura[0].c_str());
		} else {
			throw Execoes("Erro de formatação");
		}

		if (!ehQualisValido(trim(leitura[2]))) {
			throw Execoes(
					"Qualis desconhecido para qualificação do veículo "
							+ trim(leitura[1]) + " no ano " + trim(leitura[0])
							+ ": " + trim(leitura[2]) + ".");
		}
		string nomeQualis = trim(leitura[2]);

		Veiculo *veiculo = NULL;
		string siglaVeiculo = trim(leitura[1]);

		vector<Veiculo*>::iterator v = veiculos->begin();
		while (v != veiculos->end()) {
			Veiculo *v2 = *v;
			string siglaV = v2->getSigla();

			if (!siglaVeiculo.compare(siglaV)) {
				veiculo = v2;
			}
			v++;
		}

		if (veiculo != NULL) {
			bool achou = false;
			Qualis* qualis;

			vector<Qualis*>::iterator q = listaQualis->begin();
			while (q != listaQualis->end()) {
				Qualis *q2 = *q;
				string nome = q2->getNome();

				if (!nome.compare(nomeQualis)) {
					qualis = q2;
					achou = true;
					break;
				}
				q++;
			}

			if (!achou) {
				vector<Qualificacao*> q;
				vector<Pontuacao*> p;

				qualis = new Qualis(nomeQualis, q, p);
				listaQualis->push_back(qualis);
			}

			Qualificacao* qualif = new Qualificacao(ano, qualis, veiculo);

			qualif->linkaQualisEmQualificacao(qualis);
			qualif->linkaVeiculoEmQualificacao(veiculo);
			qualificacoes->push_back(qualif);

		} else {
			throw Execoes(
					"Sigla de veículo não definida usada na qualificação do ano \""
							+ trim(leitura[0]) + "\": " + siglaVeiculo + ".");
		}
	}

	bool a1 = false;
	bool a2 = false;
	bool b1 = false;
	bool b2 = false;
	bool b3 = false;
	bool b4 = false;
	bool b5 = false;
	bool c = false;
	vector<Qualis*>::iterator qua = listaQualis->begin();
	while (qua != listaQualis->end()) {
		Qualis *qua2 = *qua;
		string nomeQua = qua2->getNome();

		if (!nomeQua.compare("A1")) {
			a1 = true;
		}
		if (!nomeQua.compare("A2")) {
			a2 = true;
		}
		if (!nomeQua.compare("B1")) {
			b1 = true;
		}
		if (!nomeQua.compare("B2")) {
			b2 = true;
		}
		if (!nomeQua.compare("B3")) {
			b3 = true;
		}
		if (!nomeQua.compare("B4")) {
			b4 = true;
		}
		if (!nomeQua.compare("B5")) {
			b5 = true;
		}
		if (!nomeQua.compare("C")) {
			c = true;
		}
		qua++;
	}

	vector<Qualificacao*> aux;
	vector<Pontuacao*> aux2;
	if(!a1){
		Qualis* A1 = new Qualis("A1",aux,aux2);
		listaQualis->push_back(A1);
	}
	if(!a2){
			Qualis* A2 = new Qualis("A2",aux,aux2);
			listaQualis->push_back(A2);
		}
	if(!b1){
			Qualis* B1 = new Qualis("B1",aux,aux2);
			listaQualis->push_back(B1);
		}
	if(!b2){
			Qualis* B2 = new Qualis("B2",aux,aux2);
			listaQualis->push_back(B2);
		}
	if(!b3){
			Qualis* B3 = new Qualis("B3",aux,aux2);
			listaQualis->push_back(B3);
		}
	if(!b4){
			Qualis* B4 = new Qualis("B4",aux,aux2);
			listaQualis->push_back(B4);
		}
	if(!b5){
			Qualis* B5 = new Qualis("B5",aux,aux2);
			listaQualis->push_back(B5);
		}
	if(!c){
			Qualis* C = new Qualis("C",aux,aux2);
			listaQualis->push_back(C);
		}

}

void LeiaCSV::lerPublicacao(vector<Publicacao*> *publicacoes,
		vector<Veiculo*> *veiculos, vector<Docente*> *docentes,
		char* diretorio) {

	Veiculo* veiculo = NULL;
	int ano = 0;
	string titulo;
	int num = 0;
	string local;
	int volume = 0;
	int pagInic = 0;
	int pagFim = 0;
	string codigo;

	//ABRE ARQUIVO
	ifstream in(diretorio);

	//TRATA ERRO - I/O
	if (!in.is_open()) {
		throw Execoes("Erro de I/O");
	}

	string linha = "";

	//LE ARQUIVO
	getline(in, linha);
	while (getline(in, linha)) {

		//SEPARA A LINHA EM UM VECTOR DE STRINGS
		Tokenizer tok(linha, ';');
		vector<string> leitura = tok.remaining();

		titulo = trim(leitura[2]);
		bool achou = false;

		if (isNumber(trim(leitura[0])) && isNumber(trim(leitura[4]))
				&& isNumber(trim(leitura[7])) && isNumber(trim(leitura[8]))) {
			ano = atoi(leitura[0].c_str());
			num = atoi(leitura[4].c_str());
			pagInic = atoi(leitura[7].c_str());
			pagFim = atoi(leitura[8].c_str());
		} else {
			throw Execoes("Erro de formatação");
		}

		string siglaVeiculo = trim(leitura[1]);

		bool achouVeiculo;
		achouVeiculo = false;
		//ACHA O VEICULO
		vector<Veiculo*>::iterator v = veiculos->begin();
		while (v != veiculos->end()) {
			Veiculo *v2 = *v;
			string siglaV = v2->getSigla();

			if (!siglaVeiculo.compare(siglaV)) {
				veiculo = v2;
				achouVeiculo = true;
				break;
			}
			v++;
		}

		//SEPARA A LEITURA EM UM VECTOR DE STRINGS DE AUTORES
		Tokenizer tok2(trim(leitura[3]), ',');
		vector<string> leituraAutores = tok2.remaining();

		if (achouVeiculo) {
			if (veiculo->getTipo() == 'C') {

				local = trim(leitura[6]);

				vector<Docente*> d;
				Conferencia* conf = new Conferencia(local, ano, pagInic, pagFim,
						titulo, veiculo, d, num);
				publicacoes->push_back(conf);

				//PASSA EM TODOS OS AUTORES DA PUBLICACAO
				for (unsigned int i = 0; i < leituraAutores.size(); i++) {

					achou = false;
					if (isNumber(trim(leituraAutores[i]))) {
						codigo = trim(leituraAutores[i]);
					} else {
						throw Execoes("Erro de formatação");
					}

					//ACHA O DOCENTE E LINKA
					vector<Docente*>::iterator d = docentes->begin();
					while (d != docentes->end()) {
						Docente *d2 = *d;
						string codigoD = d2->getCodigo();

						if (!codigoD.compare(codigo)) {
							d2->linkaPublicacaoEmDocente(conf);
							achou = true;
							break;
						}
						d++;
					}

					if (!achou) {
						throw Execoes(
								"Código de docente não definido usado na publicação \""
										+ titulo + "\": " + codigo + ".");
					}

				}

				veiculo->linkaPublicacaoEmVeiculo(conf);

			} else if (veiculo->getTipo() == 'P') {


				volume = atoi(trim(leitura[5]).c_str());

				vector<Docente*> d;
				Periodico* periodico = new Periodico(volume, ano, pagInic,
						pagFim, titulo, veiculo, d, num);

				publicacoes->push_back(periodico);

				for (unsigned int i = 0; i < leituraAutores.size(); i++) {
					achou = false;
					if (isNumber(trim(leituraAutores[i]))) {
						codigo = trim(leituraAutores[i]);
					} else {
						throw Execoes("Erro de formatação");
					}

					//ACHA O DOCENTE E LINKA
					vector<Docente*>::iterator d = docentes->begin();
					while (d != docentes->end()) {
						Docente *d2 = *d;
						string codigoD = d2->getCodigo();

						if (!codigoD.compare(codigo)) {
							d2->linkaPublicacaoEmDocente(periodico);
							achou = true;
							break;
						}
						d++;
					}

					if (!achou) {
						throw Execoes(
								"Código de docente não definido usado na publicação \""
										+ titulo + "\": " + codigo + ".");
					}

				}

				veiculo->linkaPublicacaoEmVeiculo(periodico);
			}
		} else {
			throw Execoes(
					"Sigla de veículo não definida usada na publicação \""
							+ trim(leitura[2]) + "\": " + trim(leitura[1])
							+ ".");
		}
	}
}

void LeiaCSV::lerRegras(vector<Regra*> *regras,
		vector<Qualificacao*> *qualificacoes, vector<Pontuacao*> *pontuacoes,
		vector<Qualis*> *listaQualis, int ano, char* diretorio) {

	time_t data;
	time_t dataInic;
	time_t dataFim;
	double multPeriodico = 0;
	int qtdAnos;
	int pontMin;
	Pontuacao* pontuacao;
	vector<Qualis*> qualis;

	string nomeData = "02/01/";
	stringstream conversor;
	conversor << ano;
	nomeData.append(conversor.str());

	// TRATAR ERRO - DATA
	if (!validDate(trim(nomeData), DATE_FORMAT_PT_BR_SHORT)) {
		throw Execoes("Erro de formatação");
	} else {
		data = parseDate(nomeData, DATE_FORMAT_PT_BR_SHORT);
	}

	//ABRE ARQUIVO
	ifstream in(diretorio);

	//TRATAR ERRO - I/O
	if (!in.is_open()) {
		throw Execoes("Erro de I/O");
	}
	string linha = "";

	//LE ARQUIVO
	getline(in, linha);
	while (getline(in, linha)) {

		//SEPARA A LINHA EM UM VECTOR DE STRINGS
		Tokenizer tok(linha, ';');
		vector<string> leitura = tok.remaining();

		//FAZER TRATAMENTO DE EXCEPTION

		if (!validDate(trim(leitura[0]), DATE_FORMAT_PT_BR_SHORT)
				|| !validDate(trim(leitura[1]), DATE_FORMAT_PT_BR_SHORT)) {
			throw Execoes("Erro de formatação");
		} else {
			dataInic = parseDate(trim(leitura[0]), DATE_FORMAT_PT_BR_SHORT);
			dataFim = parseDate(trim(leitura[1]), DATE_FORMAT_PT_BR_SHORT);
		}

		if (difftime(dataFim, data) && difftime(data, dataInic)) {

			if (isNumber(trim(leitura[5])) || isNumber(trim(leitura[6]))) {
				qtdAnos = atoi(trim(leitura[5]).c_str());
				pontMin = atoi(trim(leitura[6]).c_str());
			} else {
				throw Execoes("Erro de formatação");
			}

			//SEPARA A LEITURAQUALIS EM UM VECTOR DE STRINGS DE QUALIS
			Tokenizer tok2(trim(leitura[2]), ',');
			vector<string> leituraQualis = tok2.remaining();

			//SEPARA A LEITURAQUALIS EM UM VECTOR DE STRINGS DE QUALIS
			Tokenizer tok3(trim(leitura[3]), ',');
			vector<string> leituraPontos = tok3.remaining();

			for (unsigned int i = 0; i < leituraPontos.size(); i++) {

				if (!isNumber(leituraPontos[i])) {
					throw Execoes("Erro de formatação");
				}
				if (!ehQualisValido(leituraQualis[i])) {

					throw Execoes(
							"Qualis desconhecido para regras de "
									+ trim(leitura[0]) + ": "
									+ leituraQualis[i]);
				}
			}

			//LINKA PONTUACAO E QUALIS
			for (unsigned int i = 0; i < leituraPontos.size(); i++) {
				vector<Qualis*> qualis2;
				if (i < leituraPontos.size() - 1) {
					vector<Qualis*>::iterator q = listaQualis->begin();
					while (q != listaQualis->end()) {
						Qualis *q2 = *q;
						string nome = q2->getNome();
						if ((trim(leituraQualis[i]).compare(nome) < 0
								|| (trim(leituraQualis[i]).compare(nome)) == 0)
								&& trim(leituraQualis[i + 1]).compare(nome)
										> 0) {
							qualis2.push_back(q2);
						}
						q++;
					}
				} else {
					vector<Qualis*>::iterator q = listaQualis->begin();
					while (q != listaQualis->end()) {
						Qualis *q2 = *q;
						if (!q2->getNome().compare(trim(leituraQualis[i]))) {
							qualis2.push_back(q2);
						}
						q++;
					}
				}
				Regra *regraaux = NULL;
				Qualis *qualisAux = NULL;

				vector<Qualis*>::iterator q = qualis2.begin();
				while (q != qualis2.end()) {
					Qualis* q2 = *q;
					pontuacao = new Pontuacao(
							atoi(trim(leituraPontos[i]).c_str()), qualisAux,
							regraaux);
					pontuacao->linkaQualisEmPontuacao(q2);
					pontuacoes->push_back(pontuacao);
					q++;
				}
				qualis2.clear();
			}

			//TRATA ERRO - PARSE
			if (isNumber(trim(leitura[4]))) {
				multPeriodico = parseDouble(trim(leitura[4]), LOCALE_PT_BR);
			} else {
				throw Execoes("Erro ao Converter Multiplicador Periodico");
			}

			//LINKA PONTUACAO E REGRA
			if (difftime(dataInic, data) < 0 && difftime(dataFim, data) > 0) {
				Regra *regra = new Regra(dataInic, dataFim, multPeriodico,
						qtdAnos, pontMin, *pontuacoes);
				regra->linkaPontuacoesEmRegra(*pontuacoes);
				regras->push_back(regra);
			}
		}
	}

}

bool LeiaCSV::ehQualisValido(string s) {
	if (!s.compare("A1") || !s.compare("A2") || !s.compare("B1")
			|| !s.compare("B2") || !s.compare("B3") || !s.compare("B4")
			|| !s.compare("B5") || !s.compare("C")) {
		return true;
	}
	return false;
}

