#include "Gestao.h"

void MenuInfo(Oficina& Of) {
	cout << "Dia: " << Of.ciclos << endl;
	EstacaoTrabalho* percorrerETS = Of.ets;
	while (percorrerETS != NULL) {
		cout << "ET: " << percorrerETS->ID << " | " << "Mecanico: " << percorrerETS->mecanico.nome
			<< " | " << "Capacidade: " << percorrerETS->capacidade << " | " << "Carros: " << percorrerETS->num_carros_a_ser_reparados << " | " <<
			"Marca: " << percorrerETS->mecanico.marca << " | " << "Total Faturacao: " << percorrerETS->faturacao << endl;
		if (Of.ciclos >= 1) {
			cout << "Carros a ser reparados: " << endl;
		}
		Carro* percorrercarrosaserreparados = percorrerETS->carros_a_ser_reparados;
		if (percorrerETS->num_carros_a_ser_reparados > 0) {
			for (int i = 0; i < percorrerETS->capacidade; i ++) {
				if ((Of.ciclos >= 1) && (percorrercarrosaserreparados->ID != 0)) {
					cout << "ID: " << percorrercarrosaserreparados->ID << " | " << "Carro: " << percorrercarrosaserreparados->marca << "-"
						<< percorrercarrosaserreparados->modelo << " | " << "Prioritario: ";
					if (percorrercarrosaserreparados->prioritario == 1) {
						cout << "Sim";
					}
					else {
						cout << "Nao";
					}
					cout << " | " << "Tempo de reparacao: " << percorrercarrosaserreparados->dias_em_reparacao << " | " << "Tempo de reparacao maximo: ";
					cout << percorrercarrosaserreparados->tempo_reparacao_max << endl;
				}
				percorrercarrosaserreparados = percorrercarrosaserreparados->seguinte;
			}
		}
		cout << endl;
		percorrerETS = percorrerETS->seguinte;

	}
	cout << "--------------------------------------------------------------------------------------" << endl;
	cout << "Lista de Espera: " << endl;
	Carro * percorrerlistaespera = Of.listaespera;
	while (percorrerlistaespera!=NULL) {
		if (percorrerlistaespera != NULL && percorrerlistaespera->ID != 0) {
			cout << "ID: " << percorrerlistaespera->ID << " | " << "Modelo: " << percorrerlistaespera->modelo << " | " << "Marca: " << percorrerlistaespera->marca << " | "
				<< "Prioritario: ";
			if (percorrerlistaespera->prioritario == 1) {
				cout << "Sim";
			}
			else {
				cout << "Nao";
			}
			cout << " | " << "Tempo de reparacao maximo: " << percorrerlistaespera->tempo_reparacao_max << endl;
		}
		percorrerlistaespera = percorrerlistaespera->seguinte;
	}
	cout << endl;
	
}

void seguinte(Oficina& Of, LinhasFicheiro& marcas, LinhasFicheiro& modelos) {
	Of.ciclos++;
	Carro* cauda = Of.listaespera;
	while (cauda->seguinte != NULL) {
		cauda = cauda->seguinte;
	}
	Of.listaespera->seguinte = CriarCarrosNaFila(Of, marcas, modelos, 10);
	organizarprioritario(Of.listaespera);
	if (Of.ciclos > 1)
		reparacao(Of.ets);
	ColocarCarrosET(Of, 8);
	MenuInfo(Of);
}


void Menu(Oficina& Of, LinhasFicheiro& marcas, LinhasFicheiro& modelos) {
	string escolha;
	bool sair = false;
	do {
		cout << "Dia (s)eguinte *********** (g)estao" << endl << "(T)erminar programa" << endl;

		cout << "Seleccione a sua opcao : " << endl;
		getline(cin, escolha);
		while (escolha.length() != 1) {
			cout << "Escolha invalida! Digite apenas uma das letras destacadas abaixo." << endl;
			cout << "Dia (s)eguinte *********** (g)estao" << endl << "(T)erminar programa" << endl;

			cout << "Seleccione a sua opcao : " << endl;
			getline(cin, escolha);
			cout << endl;
		}

		switch (escolha[0]) {
		case 's':
		case 'S':
			seguinte(Of, marcas, modelos);
			MenuInfo(Of);
			Menu(Of, marcas, modelos);
			sair = true;
			break;
		case 'g':
		case 'G':
			gestao(Of, marcas, modelos);
			sair = true;
			break;
		case 't':
		case 'T':
			sair = true;
			break;

		default:
			cout << "Opcao invalida" << endl;
			break;

		}
	} while (!sair);

}


