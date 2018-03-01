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


#include <stdlib.h>
#include "BMaisTree.h"
#include <stdio.h>

int comparaInt(const void * a, const void * b)
{
        return ( *(int*)a - *(int*)b );
}

BMaisNode::BMaisNode()
{
}
BMaisNode::BMaisNode(int valor, int ordem_) //Construtor da raiz chamado pela árvore
{
        ordem = ordem_;
        chave = new int[2*ordem];
        filho = new BMaisNode*[2*ordem+1];
        tamanho = 1;
        chave[0] = valor;
        for (int i = 0; i < 2*ordem + 1; i++)
        {
                filho[i] = NULL;
        }
}
BMaisNode::BMaisNode(int valor, BMaisNode* filho0, BMaisNode* filho1, int ordem_) //Construtor da raiz chamado quando a raiz faz um split
{
        ordem = ordem_;
        chave = new int[2*ordem];
        filho = new BMaisNode*[2*ordem+1];
        tamanho = 1;
        chave[0] = valor;
        for (int i = 0; i < 2*ordem + 1; i++)
        {
                filho[i] = NULL;
        }
        filho[0] = filho0;
        filho[1] = filho1;
}

BMaisNode::BMaisNode (int* chaves, int ordem_) //Quando uma nova folha é criada
{
        ordem = ordem_;
        chave = new int[2*ordem];
        filho = new BMaisNode*[2*ordem+1];
        tamanho = ordem;
        for (int i = 0; i < ordem; i++) //Copiando as chaves
        {
                chave[i] = chaves[i];
        }
        for (int i = 0; i < 2*ordem + 1; i++) //Zerando os ponteiros
        {
                filho[i] = NULL;
        }
}
BMaisNode::BMaisNode (int* chaves, BMaisNode** novosFilhos, int ordem_) //Quando um novo nó interno é criado através de um split de um nó interno
{
        ordem = ordem_;
        chave = new int[2*ordem];
        filho = new BMaisNode*[2*ordem+1];
        tamanho = ordem;
        for (int i = 0; i < ordem; i++) //Copiando as chaves
        {
                chave[i] = chaves[i];
        }
        for (int i = 0; i < 2*ordem + 1; i++) //Zerando os ponteiros
        {
                filho[i] = NULL; //Precaução. :D
                if (i < ordem + 1)
                {
                        if (!novosFilhos[i])
                        {
                                printf ("ARRAHH COPIEI UM NULO!!!!");
                                system("pause");
                        }
                        filho[i] = novosFilhos[i];
                }
        }
}

BMaisNode::~BMaisNode()
{
        printf("Destruiu no 0\n");
        if (chave)
                delete[] chave;
        printf("Destruiu no 1\n");
        if (filho)
                delete[] filho;
        filho = NULL;
        printf("Destruiu no 2\n");
}

