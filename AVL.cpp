/* *********************************************/
/********************************************  /
//
// @date
//
// Project - Árvore AVL
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

#include <iostream>
#include "AVL.h"


//Nó *********************************************************************************************************************************************************************************
AVLNo::AVLNo(int valor):NoBinario(valor)
{
}

AVLNo::AVLNo::~AVLNo()
{
}



/**
* Retorna a altura direita menos a altura esquerda
*/
int AVLNo::fatorBalanceamento() const
{
        int bal = 0;
        if (esquerda)
                bal -= esquerda->altura();
        if (direita)
                bal += direita->altura();
        return bal;
}

/**
* Verdadeiro caso exista o elemento
*/
bool AVLNo::buscar(int valor)
{
        if (valor < chave && esquerda) //Se o valor é menor que a chave, e eu tenho filho esquerdo
                return esquerda->buscar(valor);
        else if (valor > chave && direita) //Se o valor é maior que a chave, e eu tenho filho direito
                return direita->buscar(valor);
        else if (valor == chave) //Eu sou o valor procurado
                return true;
        return false; //Não existe
}

/**
* Retorna verdadeiro caso as alturas dos meu filhos forem similares (no máximo 1 de diferença)
* e se meus filhos estão balanceados
*/
bool AVLNo::eBalanceado() const
{
        bool fator = (fatorBalanceamento() <= 1 ) && (fatorBalanceamento() >= -1);
        bool balEsquerdo = true;
        if (esquerda)
                balEsquerdo = ((AVLNo*)esquerda)->eBalanceado();
        bool balDireito = true;
        if (direita)
                balDireito = ((AVLNo*)direita)->eBalanceado();
        return fator & balEsquerdo & balDireito;
}


/**
*  Retorna o elemento inserido, para efetuar o balanceamento
*  Retorna NULL caso o elemento já exista
*/
AVLNo* AVLNo::inserir(int valor)
{
        if (valor < chave)  //Inserção na esquerda
        {
                AVLNo* novoNo;
                if (esquerda)
                        novoNo = (AVLNo*)esquerda->inserir(valor);
                else
                {
                        esquerda = new AVLNo(valor);
                        return (AVLNo*)esquerda;
                }
                if (novoNo)
                        balancearInsercao(valor); // Caso algum nó tenha sido inserido
                return novoNo;
        }
        else if (valor > chave)  //Inserção na direita
        {
                AVLNo* novoNo;
                if (direita)
                        novoNo =  (AVLNo*)direita->inserir(valor); //Novo nó é exatamente o nó que foi inserido
                else
                {
                         direita = new AVLNo(valor);
                         return (AVLNo*)direita;
                }

                if (novoNo)// Caso algum nó tenha sido inserido
                        balancearInsercao(valor);
                return novoNo;
        }
        return NULL; //Já existe
}

/** @brief balancear
  * Verifica qual rotação ser chamada a partir de uma inserção
  */
void AVLNo::balancearInsercao(int valor)
{
        if (!esquerda && !direita)
                return;
        if (valor < chave)  //Inserção na esquerda
        {
                if (!eBalanceado())  //Desbalanceou para a esquerda
                {
                        if (valor < esquerda->chave)
                                rotacaoDireita();
                        else
                                rotacaoDuplaDireita();
                }
        }
        else if (valor > chave)  //Inserção na direita
        {
                if (!eBalanceado())  //Desbalanceou para a direita
                {
                        if (valor > direita->chave)
                                rotacaoEsquerda();
                        else
                                rotacaoDuplaEsquerda();
                }
        }
}



/**
*              this                                      this
*            /     \                                    /      \
*          A        Node2           ->     Node2     C                 E troca as chaves
*                     /      \                   /        \
*                    B       C                 A         B
*/
void AVLNo::rotacaoEsquerda()
{
   //     cout << "Rotacao esquerda do: " <<chave << endl;
        AVLNo* Node2 = (AVLNo*)direita;
        direita = Node2->direita;
        Node2->direita = Node2->esquerda;
        Node2->esquerda = esquerda;
        esquerda = Node2;

        //Swap das chaves
        int aux = Node2->chave;
        Node2->chave = chave;
        chave = aux;
}

/**
*              this                          this
*            /     \                       /      \
*       Node1   C       ->        A        Node1                     E troca as chaves
*       /      \                                   /        \
*      A       B                                 B         C
*/
void AVLNo::rotacaoDireita()
{
   //     cout << "Rotacao direita do: " <<chave << endl;
        AVLNo* Node1 = (AVLNo*)esquerda;
        esquerda = Node1->esquerda;
        Node1->esquerda = Node1->direita;
        Node1->direita = direita;
        direita = Node1;

        //Swap das chaves
        int aux = Node1->chave;
        Node1->chave = chave;
        chave = aux;
}

//Chama as rotações simples
void AVLNo::rotacaoDuplaEsquerda()
{
        ((AVLNo*)direita)->rotacaoDireita();
        rotacaoEsquerda();
}