void gestao(Oficina& Of, LinhasFicheiro& marcas, LinhasFicheiro& modelos) {
	int opcao;
	string escolha1temp;
	double escolha1temporaria = 0;
	int escolha = 0;
	string escolha2temp;
	double escolha2temporaria = 0;
	int escolha2 = 0;
	string caminho = "oficina.txt";
	bool sair = false;
	do {
		cout << " ***** Bem Vindo Gestor *****" << endl;
		cout << "(1).Atualizar Tempo de reparacao" << endl;
		cout << "(2).Adicionar Prioridade" << endl;
		cout << "(3).Remover Mecanico" << endl;
		cout << "(4).Gravar Oficina" << endl;
		cout << "(5).Carregar Oficina" << endl;
		cout << "(6).Adicionar ET" << endl;
		cout << "(7).Imprimir Carros reparados" << endl;
		cout << "(8).Sair da gestao" << endl;
		cout << "Seleccione a sua opcao : ";
		cin >> opcao;

		switch (opcao) {

		case 1:
			atualizar_tempo_reparacao(Of);
			system("CLS");
			MenuInfo(Of);
			Menu(Of, marcas, modelos);
			sair = true;
			break;

		case 2:
			adicionar_prioridade(Of);
			system("CLS");
			MenuInfo(Of);
			Menu(Of, marcas, modelos);
			sair = true;
			break;

		case 3:
			remover_mecanico(Of, marcas);
			system("CLS");
			MenuInfo(Of);
			Menu(Of, marcas, modelos);
			sair = true;
			break;

		case 4:
			gravar_oficina(Of);
			system("CLS");
			MenuInfo(Of);
			Menu(Of, marcas, modelos);
			sair = true;
			break;

		case 5:
			while ((escolha2temporaria > 2) || (escolha2temporaria <= 0)) {
				cout << "Digite: " << endl << "(1) Escolher o caminho manualmente" << endl << "(2) Usar o caminho padrao (Oficina.txt)" << endl;
				cin >> ws;
				getline(cin, escolha2temp);
				while (!verificarnumero(escolha2temp)) {
					cout << "Opcao invalida! Tente novamente" << endl;;
					cout << "Digite: " << endl << "(1) Escolher o caminho manualmente" << endl << "(2) Usar o caminho padrao (Oficina.txt)" << endl;
					getline(cin, escolha2temp);
				}
				escolha2temporaria = stod(escolha2temp);
				if ((escolha2temporaria > 2) || (escolha2temporaria <= 0)) {
					escolha2temporaria = 0;
				}
				else {
					escolha2 = (int)escolha2temporaria;
				}
			}
			switch (escolha2) {

			case 1:
				cout << "Digite o caminho (inclua .txt ao fim do nome do arquivo): " << endl;
				cin >> caminho;
				break;
			case 2:
				break;
			default:
				cout << "Opcao invalida" << endl << "Imprimindo usando o caminho padrao..." << endl;
				break;
			}

			//carregar_oficina(Of, caminho);
			system("CLS");
			MenuInfo(Of);
			Menu(Of, marcas, modelos);
			sair = true;
			break;

		case 6:
			adicionar_ET(Of, marcas, modelos);
			system("CLS");
			MenuInfo(Of);
			Menu(Of, marcas, modelos);
			sair = true;
			break;

		case 7:
			while ((escolha1temporaria > 2) || (escolha1temporaria <= 0)) {
				cout << "Digite: " << endl << "(1) Imprimir por ordem alfabetica" << endl << "(2) imprimir por representacao" << endl;
				cin >> ws;
				getline(cin, escolha1temp);
				while (!verificarnumero(escolha1temp)) {
					cout << "Opcao invalida! Tente novamente" << endl;;
					cout << "Digite: " << endl << "(1) Imprimir por ordem alfabetica" << endl << "(2) imprimir por representacao" << endl;
					getline(cin, escolha1temp);
				}
				escolha1temporaria = stod(escolha1temp);
			}
			escolha = (int)escolha1temporaria;
			switch (escolha) {
			case 1:

				break;
			case 2:
				imprimiroficinaporrerpresentacao(Of);
			}
			MenuInfo(Of);
			Menu(Of, marcas, modelos);
			sair = true;
			break;
		case 8:
			Menu(Of, marcas, modelos);
			sair = true;

			break;

		default:
			cout << "Opcao invalida" << endl;
			break;
			
		}
	}while (!sair);
}


