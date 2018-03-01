#ifndef LISTA_H
#define LISTA_H
#include "PrinterHash.h"
#include <stdio.h>


struct Elemento //N�s da lista
{
        Elemento(Elemento* prox_, int valor_)
        {
                prox = prox_;
                valor = valor_;
        }
        Elemento* prox; //Ponteiro para o pr�ximo n�
        int valor; //Valor do n�
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
                Elemento* cabeca; //N� inicial da lista
        private:
                void removerPrimeiroElemento();
};


#endif // LISTA_H
