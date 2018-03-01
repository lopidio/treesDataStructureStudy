/* *********************************************/
/********************************************  /
//
// @date
//
// Project - Gordos Isometricos
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


#include "Splay.h"
#include <stdio.h>

SplayNo::SplayNo(int x):NoBinario(x)
{

}


 SplayNo::~SplayNo()
{

}


/** @brief inserir
  *
  * @todo: document this function
  */
NoBinario* SplayNo::inserir(int valor)
{
        if (valor < chave)
        {
                if (esquerda)
                        return esquerda->inserir(valor);
                else
                        return esquerda = new SplayNo(valor);
        }
        else if (valor > chave)
        {
                if (direita)
                        return direita->inserir(valor);
                else
                        return direita = new SplayNo(valor);
        }
        return false; //O valor já existe na árvore
}


/** @brief encontrarSubstituto
  *
  * @todo: document this function
  */
SplayNo* SplayNo::encontrarSubstituto()
{
        if (direita->direita)
        {
                return ((SplayNo*)direita)->encontrarSubstituto();
        }
        else if (direita->esquerda)
        {
                SplayNo* retorno = (SplayNo*)direita;
		direita = direita->esquerda;
		return retorno;
        }
	else // Meu filho direito é o antecessor
	{
		SplayNo* retorno = (SplayNo*)direita;
		direita = NULL;
		return retorno;
	}
}

/** @brief remover
  *
  * @todo: document this function
  */
NoBinario* SplayNo::remover(int valor)
{
       if (valor < chave)
        {
                if (esquerda)
                {
                        if (esquerda->chave == valor)
                        {
                                if (esquerda->eFolha())
                                {
                                        SplayNo* retorno = (SplayNo*)esquerda;
                                        esquerda = NULL;
                                        return retorno;
                                }
                        }
                        return esquerda->remover(valor);
                }
                else
                        return NULL; //Não existe!
        }
        else if (valor > chave)
        {
                if (direita)
                {
                        if (direita->chave == valor)
                        {
                                if (direita->eFolha())
                                {
                                        SplayNo* retorno = (SplayNo*)direita;
                                        direita = NULL;
                                        return retorno;
                                }
                        }
                        return direita->remover(valor);
                }
                else
                        return NULL; //Não existe
        }
        else if (valor == chave)//Eu sou  o nó a ser removido
        {
                SplayNo* noSubstituto = this;
                if (esquerda && direita)
                {
                        if (esquerda->direita) //Meu filho esquerdo não é o antecessor
                        {
                                noSubstituto = ((SplayNo*)esquerda)->encontrarSubstituto(); //Encontra o antecessor
                        }
                        else //Meu filho esquerdo é o antecessor
                        {
                                noSubstituto = (SplayNo*)esquerda;
                                esquerda = esquerda->esquerda;
                        }
                }
                else if (esquerda)
                {
                        noSubstituto = (SplayNo*)esquerda;
                        esquerda = esquerda->esquerda;
                }
                else if (direita)
                {
                        noSubstituto = (SplayNo*)direita;
                        direita = direita->direita;
                        esquerda = noSubstituto->esquerda;
                }
                chave = noSubstituto->chave;
                return noSubstituto;
        }

}

/** @brief buscar
  *
  * @todo: document this function
  */
bool SplayNo::buscar(int valor)
{
        if (valor > chave && direita)
        {
                eBuscaStatus acao = ((SplayNo*)direita)->splayBuscar(valor);
             //   printf ("Busca Raiz\n");
                if (acao != naoEncontrado)
                {
                        if (valor > direita->chave)
                                zagZag();
                        else if (valor < direita->chave)
                                zigZag();
                        else if (valor == direita->chave)
                        {
        printf ("zag\n");

                                 zag();

                        }
                        return true;
                }
        }
        if (valor < chave && esquerda)
        {
                eBuscaStatus acao = ((SplayNo*)esquerda)->splayBuscar(valor);
             //   printf ("Busca Raiz\n");
                if (acao != naoEncontrado)
                {
                        if (valor > esquerda->chave)
                                zagZig();
                        else if (valor < esquerda->chave)
                                zigZig();
                        else if (valor == esquerda->chave)
                        {
                                        printf ("zig\n");
                                zig();

                        }
                        return true;
                }
        }
        if (valor == chave)
                return true;
        return false;
}


eBuscaStatus SplayNo::splayBuscar(int valor)
{
        eBuscaStatus status;
        if (valor > chave) // Utiliza a recursção para localizar
        {
                if (direita)
                        status = ((SplayNo*)direita)->splayBuscar(valor); //e esse status responde qual procedimento deverá ser realizado agr
                else
                        return naoEncontrado;
        }
        else if (valor < chave)
        {
                if (esquerda)
                        status = ((SplayNo*)esquerda)->splayBuscar(valor);
                else
                        return naoEncontrado;
        }
        else if (valor == chave)
        {
                return recemAcionado;
        }
     //   printf ("-------------------\nNo: %d    Status: %d\n ---------------\n", chave, status);
        switch (status)
        {
                case naoEncontrado:
                                return naoEncontrado;
                        break;
                case semAcao: //Por conta do zigZig e do zagZag as operações só devem ser realizadas em iterações pares
                                if (valor > chave)
                                {
                                        if (valor > direita->chave)
                                                zagZag();
                                        else
                                                zigZag();
                                }
                                else
                                {
                                        if (valor < esquerda->chave)
                                                zigZig();
                                        else
                                                zagZig();
                                }
                                return recemAcionado;
                        break;

                case recemAcionado: //Alterna entre ação e não ação
                                return semAcao;
        }

}

void SplayNo::zagZag()
{
        printf ("zagZag\n");
        zag();
        zag();
}


void SplayNo::zigZig()
{
        printf ("zigZig\n");
        zig();
        zig();
}


void SplayNo::zagZig()
{
        printf ("zagZig\n");
        ((SplayNo*)esquerda)->zag();
        zig();
}

/** @brief zigZag
  *
  * @todo: document this function
  */
void SplayNo::zigZag()
{
        printf ("zigZag\n");
        ((SplayNo*)direita)->zig();
        zag();
}


void SplayNo::zag()
{
        SplayNo* Node2 = (SplayNo*)direita;
        direita = Node2->direita;
        Node2->direita = Node2->esquerda;
        Node2->esquerda = esquerda;
        esquerda = Node2;

        int aux = Node2->chave;
        Node2->chave = chave;
        chave = aux;
}

/** @brief zig
  *
  * @todo: document this function
  */
void SplayNo::zig()
{
        SplayNo* Node1 = (SplayNo*)esquerda;
        esquerda = Node1->esquerda;
        Node1->esquerda = Node1->direita;
        Node1->direita = direita;
        direita = Node1;

        int aux = Node1->chave;
        Node1->chave = chave;
        chave = aux;
}



//-------------------------------------------------   Árvore  -------------------------------------------------------------

Splay::Splay():ArvoreBinaria("Splay")
{
        //ctor
}

Splay::~Splay()
{
        //dtor
}

/** @brief inserir
  *
  * @todo: document this function
  */
bool Splay::inserir(int valor)
{
        if (eVazia())
        {
                raiz = new SplayNo(valor);
                return true;
        }
        else
        {
                return raiz->inserir(valor);
        }
}