//Chamaas rotações simples
void AVLNo::rotacaoDuplaDireita()
{
        ((AVLNo*)esquerda)->rotacaoEsquerda();
        rotacaoDireita();
}



/**
*  Composta de duas recursões:
* Primeira: Percorre recursivamente até encontrar o nó a ser removido
* Segunda: a partir do nó removido, chama um método recursivo para encontrar o seu nó antecessor
* Segunda continuação: Balanceia todos os nós desbalanceados entre o antecessor e o removido
* Primeira continuação: Balanceia todos os nós desbalanceados entre o removido e a raiz
*/
AVLNo* AVLNo::remover(int valor)
{
	if (valor < chave)
	{
	        AVLNo* novoNo = NULL;
		if (esquerda)
		{
		        if (esquerda->chave == valor)
                        {
                                if (esquerda->eFolha())
                                {
                                        novoNo = (AVLNo*)esquerda;
                                        esquerda = NULL; //Encontrei a chave
                                        balancearRemocao();
                                        return novoNo;
                                }
                        }
                        novoNo = (AVLNo*)esquerda->remover(valor); //Inicia a recursão
		}
		else
			return NULL; //Não existe
		if (novoNo)
			balancearRemocao();
		return novoNo;
	}
	else if(valor > chave)
	{
                AVLNo* novoNo = NULL;
		if (direita)
		{
		        if (direita->chave == valor)
		        {
		                if (direita->eFolha())
		                {
                                        novoNo = (AVLNo*)direita;
                                        direita = NULL;
                                        balancearRemocao();
                                        return novoNo;
		                }
		        }
                        novoNo = (AVLNo*)direita->remover(valor);
		}
		else
			return NULL; //Não existe
		if (novoNo)
			balancearRemocao();
		return novoNo;
	}
	else if (valor == chave)//Eu sou o nó a ser removido
	{
		AVLNo* noSubstituto = this;
		if (esquerda)
		{
			if (esquerda->direita) //Meu filho esquerdo não é o antecessor
			{
				noSubstituto = ((AVLNo*)esquerda)->removerAntecessor();
				((AVLNo*)esquerda)->balancearRemocao();
			}
			else //Meu filho esquerdo é o antecessor
			{
                                noSubstituto = (AVLNo*)esquerda;
                                esquerda = esquerda->esquerda; // Mesmo que NULL :)
                                noSubstituto->esquerda = NULL; //Só por prevenção
			}
		}
		else if (direita) //A chave do meu filho direito vem pra mim e eu removo meu filho direito
		{
			noSubstituto = (AVLNo*)direita;
			chave = direita->chave;
			direita = NULL;
			return noSubstituto;
		}
		chave = noSubstituto->chave;
		balancearRemocao();
		return noSubstituto;
	}

}

/**
* Chamado quando um nó é removido
* Realiza uma busca pelos seus descendentes para encontrar o antecessor do nó removido
*  Remove o nó substituto e o retorna
*
*/
AVLNo* AVLNo::removerAntecessor()
{
	if (direita->direita) //Meu filho direito não é antecessor
	{
		AVLNo* retorno = ((AVLNo*)direita)->removerAntecessor(); // Chamada recursiva
                balancearRemocao();
                return retorno;
	}
	else if (direita->esquerda) //Meu filho direito é o antecessor e tem um filho esquerdo
	{
		AVLNo* retorno = (AVLNo*)direita;
		direita = direita->esquerda;
		retorno->esquerda = NULL;
		balancearRemocao();
		return retorno;
	}
	else // Meu filho direito é o antecessor
	{
		AVLNo* retorno = (AVLNo*)direita;
		direita = NULL;
		balancearRemocao();
		return retorno;
	}
}

/**
        Método executado após alguma remoção.
        Responsável por balancear o nó this
*/
void AVLNo::balancearRemocao()
{
        if (fatorBalanceamento() < -1) //Altura esquerda maior
        {
                if (((AVLNo*)esquerda)->fatorBalanceamento() <= 0) //
                        rotacaoDireita();
                else
                        rotacaoDuplaDireita();
        }
        else if (fatorBalanceamento() > 1) //Altura direita maior
        {
                if (((AVLNo*)direita)->fatorBalanceamento() >= 0)
                        rotacaoEsquerda();
                else
                        rotacaoDuplaEsquerda();
        }
}



//Árvore ******************************************************************************************************************************************************************************************
AVL::AVL():ArvoreBinaria("AVL") //Chama os construtores de ArvoreBinaria e Arvore
{
}

AVL::~AVL() //Os destrutores das classes Base já fazem todo o trabalho
{
}

/**
        Retorna verdadeiro caso a operação tenha sido bem sucedida
        Retorna falso quando o elemento já existe
*/
bool AVL::inserir(int value)
{
        if (eVazia())
        {
                raiz = new AVLNo(value);
                return true;
        }
        else
        {
                return raiz->inserir(value);
        }
}

/**
        Retorna verdadeido caso a árvore AVl esteja balanceada
*/
bool AVL::eBalanceada() const
{
        if (!eVazia())
                return ((AVLNo*)raiz)->eBalanceado();
        return true;
}



