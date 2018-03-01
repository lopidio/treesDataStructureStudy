/* *********************************************/
/********************************************  /
//
// @date
//
// Project - Gordos Isometricos
//
//  if (!bug)
//	@author Lop�dio (I love America)
//  else
//	@author Unkwonn
//
//
//  Good Luck!
** *********************************/
/* *******************************/


#include "BST.h"
#define NULL 0
#include <stdio.h>


BSTNo::BSTNo(int x):NoBinario(x)
{
}

BSTNo::~BSTNo()
{
}


/** @brief buscar
  *
  * @todo: document this function
  */
bool BSTNo::buscar(int valor)
{
        if (valor < chave)
        {
                if (esquerda)
                        return esquerda->buscar(valor);
                return false;
        }
        else if (valor > chave)
        {
                if (direita)
                        return direita->buscar(valor);
                return false;
        }
        return true; //Eu sou o n� buscado
}

/** @brief inserir
  *
  * @todo: document this function
  */
NoBinario* BSTNo::inserir(int valor)
{
        if (valor < chave)
        {
                if (esquerda)
                        return esquerda->inserir(valor);
                else
                        return esquerda = new BSTNo(valor);
        }
        else if (valor > chave)
        {
                if (direita)
                        return direita->inserir(valor);
                else
                        return direita = new BSTNo(valor);
        }
        return false; //O valor j� existe na �rvore
}



BSTNo* BSTNo::encontrarSubstituto()
{
        if (direita->direita)
        {
                return ((BSTNo*)direita)->encontrarSubstituto();
        }
        else if (direita->esquerda)
        {
                BSTNo* retorno = (BSTNo*)direita;
		direita = direita->esquerda;
		return retorno;
        }
	else // Meu filho direito � o antecessor
	{
		BSTNo* retorno = (BSTNo*)direita;
		direita = NULL;
		return retorno;
	}
}


NoBinario* BSTNo::remover(int valor)
{
        if (valor < chave) //Recurs�o (sem pilha) at� encontrar o n� a ser removido
        {
                if (esquerda)
                {
                        if (esquerda->chave == valor)
                        {
                                if (esquerda->eFolha()) //Sempre verificando se � folha ou n�o
                                {
                                        BSTNo* retorno = (BSTNo*)esquerda;
                                        esquerda = NULL; //Se for a opera��o � bem simples
                                        return retorno;
                                }
                        }
                        return esquerda->remover(valor);
                }
                else
                        return NULL; //N�o existe!
        }
        else if (valor > chave) // Procede da mesma maneira
        {
                if (direita)
                {
                        if (direita->chave == valor)
                        {
                                if (direita->eFolha())
                                {
                                        BSTNo* retorno = (BSTNo*)direita;
                                        direita = NULL;
                                        return retorno;
                                }
                        }
                        return direita->remover(valor);
                }
                else
                        return NULL; //N�o existe
        }
        else if (valor == chave)//Eu sou  o n� a ser removido
        {
                BSTNo* noSubstituto = this;
                if (esquerda && direita) //Recurs�o para achar o maior n� na sub�rvore esquerda
                {
//                        printf("Iupi\n");
                        if (esquerda->direita) //Meu filho esquerdo n�o � o antecessor
                        {
//                                printf("Substituto\n");
                                noSubstituto = ((BSTNo*)esquerda)->encontrarSubstituto(); //Encontra o antecessor
                        }
                        else //Meu filho esquerdo � o antecessor
                        {
                                printf("Meu fihlo esquerdo e o antecessor\n");
                                noSubstituto = (BSTNo*)esquerda;
                                esquerda = esquerda->esquerda;
                        }
                }
                else if (esquerda)
                {
                        printf("Eu soh tenho o filho esquerdo\n");
                        noSubstituto = (BSTNo*)esquerda;
                        esquerda = esquerda->esquerda;
                }
                else if (direita)
                {
//                        printf("Eu soh tenho o filho direito eis o endere3co dele: %d\n", direita);
                        noSubstituto = (BSTNo*)direita;
//                        printf("direita->direita: %d\n", direita->direita);
                        direita = direita->direita;
//                        printf("Esquerda: %d   =  %d\n", esquerda);
                        esquerda = noSubstituto->esquerda;
                }
//                printf("Trocando chaves\n");
                chave = noSubstituto->chave;
//                printf("Retornando\n");
                return noSubstituto;
        }
}




//************* �rvore ***********************************

BST::BST():ArvoreBinaria("BST")
{
        //ctor
}

BST::~BST()
{
        //dtor
}


/**
        Retorna verdadeiro caso a opera��o tenha sido bem sucedida
        Retorna falso quando o elemento j� existe
*/
bool BST::inserir(int value)
{
        if (eVazia())
        {
                raiz = new BSTNo(value);
                return true;
        }
        else
        {
                return raiz->inserir(value);
        }
}
