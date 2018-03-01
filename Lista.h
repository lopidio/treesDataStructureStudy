#ifndef LISTA_H
#define LISTA_H
#include "PrinterHash.h"
#include <stdio.h>


struct Elemento //Nós da lista
{
        Elemento(Elemento* prox_, int valor_)
        {
                prox = prox_;
                valor = valor_;
        }
        Elemento* prox; //Ponteiro para o próximo nó
        int valor; //Valor do nó
};

class Lista
{
        public:
                Lista(); //Construtor
                ~Lista(); //Destrutor
                bool inserir(int); //
                bool remover(int);
                bool buscar(int);
                void imprimir()
                {
                        Elemento* atual = cabeca;
                        while (atual)
                        {
                                printf("%d  ", atual->valor);
                                atual = atual->prox;
                        }
                }
                Elemento* cabeca; //Nó inicial da lista
        private:
                void removerPrimeiroElemento();
};


#endif // LISTA_H