BMaisNode::Requisicao* BMaisNode::inserir(int x)
{
        printf("Inserir comeco, valor: %d\n", x);
        if (eFolha())
        {
                printf("Sou folha\n");
                //Verifica se já existe
                int indice = buscaBinaria(x, 0, tamanho-1);
                if (chave[indice] == x) //Se já existe
                {

                        return NULL;
                }
                if (!eCompleto()) //Caso mais fácil
                {
                        printf("Folha nao completa: %d\n", x);
                        chave[tamanho] = x;
                        for (int i = tamanho-1; i >= 0; --i) //Shift
                        {
                                if (chave[i] > x)
                                        chave[i+1] = chave[i];
                                else
                                {
                                        chave[i+1] = x;
                                        break;
                                }
                                if (i == 0)
                                        chave[0] = x;
                        }
                        ++tamanho;
                        printf("Retornei verdadeiro e sem chaves\n");
                        return new Requisicao(0);
                }
                else //Faz split!
                {
                        printf("Folha completa\n");
                        int ordenados[2*ordem +1];
                        for (int i = 0; i < 2*ordem; i++) //Copiando chaves para ordenados
                        {
                                ordenados[i] = chave[i];
                        }
                        ordenados[2*ordem] = x;
                        qsort (ordenados, 2*ordem+1, sizeof(int), comparaInt); //Ordeno as chaves
                        tamanho = ordem + 1;
                        for (int i = 0; i < ordem + 1; i++) //Copiando ordenados para a chave (incluindo a central)
                        {
                                chave[i] = ordenados[i];
                        }
                        BMaisNode* splitado = new BMaisNode(&ordenados[ordem + 1], ordem);
                        printf("Split de um no\n");
                        Requisicao* requisicao = new Requisicao(1);
                        requisicao->chave[0] = ordenados[ordem];
                        requisicao->ponteiro[0] = splitado;
                        printf("Sou uma folha, fiz split\n");
                        return requisicao;
                }
        }
        else //Caso seja um nó interno
        {
                int indice = buscaBinaria(x, 0, tamanho - 1);

                //Apontando para o lado correto da busca binaria
                if (chave[indice] < x)
                        ++indice;

                BMaisNode* filhoCorrespondente = filho[indice];
                Requisicao* retorno = filhoCorrespondente->inserir(x);
                if (retorno && retorno->tamanho > 0) //Inserção foi bem sucedida e se subiu algum nó
                {
                        if (!eCompleto())//Simplesmente faz um shift nos vetores
                        {
                                printf ("No interno: nao sou completo: %d\n", retorno->ponteiro[0]);
                                sobeParaNaoCompleto(retorno->chave[0], indice, retorno->ponteiro[0]);
                                return new Requisicao(0);
                        }
                        else //Vai ter que fazer outro split
                        {

                                //{ Ordena
                                int ordenados[2*ordem +1];
                                ordenados[0] = retorno->chave[0];
                                for (int i = 1; i < 2*ordem+1; ++i)
                                        ordenados[i] = chave[i-1];
                                qsort (ordenados, 2*ordem+1, sizeof(int), comparaInt); //Ordeno as chaves
                                printf("Ordenei chaves, ordenarei ponteiros\n");
                                //{Ordenação dos ponteiros através de um shift e do primeiro elemento de cada um
                                BMaisNode* ponteirosOrdenados[2*ordem+2];
                                for (int j = 0; j < 2*ordem+1; ++j)
                                        ponteirosOrdenados[j] = filho[j];
                                ponteirosOrdenados[2*ordem + 1] = retorno->ponteiro[0];

                                        for (int i = 0; i < 2*ordem + 2; ++i)
                                        {
                                                if (i==2*ordem+1) //Última iteração
                                                {
                                                        ponteirosOrdenados[i] = retorno->ponteiro[0];
                                                        break;
                                                }
                                                if (filho[i]->getPrimeiroElemento() < retorno->ponteiro[0]->getPrimeiroElemento())
                                                {
                                                        ponteirosOrdenados[i] = filho[i];
                                                }
                                                else
                                                {
                                                        ponteirosOrdenados[i] = retorno->ponteiro[0];
                                                        for (int j = i + 1; j < 2*ordem+2; ++j)
                                                                ponteirosOrdenados[j] = filho[j-1];
                                                        break;
                                                }
                                        }
                                //}
                                tamanho = ordem;
                                for (int i = 0; i < 2*ordem; ++i) //Copiando ordenados para a chave
                                {
                                        if (i < ordem)
                                                chave[i] = ordenados[i];
                                        else
                                                chave[i] = NULL;
                                }
                                for (int i = 0; i < 2*ordem + 1; ++i) //Copiando os ponteiros para a chave
                                {
                                        if (i < ordem + 1)
                                                filho[i] = ponteirosOrdenados[i];
                                        else
                                                filho[i] = NULL;
                                }
                                //} Ordenação
                                printf("No interno Ordenei \n");
                                BMaisNode* splitado = new BMaisNode(&ordenados[ordem + 1], &ponteirosOrdenados[ordem + 1], ordem);
                                Requisicao* requisicao = new Requisicao(1);
                                requisicao->chave[0] = ordenados[ordem];
                                requisicao->ponteiro[0] = splitado;
                                return requisicao;
                        }
                }
                printf("Passou do IF: resultado %d\n", retorno);
                return retorno;
        }
}
bool BMaisNode::buscar(int x)
{
        int indice = buscaBinaria(x, 0, tamanho - 1);
        if (eFolha())
                return chave[indice] == x;
        if (chave[indice] == x)
                return true;
        if (chave[indice] > x)
                return filho[indice]->buscar(x);
        return filho[indice + 1]->buscar(x);
}
void BMaisNode::imprimir() const
{
        for (int i = 0; i < 2*ordem; i++)
        {
                if (i< tamanho)
                        printf("|%d|", chave[i]);
                else
                        printf("| |");
        }
        for (int j = 0; j < tamanho + 1; j++)
                if (filho[j])
                {
                        int inicio =   j >0 ?chave[j-1]: -1;
                        int fim =     j != tamanho ? chave[j]:-1;
                        printf("\n\n Filho do %d <-> %d   (%d):  ", inicio, fim, filho[j]->tamanho);
                        filho[j]->imprimir();
                }
}
int BMaisNode::getPrimeiroElemento() const
{
        return chave[0];
}

