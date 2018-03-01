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
#include "BTree.h"

int comparaIntMais(const void * a, const void * b)
{
        return ( *(int*)a - *(int*)b );
}

BNode::BNode()
{
}
BNode::BNode(int valor, int ordem_) //Construtor da raiz chamado pela árvore
{
        ordem = ordem_;
        chave = new int[2*ordem];
        filho = new BNode*[2*ordem+1];
        tamanho = 1;
        chave[0] = valor;
        for (int i = 0; i < 2*ordem + 1; i++)
        {
                filho[i] = NULL;
        }
}
BNode::BNode(int valor, BNode* filho0, BNode* filho1, int ordem_) //Construtor da raiz chamado quando a raiz faz um split
{
        ordem = ordem_;
        chave = new int[2*ordem];
        filho = new BNode*[2*ordem+1];
        tamanho = 1;
        chave[0] = valor;
        for (int i = 0; i < 2*ordem + 1; i++)
        {
                filho[i] = NULL;
        }
        filho[0] = filho0;
        filho[1] = filho1;
}

BNode::BNode (int* chaves, int ordem_) //Quando uma nova folha é criada
{
        ordem = ordem_;
        chave = new int[2*ordem];
        filho = new BNode*[2*ordem+1];
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
BNode::BNode (int* chaves, BNode** novosFilhos, int ordem_) //Quando um novo nó interno é criado através de um split de um nó interno
{
        ordem = ordem_;
        chave = new int[2*ordem];
        filho = new BNode*[2*ordem+1];
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

BNode::~BNode()
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

BNode::Requisicao* BNode::inserir(int x)
{
        printf("Inserir comeco, valor: %d\n", x);
        if (eFolha())
        {
                printf("Sou folha\n");
                //Verifica se já existe
                if (chave[buscaBinaria(x, 0, tamanho-1)] == x) //Se já existe
                        return NULL;
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
                        qsort (ordenados, 2*ordem+1, sizeof(int), comparaIntMais); //Ordeno as chaves
                        tamanho = ordem;
                        for (int i = 0; i < ordem; i++) //Copiando ordenados para a chave
                        {
                                chave[i] = ordenados[i];
                        }
                        BNode* splitado = new BNode(&ordenados[ordem + 1], ordem);
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
                if (chave[indice] == x)// || chave[indice+1] == x)
                {
                        printf("Jah existe!!\n");
                        return NULL; //Já existe
                }
                //Apontando para o lado correto da busca binaria
                if (chave[indice] < x)
                        ++indice;

                BNode* filhoCorrespondente = filho[indice];
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
                                qsort (ordenados, 2*ordem+1, sizeof(int), comparaIntMais); //Ordeno as chaves
                                printf("Ordenei chaves, ordenarei ponteiros\n");
                                //{Ordenação dos ponteiros através de um shift e do primeiro elemento de cada um
                                BNode* ponteirosOrdenados[2*ordem+2];
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
                                BNode* splitado = new BNode(&ordenados[ordem + 1], &ponteirosOrdenados[ordem + 1], ordem);
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
bool BNode::buscar(int x)
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
void BNode::imprimir() const
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
int BNode::getPrimeiroElemento() const
{
        return chave[0];
}

bool BNode::remover(int x, BNode* pai)
{
        printf("Adentrei a remocao: %d\n", x);
        bool resultado;
        int indiceCentral = buscaBinaria(x, 0, tamanho - 1);
        if (!eFolha()) //Se for nó interno
        {
                int chaveCentral = chave[indiceCentral];
                if (chaveCentral == x) //Remoção no nó interno
                {
                        chave[indiceCentral] = filho[indiceCentral]->pegarMaiorElemento();
                        printf("\nA remocao vai ser num no interno, peguei esse antecessor: %d",filho[indiceCentral]->pegarMaiorElemento() );
                        resultado = filho[indiceCentral]->remover(chave[indiceCentral], this); //Transforma na remoção de umelemento da folha
                }
                else//Remoção ocorrerá em algum filho
                {
                        resultado = filho[indiceCentral  + (x > chaveCentral)]->remover(x, this); //Valor booleano responde qual filho deverá ser invocado
                }

        }
        else // Se for folha
        {
                if (chave[indiceCentral] == x)
                {
                        printf("\nSou folha, achei e removi o: %d e esse eh meu tamanho: %d", x, tamanho - 1);
                        --tamanho;
                        resultado = true;
                        for (int i = indiceCentral; i < tamanho; ++i) //Shift para esquerda a partir da chave removida
                        {
                                chave[i] = chave[i+1];
                                filho[i] = filho[i+1];
                        }
                        filho[tamanho] = NULL;
                }
                else
                {
                        printf("\nSou folha, nao achei o elemento. chave: %d..indice: %d     CI: %d     tamanho: %d", chave[indiceCentral],indiceCentral, chave[0], tamanho);
                        resultado = false; //Elemento não existe!!
                }
        }
        printf("\nVou verificar se estou desbalanceado. Minha primeira chave eh: %d", chave[0]);
        //A remoção já ocorreu (em um nível mais embaixo ou não) e talvez tenha me deixado instável.. Verificar isso
        // Se com a remoção, eu tou com o tamanho menor do que a ordem
        //Se eu não tiver pai, eu sou a raiz..
        if (pai && resultado && tamanho < ordem) //Se a remoção tiver sido mal sucedida não precisa verificar
                                                                                //Se o tamanho ainda estiver maior do que ordem, tb não há problema
        {
                printf("\nEstou desbalanceado. Chave inicial: %d", chave[0]);
                Requisicao* requisicao = pai->filhoRequisita(this); // Retorna um conjunto de chaves e ponteiros para ser inseridos no nó atual
                printf("\nRequisitei e fui atendido. Chave inicial: %d", chave[0]);
                if (requisicao->chave[0] < chave[0]) //Peguei o irmão da esquerda
                {
                        printf("\nVeio algo do meu irmao da esquerda, aumentei meu tamanho em: %d", requisicao->tamanho);
                        //Especie de shift pra direita
                        for (int i = tamanho - 1; i >=0; --i) //Mover todos os elementos (requisicao->tamanho casas)
                        {
                                chave[i + requisicao->tamanho] = chave[i];
                                filho[i + requisicao->tamanho + 1] = filho[i + 1];
                        }
                        filho[requisicao->tamanho] = filho[0];
                        //Inserir os elementos no início
                        for (int i = 0; i < requisicao->tamanho; ++i)
                        {
                                chave[i] = requisicao->chave[i];
                                filho[i] = requisicao->ponteiro[i];
                                requisicao->ponteiro[i] = NULL;
                        }
                        tamanho += requisicao->tamanho;
                }
                else //Peguei o irmão da direita
                {
                        printf("\nVeio algo do meu irmao da direita, aumentei meu tamanho em: %d", requisicao->tamanho);
                        //Inserir os elementos no fim
                        for (int i = 0; i < requisicao->tamanho; ++i)
                        {
                                chave[tamanho + i] = requisicao->chave[i];
                                filho[tamanho+ i +1]= requisicao->ponteiro[i];
                                requisicao->ponteiro[i] = NULL;
                        }
                        tamanho += requisicao->tamanho; //Atualiza meu tamanho
                }
        }
        return resultado;
}

int BNode::buscaBinaria(int x, int inicial, int final) //retorna o índice mais próximo de x
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

bool BNode::eFolha() const
{
        bool retorno = !filho[0];
        return retorno;
}

bool BNode::eCompleto() const
{
        return tamanho == 2*ordem;
}
void BNode::sobeParaNaoCompleto(int valor, int indice, BNode* novoNo) //Quando um filho faz split, manda um elemento para o pai
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

int BNode::pegarMaiorElemento() //OK! Usado para retornar o antecessor!
{
        if (eFolha())
        {
                 return chave[tamanho - 1];
        }
        return filho[tamanho]->pegarMaiorElemento();
}

BNode::Requisicao* BNode::filhoRequisita(BNode*filhoRequerente) //retorna um conjunto de chaves e ponteiros
{
        int indice = buscaBinaria(filhoRequerente->chave[0], 0, tamanho-1);
        if (filho[indice] != filhoRequerente)
                ++indice;
        printf("\nMeu filho [%d] requisitou algo. Chave inicial: %d", indice, chave[0]);
        if (indice < tamanho) //Se não for o último filho
        {
                printf("\nEsse filho NAO eh o ultimo");
                if (filho[indice+1]->tamanho > ordem) //Irmão direito pode emprestar?
                {
                        printf("\nMeu irmao direito vai emprestar. Chave inicial dele: %d", filho[indice+1]->chave[0]);
                        Requisicao* retorno = filho[indice+1]->paiPedePrimeiroElemento(); //Remove o primeiro elemento do filho
                        int backUp = retorno->chave[0];
                        retorno->chave[0] = chave[indice];
                        chave[indice] = backUp;
                        return retorno;
                }
                else if (indice > 0 && filho[indice-1]->tamanho > ordem) // Irmão esquerdo pode emprestar? (caso não seja o primeiro filho)
                {
                        printf("\nO irmao esquerdo pode emprestar");
                        Requisicao* retorno = filho[indice-1]->paiPedeUltimoElemento(); //Remove o último elemento do filho
                        int sobe = retorno->chave[0]; //sobe o elemento que veio do filho
                        retorno->chave[0] = chave[indice-1]; //Vai descer a chave do pai
                        chave[indice-1] = sobe;
                        return retorno;
                }
                else //Vou retornar o 'irmão direito' e a "chave pai" para o merge dos filhos
                {
                        Requisicao* retorno = filho[indice+1]->paiPedeMergeFilhoDireito();	 //Tamanho = quantidade
                        retorno->chave[0] = chave[indice];
                        delete filho[indice+1];
                        for (int i = indice; i < tamanho - 1; ++i) //Faz shift pra esquerda de todos as chaves e ponteiros a partir de indice
                        {
                                chave[i] = chave[i+1];
                                filho[i+1] = filho[i+2];
                        }
                        --tamanho;
                        return retorno;
                }
        }
        else //Se for o último filho
        {
                printf("\nEsse filho eh o ultimo");
                if (filho[indice-1]->tamanho > ordem) //Irmão esquerdo pode emprestar? (cópia do código pouco acima)
                {
                        printf("\nO irmao esquerdo pode emprestar");
                        Requisicao* retorno = filho[indice-1]->paiPedeUltimoElemento(); //Remove o último elemento do filho
                        int sobe = retorno->chave[0]; //sobe o elemento que veio do filho
                        retorno->chave[0] = chave[indice-1]; //Vai descer a chave do pai
                        chave[indice-1] = sobe;
                        return retorno;
                }
                else //Vou retornar o 'irmão esquerdo' e a "chave pai" para o merge dos meus filhos
                {
                        printf("\nSou o pai e Eh o filho esquerdo que vai fazer o merge!");
                        Requisicao* retorno = filho[indice-1]->paiPedeMergeFilhoEsquerdo();	 //Tamanho = quantidade
                        retorno->chave[ordem] = chave[indice-1]; //último elemento do retorno é o valor da "chave pai"
                        delete filho[indice - 1];
                        for (int i = indice; i < tamanho - 1; ++i) //Faz shift pra esquerda de todos as chaves e ponteiros a partir de indice
                        {
                                chave[i] = chave[i+1];
                                filho[i+1] = filho[i+2];
                        }
                        filho[indice- 1] = filho[indice];
                        --tamanho;
                        return retorno;
                }
        }
}

BNode::Requisicao* BNode::paiPedeMergeFilhoEsquerdo() //Meu irmão direito quer se mesclar a mim
{
        Requisicao* retorno = new Requisicao(ordem + 1); //Todo meu conteúdo e um valor do pai
        for (int i = 0; i < ordem; ++i)
        {
                retorno->chave[i] = chave[i];
                retorno->ponteiro[i] = filho[i];
        }
        //Perceber que fica um espaço vago de chave que será completado com o valor do pai
        retorno->ponteiro[ordem] = filho[ordem];
        for (int i = 0; i < tamanho;++i)
                filho[i] = NULL; //Isso ocorre para que quando a deleção ocorra não destrua tudo
        return retorno;
}
BNode::Requisicao* BNode::paiPedeMergeFilhoDireito() //Meu irmão esquerdo quer se mesclar a mim
{
        Requisicao* retorno = new Requisicao(ordem + 1); //Todo meu conteúdo e um valor do pai
        for (int i = 0; i < ordem; ++i)
        {
                retorno->chave[i + 1] = chave[i];
                retorno->ponteiro[i] = filho[i];
        }
        //Perceber que fica um espaço vago de chave que será completado com o valor do pai
        retorno->ponteiro[ordem] = filho[ordem];
        for (int i = 0; i < tamanho;++i)
                filho[i] = NULL; //Isso ocorre para que quando a deleção ocorra não destrua tudo
        return retorno;
}
BNode::Requisicao* BNode::paiPedeUltimoElemento() //Irmão direito quer um elemento e eu posso emprestar
{
        printf("\nMeu pai pediu meu ultimo elemento. Eu doei o: %d", chave[tamanho - 1]);
        Requisicao* retorno = new Requisicao(1);
        retorno->chave[0] = chave[tamanho - 1];
        retorno->ponteiro[0] = filho[tamanho];
        filho[tamanho] = NULL;
        --tamanho;
        return retorno;
}
BNode::Requisicao* BNode::paiPedePrimeiroElemento() //Irmão esquerdo quer um elemento e eu posso emprestar
{
        printf("\nMeu pai pediu meu primeiro elemento. Eu doei o: %d", chave[0]);
        Requisicao* retorno = new Requisicao(1);
        retorno->chave[0] = chave[0];
        retorno->ponteiro[0] = filho[0];
        for (int i = 0; i < tamanho - 1; ++i) //Shift para esquerda
        {
                chave[i] = chave[i+1];
                filho[i] = filho[i+1];
        }
        filho[tamanho - 1] = filho[tamanho];
        filho[tamanho] = NULL;
        --tamanho;
        return retorno;
}

BTree::BTree(int ordem_):Estrutura("Arvore B")
{
        raiz = NULL;
        ordem = ordem_;
}
BTree::~BTree()
{
        printf("Comecou o fuzue\n");
        if (raiz)
                delete raiz;
}
void BTree::imprimir() const
{
        if (raiz)
        {
                printf("\n\nImpressao ordem: %d\nRaiz:  ", ordem);
                raiz->imprimir();
        }
}
bool BTree::buscar(int x)
{
        if (raiz)
                return raiz->buscar(x);
        return false;
}
bool BTree::inserir(int x)
{
        if (raiz)
        {
                BNode::Requisicao* resultadoInsercao = raiz->inserir(x);
                if (resultadoInsercao && resultadoInsercao->tamanho > 0) //Se subiu algum elemento
                {
                        if (raiz->getPrimeiroElemento() < resultadoInsercao->ponteiro[0]->getPrimeiroElemento())
                        {
                                BNode*novaRaiz = new BNode(resultadoInsercao->chave[0], raiz, resultadoInsercao->ponteiro[0], ordem);
                                raiz = novaRaiz;
                        }
                        else
                        {
                                 raiz = new BNode(resultadoInsercao->chave[0], resultadoInsercao->ponteiro[0], raiz, ordem);
                        }
                }
                return resultadoInsercao;
        }
        return raiz = new BNode(x, ordem);
}
bool BTree::remover(int x)
{
        if (!raiz)
                return false;

        bool retorno = raiz->remover(x, NULL);
        if (retorno && raiz->tamanho == 0)
        {
                printf("\nRaiz tamanho == 0 -> ponteiro: %d", raiz);
                BNode* novaRaiz;
                if (raiz->filho[0])
                {
                        printf("\nPrimeiro filho eh a nova raiz: %d", raiz->filho[0]);
                        novaRaiz = raiz->filho[0];
                        raiz = novaRaiz;
                }
                else if (raiz->filho[1])
                {
                        printf("\nSegundo filho eh a nova raiz: %d", raiz->filho[1]);
                        novaRaiz = raiz->filho[1];
                        raiz = novaRaiz;
                }
                else
                {
                        printf("\nNinguem eh a nova raiz");
                        raiz = NULL;
                }
        }
        return retorno;
}
void BTree::setRaiz(BNode* novaRaiz)
{
        raiz = novaRaiz;
}
int BTree::getOrdem() const
{
        return ordem;
}
