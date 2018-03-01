#ifndef BST_H
#define BST_H

#include "ArvoreBinaria.h"

struct BSTNo;

class BST: public ArvoreBinaria
{
        public:
                BST();
                virtual ~BST();
                virtual bool inserir(int); //Aqui o filho deve especificar o tipo da Raiz
        protected:
        private:
};

struct BSTNo: public NoBinario
{
        BSTNo(int);
        ~BSTNo();
        virtual NoBinario* inserir(int);
        virtual bool buscar(int);
        virtual NoBinario* remover(int);
        private:
        BSTNo* encontrarSubstituto();
};

#endif // BST_H
