/* *********************************************/
/********************************************  /
//
// @date
//
// Project - �rvore AVL
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

#include <iostream>
#include "AVL.h"


//N� *********************************************************************************************************************************************************************************
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
        if (valor < chave && esquerda) //Se o valor � menor que a chave, e eu tenho filho esquerdo
                return esquerda->buscar(valor);
        else if (valor > chave && direita) //Se o valor � maior que a chave, e eu tenho filho direito
                return direita->buscar(valor);
        else if (valor == chave) //Eu sou o valor procurado
                return true;
        return false; //N�o existe
}

/**
* Retorna verdadeiro caso as alturas dos meu filhos forem similares (no m�ximo 1 de diferen�a)
* e se meus filhos est�o balanceados
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
*  Retorna NULL caso o elemento j� exista
*/
AVLNo* AVLNo::inserir(int valor)
{
        if (valor < chave)  //Inser��o na esquerda
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
                        balancearInsercao(valor); // Caso algum n� tenha sido inserido
                return novoNo;
        }
        else if (valor > chave)  //Inser��o na direita
        {
                AVLNo* novoNo;
                if (direita)
                        novoNo =  (AVLNo*)direita->inserir(valor); //Novo n� � exatamente o n� que foi inserido
                else
                {
                         direita = new AVLNo(valor);
                         return (AVLNo*)direita;
                }

                if (novoNo)// Caso algum n� tenha sido inserido
                        balancearInsercao(valor);
                return novoNo;
        }
        return NULL; //J� existe
}

/** @brief balancear
  * Verifica qual rota��o ser chamada a partir de uma inser��o
  */
void AVLNo::balancearInsercao(int valor)
{
        if (!esquerda && !direita)
                return;
        if (valor < chave)  //Inser��o na esquerda
        {
                if (!eBalanceado())  //Desbalanceou para a esquerda
                {
                        if (valor < esquerda->chave)
                                rotacaoDireita();
                        else
                                rotacaoDuplaDireita();
                }
        }
        else if (valor > chave)  //Inser��o na direita
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

//Chama as rota��es simples
void AVLNo::rotacaoDuplaEsquerda()
{
        ((AVLNo*)direita)->rotacaoDireita();
        rotacaoEsquerda();
}

//Chamaas rota��es simples
void AVLNo::rotacaoDuplaDireita()
{
        ((AVLNo*)esquerda)->rotacaoEsquerda();
        rotacaoDireita();
}



/**
*  Composta de duas recurs�es:
* Primeira: Percorre recursivamente at� encontrar o n� a ser removido
* Segunda: a partir do n� removido, chama um m�todo recursivo para encontrar o seu n� antecessor
* Segunda continua��o: Balanceia todos os n�s desbalanceados entre o antecessor e o removido
* Primeira continua��o: Balanceia todos os n�s desbalanceados entre o removido e a raiz
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
                        novoNo = (AVLNo*)esquerda->remover(valor); //Inicia a recurs�o
		}
		else
			return NULL; //N�o existe
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
			return NULL; //N�o existe
		if (novoNo)
			balancearRemocao();
		return novoNo;
	}
	else if (valor == chave)//Eu sou o n� a ser removido
	{
		AVLNo* noSubstituto = this;
		if (esquerda)
		{
			if (esquerda->direita) //Meu filho esquerdo n�o � o antecessor
			{
				noSubstituto = ((AVLNo*)esquerda)->removerAntecessor();
				((AVLNo*)esquerda)->balancearRemocao();
			}
			else //Meu filho esquerdo � o antecessor
			{
                                noSubstituto = (AVLNo*)esquerda;
                                esquerda = esquerda->esquerda; // Mesmo que NULL :)
                                noSubstituto->esquerda = NULL; //S� por preven��o
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
* Chamado quando um n� � removido
* Realiza uma busca pelos seus descendentes para encontrar o antecessor do n� removido
*  Remove o n� substituto e o retorna
*
*/
AVLNo* AVLNo::removerAntecessor()
{
	if (direita->direita) //Meu filho direito n�o � antecessor
	{
		AVLNo* retorno = ((AVLNo*)direita)->removerAntecessor(); // Chamada recursiva
                balancearRemocao();
                return retorno;
	}
	else if (direita->esquerda) //Meu filho direito � o antecessor e tem um filho esquerdo
	{
		AVLNo* retorno = (AVLNo*)direita;
		direita = direita->esquerda;
		retorno->esquerda = NULL;
		balancearRemocao();
		return retorno;
	}
	else // Meu filho direito � o antecessor
	{
		AVLNo* retorno = (AVLNo*)direita;
		direita = NULL;
		balancearRemocao();
		return retorno;
	}
}

/**
        M�todo executado ap�s alguma remo��o.
        Respons�vel por balancear o n� this
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



//�rvore ******************************************************************************************************************************************************************************************
AVL::AVL():ArvoreBinaria("AVL") //Chama os construtores de ArvoreBinaria e Arvore
{
}

AVL::~AVL() //Os destrutores das classes Base j� fazem todo o trabalho
{
}

/**
        Retorna verdadeiro caso a opera��o tenha sido bem sucedida
        Retorna falso quando o elemento j� existe
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
        Retorna verdadeido caso a �rvore AVl esteja balanceada
*/
bool AVL::eBalanceada() const
{
        if (!eVazia())
                return ((AVLNo*)raiz)->eBalanceado();
        return true;
}



