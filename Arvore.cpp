#include "Arvore.h"


Arvore* novoNodo(Carro* item){

    Arvore* temp = new Arvore();
    Carro* temp2 = item;
    temp->carros_reparados = temp2;
    temp->esquerda = temp->direita = NULL;
    return temp;
}
void insert(Arvore* nodo, Carro* chave)
{
    Arvore* primeironodo = nodo;
    Arvore* aux = primeironodo;
    Arvore* nova = novoNodo(chave);
    while (aux != NULL) {
        if (chave->modelo > aux->carros_reparados->modelo || chave->modelo == aux->carros_reparados->modelo) {
            if (aux->direita == NULL) {
                aux->direita = nova;
                break;
            }
            else {
                aux = aux->direita;
            }
        }
        else if (chave->modelo < aux->carros_reparados->modelo) {
            if (aux->esquerda == NULL) {
                aux->esquerda = nova;
                break;
            }
            else {
                aux = aux->esquerda;
            }
        }
    }
    nodo = primeironodo;
}

void adicionarar(Arvore* raiz, Carro* chave) {
    if (raiz->carros_reparados->ID == 0) {
        raiz->carros_reparados = chave;
        raiz->direita = NULL;
        raiz->esquerda = NULL;
    }
    else {
        insert(raiz, chave);
    }
}

int numeroniveis(Arvore* raiz){
    int h = 0;
    if (raiz != NULL )
    {
        if (raiz->carros_reparados->ID != 0) {
            int alturaesq = numeroniveis(raiz->esquerda);
            int alturadir = numeroniveis(raiz->direita);
            int alturamax = max(alturaesq, alturadir);
            h = alturamax + 1;
        }
    }
    return h;
}

void imprimirarvore(Arvore* no, int nivel) {
	if (no == NULL || no->carros_reparados->ID == 0){
		cout << endl;
		return;
	}
	imprimirarvore(no->direita, nivel + 1);
	for (int i = 1; i < nivel; i++)
	{
		cout << "\t";
	}
	cout << no->carros_reparados->ID << endl;
	imprimirarvore(no->esquerda, nivel + 1);
}


