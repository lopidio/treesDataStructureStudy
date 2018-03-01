#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include "Estrutura.h"

class BNode
{
        friend class PrinterB;
        struct Requisicao;
        friend class BTree;
        public:
                BNode();
                BNode(int valor, int ordem_); //Construtor da raiz chamado pela árvore
                BNode(int valor, BNode* filho0, BNode* filho1, int ordem_); //Construtor da raiz chamado quando a raiz faz um split
                BNode (int* chaves, int ordem_); //Quando uma nova folha é criada
                BNode (int* chaves, BNode** novosFilhos, int ordem_); //Quando um novo nó interno é criado através de um split de um nó interno
                virtual ~BNode();
                Requisicao* inserir (int x);
                bool buscar(int x);
                void imprimir() const;
                int getPrimeiroElemento() const;
                bool remover(int x, BNode* pai);
        protected:
        private:
                int ordem;
                int tamanho;
                int *chave;
                BNode**filho;
                int buscaBinaria(int x, int inicial, int final); //retorna o índice mais próximo de x
                bool eFolha() const;
                bool eCompleto() const;
               void sobeParaNaoCompleto(int valor, int indice, BNode* novoNo); //Quando um filho faz split, manda um elemento para o pai
                int pegarMaiorElemento();//OK! Usado para retornar o antecessor!
                Requisicao* filhoRequisita(BNode*filhoRequerente); //retorna um conjunto de chaves e ponteiros
                struct Requisicao //Utilizado na remoção
                {
                        Requisicao(int tamanho_):tamanho(tamanho_)
                        {
                                ponteiro = new BNode*[tamanho];
                                chave = new int[tamanho];
                        }
                        ~Requisicao()
                        {
                                delete[] ponteiro;
                                delete[] chave;
                                ponteiro = NULL;
                                chave = NULL;
                        }
                        BNode** ponteiro; //tamanho
                        int* chave; //tamanho
                        int tamanho;
                };
                Requisicao* paiPedeMergeFilhoEsquerdo(); //Meu irmão direito quer se mesclar a mim
                Requisicao* paiPedeMergeFilhoDireito(); //Meu irmão esquerdo quer se mesclar a mim
                Requisicao* paiPedeUltimoElemento(); //Irmão direito quer um elemento e eu posso emprestar
                Requisicao* paiPedePrimeiroElemento(); //Irmão esquerdo quer um elemento e eu posso emprestar
};

class BTree: public Estrutura
{
        friend class BNode;
        friend class BNode::Requisicao;
        friend class PrinterB;
        public:
                BTree(int ordem_);
                virtual ~BTree();
                void imprimir() const;
                bool buscar(int x);
                bool inserir(int x);
                bool remover(int x);
                void setRaiz(BNode* novaRaiz);
                int getOrdem() const;
        protected:
        private:
                BNode* raiz;
                int ordem;
};



#endif // BTREE_H
