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


#include "ArvoreBinaria.h"
#define NULL 0

#include <iostream> //COUT :)
using namespace std;


NoBinario::NoBinario(int x)
{
        chave = x;
        esquerda = NULL;
        direita = NULL;
}

 NoBinario::~NoBinario()
{
        cout << "deletou: " << chave << endl;
        esquerda = direita = NULL; //Precaução
}




/** @brief destruir
  *
  * @todo: document this function
  */
void NoBinario::destruir()
{
         if (esquerda)
                esquerda->destruir(); //Destrói a esquerda, caso haja
        if (direita)
                direita->destruir(); //Destrói a direita, caso haja
        delete this; // Se remove
}

/** @brief numeroFolhas
  *
  * @todo: document this function
  */
int NoBinario::numeroFolhas() const
{
        int soma = 0;
        if (eFolha())
                return 1;
        if (esquerda)
                soma += esquerda->numeroFolhas();
        if (direita)
                soma += direita->numeroFolhas();
        return soma;
}

/** @brief eCheio
  *
  */
bool NoBinario::eCheio() const
{
        bool cheioEsquerda = true;
        int alturaEsquerda = 0;
        if (esquerda)
        {
                cheioEsquerda = esquerda->eCheio();
                alturaEsquerda = esquerda->altura();
        }
        bool cheioDireita = true;
        int alturaDireita = 0;
        if (direita)
        {
                cheioDireita = direita->eCheio();
                alturaDireita = direita->altura();
        }
        bool alturasIguais = (alturaEsquerda == alturaDireita);
        return alturasIguais & cheioDireita & cheioEsquerda;
}



/** @brief numeroElementos
  *
  * @todo: document this function
  */
int NoBinario::numeroElementos() const
{
        int soma = 1; //Contar comigo mesmo..
        if (esquerda)
                soma += esquerda->numeroElementos();
        if (direita)
                soma += direita->numeroElementos();
        return soma; // Eu mesmo
}

/** @brief altura
  *
  * @todo: document this function
  */
int NoBinario::altura() const
{
        int esquerdaAltura = 1; //Minha própria altura
        int direitaAltura = 1;

        if (esquerda)
                esquerdaAltura += esquerda->altura();
        if (direita)
                direitaAltura += direita->altura();

        if (esquerdaAltura > direitaAltura)
                return esquerdaAltura;
        return direitaAltura;
}

/** @brief eFolha
  *
  * @todo: document this function
  */
bool NoBinario::eFolha() const
{
        return !esquerda && !direita;
}

void NoBinario::imprimir() const
{
        if (esquerda)
        {
                cout<< "No: "<< chave <<", filho esquerdo: " << esquerda->chave << endl;
                esquerda->imprimir();
        }
        if (direita)
        {
                cout<< "No: "<< chave <<", filho direito: " << direita->chave << endl;
                direita->imprimir();
        }
}
//********************************************    Árvore *************************************


ArvoreBinaria::ArvoreBinaria(char* nome):Estrutura(nome)
{
        raiz = NULL;
}

ArvoreBinaria::~ArvoreBinaria()
{
        //dtor
}

void ArvoreBinaria::imprimir() const
{
        cout <<"IMPRIMIR-------------------------------------------------------\n";
        if (!eVazia())
        {
                cout << "Raiz: " << ((NoBinario*)raiz)->chave << endl;
                raiz->imprimir();
        }
        cout <<"FIM   IMPRIMIR-------------------------------------------------------\n";

}


bool ArvoreBinaria::remover(int valor)
{
        if (!eVazia())
        {
                bool soExisteARaiz = (numeroElementos() == 1); // PRecaução para caso a raiz seja o único elemento
                NoBinario* retorno = (NoBinario*)raiz->remover(valor);
                delete retorno;
                if (retorno && soExisteARaiz) //Se a raiz for deletada
                {
                        raiz = NULL; //Atualizar o valor dela
                }
                return retorno;
        }
        return false;
}

/** @brief destruir
  *
  * @todo: document this function
  */
void ArvoreBinaria::destruir()
{
        if (!eVazia())
                raiz->destruir();
}

/** @brief numeroFolhas
  *
  * @todo: document this function
  */
int ArvoreBinaria::numeroFolhas() const
{
        if (!eVazia())
                return raiz->numeroFolhas();
        return 0;
}

/** @brief eCheia
  *
  * @todo: document this function
  */
bool ArvoreBinaria::eCheia() const
{
        if (!eVazia())
                return raiz->eCheio();
        return true;
}

/** @brief numeroElementos
  *
  * @todo: document this function
  */
int ArvoreBinaria::numeroElementos() const
{
        if (!eVazia())
                return raiz->numeroElementos();
        return 0;
}

/** @brief altura
  *
  * @todo: document this function
  */
int ArvoreBinaria::altura() const
{
        if (!eVazia())
        {
                return raiz->altura();
        }
        return 0;
}

/** @brief eVazia
  *
  * @todo: document this function
  */
bool ArvoreBinaria::eVazia() const
{
        return !raiz;
}


/** @brief buscar
  *
  * @todo: document this function
  */
bool ArvoreBinaria::buscar(int x)
{
        if (!eVazia())
                return raiz->buscar(x);
        return false;
}
