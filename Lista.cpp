/* *********************************************/
/********************************************  /
//
// @date -
//
// Project -
//
//  if (!bug)
//	@author Lopídio (I love America)
//  else
//	@author Unkwonn
//
//
//  Good Luck!
** *********************************/
/* *******************************/


#include "Lista.h"
#include <stdio.h>

Lista::Lista()
{
        cabeca = 0;
}

Lista::~Lista()
{
        while (cabeca)
        {
                printf("Removeu o %d\n", cabeca->valor);
                removerPrimeiroElemento();
        }
}

bool Lista::inserir(int valor)
{
        return cabeca = new Elemento(cabeca, valor);
}

void Lista::removerPrimeiroElemento()
{
        if (cabeca)
        {
                Elemento* apaga = cabeca;
                cabeca = cabeca->prox;
                delete apaga;
        }
}

bool Lista::remover(int x)
{
        if (cabeca)
        {
                Elemento* backUp;
                if (cabeca->valor == x)
                {
                        backUp = cabeca;
                        cabeca = cabeca->prox;
                        delete backUp;
                        return true;
                }
                else
                {
                        Elemento* atual = cabeca;
                        while (atual->prox)
                        {
                                if (atual->prox->valor == x)
                                {
                                        backUp = atual->prox;
                                        atual->prox = atual->prox->prox;
                                        delete backUp;
                                        return true;
                                }
                                atual = atual->prox;
                        }
                }
        }
        return false; //Elemento não existe
}


bool Lista::buscar(int x)
{
        Elemento* atual = cabeca;
        while (atual)
        {
                if (atual->valor == x)
                        return true;
                atual = atual->prox;
        }
        return false; //Não existe
}
