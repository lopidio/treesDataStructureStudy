#ifndef SPLAY_H
#define SPLAY_H

#include "ArvoreBinaria.h"

struct SplayNo;

class Splay: public ArvoreBinaria
{
        public:
                Splay();
                virtual ~Splay();
                virtual bool inserir(int); //Aqui o filho deve especificar o tipo da Raiz
        protected:
        private:
};

enum eBuscaStatus
{
        naoEncontrado,
        semAcao,
        recemAcionado
};

struct SplayNo: public NoBinario
{
        SplayNo(int);
        ~SplayNo();
        virtual NoBinario* inserir(int);
        virtual bool buscar(int);
        eBuscaStatus splayBuscar(int);
        virtual NoBinario* remover(int);
        private:
        void zig();
        void zag();
        void zigZag();
        void zagZig();
        void zigZig();
        void zagZag();

        SplayNo* encontrarSubstituto();
};

#endif // SPLAY_H