void atualizar_tempo_reparacao(Oficina& Of) {

	string marca;
	string modelo;
	string entrada;
	double tempotemp = 0;
	int tempo;
	cout << "indique a marca a atualizar o tempo de reparacao: " << endl;
	cin >> ws;
	getline(cin, marca);
	cout << "indique o modelo a atualizar o tempo de reparacao: " << endl;
	cin >> ws;
	getline(cin, modelo);
	cout << "Introduza o respetivo tempo: \n ";
	getline(cin, entrada);	
	while ((tempotemp > INT_MAX) || (tempotemp <= 0)) {
		while (!verificarnumero(entrada)) {
			cout << "Tempo invalido!" << endl << "introduza um tempo de reparacao valido (inteiro entre 0 e 2147483647): " << endl;
			getline(cin, entrada);
		}
		tempotemp = stod(entrada);
		if ((tempotemp <= INT_MAX) && (tempotemp > 0)) {
			tempo = (int)tempotemp;

		}
		else {
			cout << "Tempo invalido!" << endl << "introduza um tempo de reparacao valido (inteiro entre 0 e 2147483647): " << endl;
			getline(cin, entrada);
			tempotemp = 0;
		}
	}
	//percorrer lista de espera
	Carro* primeiroespera = Of.listaespera;
	Carro* atual = primeiroespera;
	while (atual != NULL) {
		if (removerespacos((maiuscula(atual->marca))) == removerespacos(maiuscula(marca)) && (removerespacos(maiuscula(atual->modelo)) == removerespacos(maiuscula(modelo)))) {
			atual->tempo_reparacao_max = tempo;

		}
		atual = atual->seguinte;
	}
}

void adicionar_prioridade(Oficina& Of) {
	string entrada;
	double Idtemp = 0;
	int Id;
	cout << "Indique O ID do carro que quer por a Prioritario: " << endl;
	cin >> ws;
	getline(cin, entrada);
	while ((Idtemp > INT_MAX) || (Idtemp <= 0)) {
		while (!verificarnumero(entrada)) {
			cout << "ID invalido!" << endl << "Indique um ID valido para colocar como prioritario (inteiro): " << endl;
			getline(cin, entrada);
		}
		Idtemp = stod(entrada);
		if ((Idtemp <= INT_MAX) && (Idtemp > 0)) {
			Id = (int)Idtemp;

		}
		else {
			cout << "ID invalido!" << endl << "Indique um ID valido para colocar como prioritario (inteiro entre 0 e 2147483647): " << endl;
			getline(cin, entrada);
			Idtemp = 0;
		}
	}
	//percorrer lista de espera2
	Carro* primeiroCarro = Of.listaespera;
	Carro* atual = primeiroCarro;
	while (atual != NULL) {
		//faz se id for igual e se n for prioritario
		if ((atual->ID == Id) && (atual->prioritario == false)) {
			atual->prioritario = true;
		}

		atual = atual->seguinte;
	}

	organizarprioritario(Of.listaespera);
}


