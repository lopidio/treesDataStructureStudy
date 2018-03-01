#ifndef BMAISTREE_H
#define BMAISTREE_H

#include "Estrutura.h"

class BMaisTree;

class BMaisNode
{
        friend class PrinterBMais;
        struct Requisicao;
        friend class BMaisTree;
        public:
                BMaisNode();
                BMaisNode(int valor, int ordem_); //Construtor da raiz chamado pela �rvore
                BMaisNode(int valor, BMaisNode* filho0, BMaisNode* filho1, int ordem_); //Construtor da raiz chamado quando a raiz faz um split
                BMaisNode (int* chaves, int ordem_); //Quando uma nova folha � criada
                BMaisNode (int* chaves, BMaisNode** novosFilhos, int ordem_); //Quando um novo n� interno � criado atrav�s de um split de um n� interno
                virtual ~BMaisNode();
                Requisicao* inserir (int x);
                bool buscar(int x);
                void imprimir() const;
                int getPrimeiroElemento() const;
                bool remover(int x, BMaisNode* pai);
        protected:
        private:
                int ordem;
                int tamanho;
                int *chave;
                BMaisNode**filho;
                int buscaBinaria(int x, int inicial, int final); //retorna o �ndice mais pr�ximo de x
                bool eFolha() const;
                bool eCompleto() const;
                void sobeParaNaoCompleto(int valor, int indice, BMaisNode* novoNo); //Quando um filho faz split, manda um elemento para o pai
                struct Requisicao //Utilizado na remo��o
                {
                        friend class BMaisTree;
                        Requisicao(int tamanho_):tamanho(tamanho_)
                        {
                                ponteiro = new BMaisNode*[tamanho];
                                chave = new int[tamanho];
                        }
                        ~Requisicao()
                        {
                                delete[] ponteiro;
                                delete[] chave;
                                ponteiro = NULL;
                                chave = NULL;
                        }
                        BMaisNode** ponteiro; //tamanho
                        int* chave; //tamanho
                        int tamanho;
                };
};

class BMaisTree: public Estrutura
{
        friend class BMaisNode;
        friend class PrinterBMais;
        public:
                BMaisTree(int ordem_);
                virtual ~BMaisTree();
                void imprimir() const;
                bool buscar(int x);
                bool inserir(int x);
                bool remover(int x);
                void setRaiz(BMaisNode* novaRaiz);
                int getOrdem() const;
        protected:
        private:
                BMaisNode* raiz;
                int ordem;
};




#endif // BMAISTREE_H
