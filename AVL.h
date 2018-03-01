#ifndef AVL_H
#define AVL_H

#include "ArvoreBinaria.h"

struct AVLNo;

class AVL: public ArvoreBinaria
{
        public:
                //Construtor
                AVL();
                //Destrutor
                virtual ~AVL();
                //Métodos
                virtual bool inserir(int);
                bool eBalanceada() const;
        private:
                //Atributos: herda o atributo principal: raiz
};

struct AVLNo : public NoBinario
{
        //Construtor
        AVLNo(int);
        //Destrutor
        ~AVLNo();

        //Métodos
        int fatorBalanceamento() const;
        virtual bool buscar(int);
        void rotacaoEsquerda();
        void rotacaoDireita();
        void rotacaoDuplaEsquerda();
        void rotacaoDuplaDireita();
        bool eBalanceado() const;
        AVLNo* inserir(int);
        void balancearInsercao(int);
        void balancearRemocao();
        AVLNo* remover(int);
        AVLNo* removerAntecessor();
        AVLNo* removerNo();

        //Herda os atributos do Nó Binário:
        /*
                NoBinario * esquerda, *direita;
                int chave;
        */
};

#endif //AVL_H