void remover_mecanico(Oficina& Of, LinhasFicheiro& marcas) {
	string mecanicoRem;
	string mecanicoAdi;
	cout << "Indique o nome do mecanico que deseja remover: " << endl;
	cin >> ws;
	getline(cin, mecanicoRem);
	EstacaoTrabalho* primeiraET = Of.ets;
	EstacaoTrabalho* atualET = primeiraET;
	while (atualET != NULL) {
		if (removerespacos(maiuscula(atualET->mecanico.nome)) == removerespacos(maiuscula(mecanicoRem))) {
			break;
		}
		else {
			atualET = atualET->seguinte;
		}
	}
	if (atualET == NULL) {
		cout << "Nao existe nenhuma ET com esse mecanico!" << endl;
		return;
	}
	//Reparar todos os carros
	Carro* primeirocarro = atualET->carros_a_ser_reparados;
	Carro* percorrerlistacarros = primeirocarro;
	int n = atualET->num_carros_a_ser_reparados;
	for (int i = 0; i < n; i++) {
		if (percorrerlistacarros->ID != 0) {
			percorrerlistacarros->custoreparacao = percorrerlistacarros->dias_em_reparacao * atualET->mecanico.preco_reparacao_por_dia;
			//inserir arvore
			atualET->num_carros_a_ser_reparados = atualET->num_carros_a_ser_reparados - 1;
			percorrerlistacarros->ID = 0;
			atualET->faturacao = atualET->faturacao + percorrerlistacarros->custoreparacao;
			atualET->num_carros_reparados = atualET->num_carros_reparados + 1;
		}
	}
			//adicionar novo mecanico
			cout << "O mecanico com o nome " << mecanicoRem << ", foi removido da et" << endl;
			cout << "ET: " << atualET->ID << " | " << "Mecanico: " << atualET->mecanico.nome
				<< " | " << "Capacidade: " << atualET->capacidade << " | " <<
				"Marca: " << atualET->mecanico.marca << " | " << "Total Faturacao: " << atualET->faturacao << endl;
			cout << endl;

			//remover a ET antiga e criar uma nova ou algo semelhante
			EstacaoTrabalho*temp = CriarET(1,marcas);
			atualET->ID = atualET->ID;
			atualET->capacidade = temp->capacidade;
			atualET->Carrosreparados = temp->Carrosreparados;
			atualET->carros_a_ser_reparados = temp->carros_a_ser_reparados;
			atualET->faturacao = temp->faturacao;
			atualET->mecanico = temp->mecanico;
			atualET->num_carros_a_ser_reparados = temp->num_carros_a_ser_reparados;
			atualET->num_carros_reparados = temp->num_carros_reparados;
			Carro* primeirocarroaux = atualET->carros_a_ser_reparados;
			Carro* atualcarro = primeirocarroaux;
			for (int i = 0; i < atualET->capacidade - 1; i++) {
				atualcarro->seguinte = new Carro;
				atualcarro = atualcarro->seguinte;
			}
		}
	
void imprimiroficinaporrerpresentacao(Oficina & of) {
	double IDtemp = 0;
	int ID = 0;
	while (IDtemp > of.numero_ets || IDtemp <= 0) {
		cout << "Insira um ID da ET: " << endl;
		cin >> IDtemp;
	}
	ID = int(IDtemp);
	EstacaoTrabalho* primeiraET = of.ets;
	EstacaoTrabalho* percorrerET = primeiraET;
	while (percorrerET != NULL) {
		if (percorrerET->ID == ID) {
			cout << "Marca: " << endl;
			imprimirarvore(percorrerET->Carrosreparados, numeroniveis(percorrerET->Carrosreparados));
			return;
		}
	}
	cout << "Ocorreu algum erro. Tente novamente!" << endl;
}
void adicionar_ET(Oficina& of, LinhasFicheiro& marcas, LinhasFicheiro& modelos) {
	EstacaoTrabalho* primeiraet = of.ets;
	EstacaoTrabalho* percorreret = primeiraet;
	while (percorreret->seguinte != NULL) {
		percorreret = percorreret->seguinte;
	}
	percorreret->seguinte = CriarET(1, marcas);
	percorreret = percorreret->seguinte;
	percorreret->ID = of.numero_ets + 1;
	Carro* primeirocarro = percorreret->carros_a_ser_reparados;
	Carro* percorrercarro = primeirocarro;
	for (int i = 0; i < percorreret->capacidade - 1; i++) {
		percorrercarro->seguinte = new Carro;
		percorrercarro = percorrercarro->seguinte;
	}

	of.ets = primeiraet;
	of.numero_ets = of.numero_ets + 1;
}