bool BMaisNode::remover(int x, BMaisNode* pai)
{
        return true;
}

int BMaisNode::buscaBinaria(int x, int inicial, int final) //retorna o índice mais próximo de x
{
        int meio = (inicial + final)/2;
        if (inicial > final )
        {
                 return meio;
        }
        if (chave[meio] == x)
        {
                 return meio;
        }
        if ( x < chave[meio])
        {
                return buscaBinaria(x, inicial, meio - 1);
        }
        // x > chave[meio]
                return buscaBinaria(x, meio+1, final);
}

bool BMaisNode::eFolha() const
{
        bool retorno = !filho[0];
        return retorno;
}

bool BMaisNode::eCompleto() const
{
        return tamanho == 2*ordem;
}
void BMaisNode::sobeParaNaoCompleto(int valor, int indice, BMaisNode* novoNo) //Quando um filho faz split, manda um elemento para o pai
{
        printf("Subiu elemento para pai nao completo: %d\n", valor);
        for (int i = tamanho ; i >= indice +1; i--) //SHIFT para a direita!!
        {
                chave[i] = chave[i-1];
                filho[i + 1] = filho[i];
        }
        ++tamanho;
        chave[indice] = valor;
        filho[indice + 1] = novoNo;
}

BMaisTree::BMaisTree(int ordem_):Estrutura("Arvore Bmais")
{
        raiz = NULL;
        ordem = ordem_;
}
BMaisTree::~BMaisTree()
{
        printf("Comecou o fuzue\n");
        if (raiz)
                delete raiz;
}
void BMaisTree::imprimir() const
{
        if (raiz)
        {
                printf("\n\nImpressao ordem: %d\nRaiz:  ", ordem);
                raiz->imprimir();
        }
}
bool BMaisTree::buscar(int x)
{
        if (raiz)
                return raiz->buscar(x);
        return false;
}
bool BMaisTree::inserir(int x)
{
        if (raiz)
        {
                BMaisNode::Requisicao* resultadoInsercao = raiz->inserir(x);
                if (resultadoInsercao && resultadoInsercao->tamanho > 0) //Se subiu algum elemento
                {
                        if (raiz->getPrimeiroElemento() < resultadoInsercao->ponteiro[0]->getPrimeiroElemento())
                        {
                                BMaisNode*novaRaiz = new BMaisNode(resultadoInsercao->chave[0], raiz, resultadoInsercao->ponteiro[0], ordem);
                                raiz = novaRaiz;
                        }
                        else
                        {
                                 raiz = new BMaisNode(resultadoInsercao->chave[0], resultadoInsercao->ponteiro[0], raiz, ordem);
                        }
                }
                return resultadoInsercao;
        }
        return raiz = new BMaisNode(x, ordem);
}
bool BMaisTree::remover(int x)
{
        return raiz;
}
void BMaisTree::setRaiz(BMaisNode* novaRaiz)
{
        raiz = novaRaiz;
}
int BMaisTree::getOrdem() const
{
        return ordem;
}
