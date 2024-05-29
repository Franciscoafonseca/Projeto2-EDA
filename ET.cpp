#include "ET.h"

EstacaoTrabalho * CriarET(int numeroETs,LinhasFicheiro& marcas) {
	EstacaoTrabalho* primeiraET = new EstacaoTrabalho;
	primeiraET->mecanico = CriarMecanico(marcas);
	primeiraET->capacidade = 2 + (rand() % 3);
	primeiraET->faturacao = 0;
	primeiraET->ID = 1;
	primeiraET->Carrosreparados = new Arvore;
	primeiraET->carros_a_ser_reparados = new Carro;
	primeiraET->num_carros_a_ser_reparados = 0;
	primeiraET->num_carros_reparados = 0;
	primeiraET->seguinte = NULL;
	EstacaoTrabalho* ETauxiliar = primeiraET;
	for (int i = 1; i < numeroETs; i++) {
		EstacaoTrabalho* novo = new EstacaoTrabalho;
		novo->mecanico = CriarMecanico(marcas);
		novo->capacidade = 2 + (rand() % 3);
		novo->faturacao = 0;
		novo->ID = i + 1;
		novo->Carrosreparados = new Arvore;
		novo->carros_a_ser_reparados = new Carro;
		novo->num_carros_a_ser_reparados = 0;
		novo->num_carros_reparados = 0;
		ETauxiliar->seguinte = novo;
		ETauxiliar = ETauxiliar->seguinte;
		if (i == numeroETs - 1)
			novo->seguinte = NULL;
		
	}
	return primeiraET;
}


void reparacao(EstacaoTrabalho *& ET) {
	bool reparar = false;
	EstacaoTrabalho* primeiraET = ET;
	EstacaoTrabalho* percorrerET = primeiraET;
	
	while (percorrerET != NULL) {
		if (percorrerET->num_carros_a_ser_reparados> 0) {
			EstacaoTrabalho* auxET = percorrerET;
			Carro* primeirocarroaserreparado = percorrerET->carros_a_ser_reparados;
			Carro* percorreraserreparados = primeirocarroaserreparado;
			int n = percorrerET->num_carros_a_ser_reparados;
			for (int i = 0; i < n; i ++) {
				reparar = GerarProbalidades(0.15);
				Carro* aux = percorreraserreparados;
				if (aux != NULL && aux->ID != 0 && aux->dias_em_reparacao < aux->tempo_reparacao_max) {
					if ((reparar) && aux->dias_em_reparacao > 0) {

						aux->custoreparacao = aux->dias_em_reparacao * auxET->mecanico.preco_reparacao_por_dia;
						adicionarar(ET->Carrosreparados, aux);
						auxET->num_carros_a_ser_reparados = auxET->num_carros_a_ser_reparados - 1;
						aux->ID = 0;
						auxET->faturacao = auxET->faturacao + aux->dias_em_reparacao * auxET->mecanico.preco_reparacao_por_dia;

						auxET->num_carros_reparados = auxET->num_carros_reparados;
					}
					else {
						aux->dias_em_reparacao = aux->dias_em_reparacao + 1;
					}
				}
				else if (aux != NULL && aux->dias_em_reparacao >= aux->tempo_reparacao_max) {
					aux->custoreparacao = aux->dias_em_reparacao * auxET->mecanico.preco_reparacao_por_dia;
					adicionarar(ET->Carrosreparados, aux);
					auxET->num_carros_a_ser_reparados = auxET->num_carros_a_ser_reparados - 1;
					aux->ID = 0;
					auxET->faturacao = auxET->faturacao + aux->dias_em_reparacao * auxET->mecanico.preco_reparacao_por_dia;
					auxET->num_carros_reparados = auxET->num_carros_reparados;
				}
				percorreraserreparados = percorreraserreparados->seguinte;
			}
		}
			percorrerET = percorrerET->seguinte;
		
	}
		ET = primeiraET;
	
}