void gravar_oficina(const Oficina& oficina) {
	string caminho = "oficina.txt";
	ofstream ficheiro(caminho);

	if (ficheiro.is_open()) {
		// Gravação dos dados da oficina
		ficheiro << oficina.ciclos << "|"
			<< oficina.carrostotais << "|"
			<< oficina.numero_ets << "\n";

		// Gravação dos dados de cada EstacaoTrabalho
		EstacaoTrabalho* atualET = oficina.ets;
		while (atualET != nullptr) {
			ficheiro << atualET->ID << "|"
				<< atualET->capacidade << "|"
				<< atualET->faturacao << "|"
				<< atualET->num_carros_a_ser_reparados << "|"
				<< atualET->num_carros_reparados << "\n";

			// Gravação dos carros a ser reparados
			Carro* atualcarrosaserreparados = atualET->carros_a_ser_reparados;
			while (atualcarrosaserreparados != nullptr) {
				ficheiro << atualcarrosaserreparados->dias_em_reparacao << "|"
					<< atualcarrosaserreparados->ID << "|"
					<< atualcarrosaserreparados->marca << "|"
					<< atualcarrosaserreparados->modelo << "|"
					<< atualcarrosaserreparados->prioritario << "|"
					<< atualcarrosaserreparados->tempo_reparacao_max << "\n";
				atualcarrosaserreparados = atualcarrosaserreparados->seguinte;
			}

			// Gravação dos dados do mecânico 
			ficheiro << atualET->mecanico.marca << "|"
				<< atualET->mecanico.nome << "|"
				<< atualET->mecanico.preco_reparacao_por_dia << "\n";

			atualET = atualET->seguinte;
		}

		// Gravação dos dados da fila de espera
		ficheiro << oficina.fila_espera_tamanho << "\n";
		Carro* atualFilaEspera = oficina.listaespera;
		while (atualFilaEspera != nullptr) {
			ficheiro << atualFilaEspera->ID << "|"
				<< atualFilaEspera->dias_em_reparacao << "|"
				<< atualFilaEspera->marca << "|"
				<< atualFilaEspera->modelo << "|"
				<< atualFilaEspera->prioritario << "|"
				<< atualFilaEspera->tempo_reparacao_max << "\n";
			atualFilaEspera = atualFilaEspera->seguinte;
		}

		ficheiro.close();
	}
	else {
		cout << "Erro ao abrir o arquivo" << endl;
	}
}
void carregar_oficina(Oficina& Of, string& caminho) {
	ifstream ficheiro(caminho);

	if (ficheiro.is_open()) {
		Oficina nova;
		string linha;

		getline(ficheiro, linha);
		stringstream ss(linha);
		string temp;

		// Obtém ciclos
		getline(ss, temp, '|');
		nova.ciclos = stoi(temp);

		// Obtém carrostotais
		getline(ss, temp, '|');
		nova.carrostotais = stoi(temp);

		// Obtém numero_ets
		getline(ss, temp, '|');
		nova.numero_ets = stoi(temp);

		// Cria as Estacoes de Trabalho
		nova.ets = nullptr;
		EstacaoTrabalho* atualET = nullptr;
		for (int i = 0; i < nova.numero_ets; i++) {
			getline(ficheiro, linha);
			stringstream ss(linha);

			// Obtém ID
			getline(ss, temp, '|');
			int id = stoi(temp);

			// Obtém capacidade
			getline(ss, temp, '|');
			int capacidade = stoi(temp);

			// Obtém faturacao
			getline(ss, temp, '|');
			float faturacao = stof(temp);

			// Obtém num carros a ser reparados
			getline(ss, temp, '|');
			int carros_a_reparar = stoi(temp);

			// Obtém carros reparados
			getline(ss, temp, '|');
			int carros_reparados = stoi(temp);

			EstacaoTrabalho* novaET = new EstacaoTrabalho;
			if (nova.ets == nullptr) {
				nova.ets = novaET;
				atualET = nova.ets;
			}
			else {
				atualET->seguinte = novaET;
				atualET = atualET->seguinte;
			}
		}

		atualET = nova.ets;
		while (atualET != nullptr) {
			getline(ficheiro, linha);
			stringstream ss(linha);

			// Obtém Mecânico
			Mecanico mecanico;

			// Obtém marca
			getline(ss, temp, '|');
			mecanico.marca = temp;

			// Obtém nome do mecânico
			getline(ss, temp, '|');
			mecanico.nome = temp;

			// Obtém preço de reparação por dia
			getline(ss, temp, '|');
			mecanico.preco_reparacao_por_dia = stoi(temp);

			atualET->mecanico = mecanico;

			atualET = atualET->seguinte;
		}

		// Carrega carros a serem reparados
		atualET = nova.ets;
		while (atualET != nullptr) {
			int capacidade = atualET->capacidade;
			atualET->carros_a_ser_reparados = nullptr;
			Carro* atualcarrosaserreparados = nullptr;
			for (int i = 0; i < capacidade; i++) {
				getline(ficheiro, linha);
				stringstream ss(linha);

				// Obtém dias em reparação
				getline(ss, temp, '|');
				int dias_em_reparacao = stoi(temp);

				// Obtém ID do carro em reparação
				getline(ss, temp, '|');
				int ID = stoi(temp);

				// Obtém marca
				getline(ss, temp, '|');
				string marca = temp;

				// Obtém modelo
				getline(ss, temp, '|');
				string modelo = temp;

				// Obtém prioridade
				getline(ss, temp, '|');
				int prioridade = stoi(temp);

				// Obtém tempo de reparação máximo
				getline(ss, temp, '|');
				int tempo_reparacao_max = stoi(temp);

				Carro* novoCarro = new Carro;
				if (atualET->carros_a_ser_reparados == nullptr) {
					atualET->carros_a_ser_reparados = novoCarro;
					atualcarrosaserreparados = atualET->carros_a_ser_reparados;
				}
				else {
					atualcarrosaserreparados->seguinte = novoCarro;
					atualcarrosaserreparados = atualcarrosaserreparados->seguinte;
				}
			}
			atualET = atualET->seguinte;
		}

		// Carrega carros reparados
		atualET = nova.ets;
		while (atualET != nullptr) {
			int num_carros_reparados = atualET->num_carros_reparados;
			atualET->Carrosreparados = nullptr;
			Arvore* atualcarrosreparados = nullptr;
			for (int i = 0; i < num_carros_reparados; i++) {
				getline(ficheiro, linha);
				stringstream ss(linha);

				// Obtém ID
				getline(ss, temp, '|');
				int ID = stoi(temp);

				// Obtém dias_em_reparacao
				getline(ss, temp, '|');
				int dias_em_reparacao = stoi(temp);

				// Obtém marca
				getline(ss, temp, '|');
				string marca = temp;

				// Obtém modelo
				getline(ss, temp, '|');
				string modelo = temp;

				// Obtém prioridade
				getline(ss, temp, '|');
				int prioridade = stoi(temp);

				// Obtém tempo_reparacao_max
				getline(ss, temp, '|');
				int tempo_reparacao_max = stoi(temp);

				Arvore* novoCarro = new Arvore;
				if (atualET->Carrosreparados == nullptr) {
					atualET->Carrosreparados = novoCarro;
					atualcarrosreparados = atualET->Carrosreparados;
				}
				else {
					atualcarrosreparados->esquerda = novoCarro;
					atualcarrosreparados = atualcarrosreparados->esquerda;
				}
			}
			atualET = atualET->seguinte;
		}

		// Carrega fila de espera
		getline(ficheiro, linha);
		
		getline(ss, temp, '|');
		int fila_espera_tamanho = stoi(temp);

		nova.listaespera = nullptr;
		Carro* atualfilaespera = nullptr;
		for (int i = 0; i < fila_espera_tamanho; i++) {
			getline(ficheiro, linha);
			stringstream ss(linha);

			// Obtém ID
			getline(ss, temp, '|');
			int ID = stoi(temp);

			// Obtém dias_em_reparacao
			getline(ss, temp, '|');
			int dias_em_reparacao = stoi(temp);

			// Obtém marca
			getline(ss, temp, '|');
			string marca = temp;

			// Obtém modelo
			getline(ss, temp, '|');
			string modelo = temp;

			// Obtém prioridade
			getline(ss, temp, '|');
			int prioridade = stoi(temp);

			// Obtém tempo_reparacao_max
			getline(ss, temp, '|');
			int tempo_reparacao_max = stoi(temp);

			Carro* novoCarro = new Carro;
			if (nova.listaespera == nullptr) {
				nova.listaespera = novoCarro;
				atualfilaespera = nova.listaespera;
			}
			else {
				atualfilaespera->seguinte = novoCarro;
				atualfilaespera = atualfilaespera->seguinte;
			}
		}

		Of = nova;
		ficheiro.close();
		cout << "Oficina carregada com sucesso!" << endl;
	}
	else {
		cout << "Erro: Não foi possível abrir o arquivo de carregamento!" << endl;
	}
}

