#pragma once
#pragma once
#include "Carro.h"
#include "Mecanico.h"

struct Arvore {
    Carro* carros_reparados = new Carro;
    struct Arvore* esquerda, * direita;
};
Arvore* novoNodo(Carro* item);
void insert(Arvore* nodo, Carro* chave);
void adicionarar(Arvore* raiz, Carro* chave);
int numeroniveis(Arvore* raiz);
void imprimirarvore(Arvore* root, int niveis);