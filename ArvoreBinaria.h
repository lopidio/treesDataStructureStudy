#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include "Estrutura.h"

struct NoBinario; // Forward declaration!

class ArvoreBinaria: public Estrutura
{
        friend class PrinterBinario;
        public:
                bool eVazia() const;
                int altura() const;
                int numeroElementos() const;
                bool eCheia() const;
                int numeroFolhas() const;
                void destruir();
                const NoBinario* const getRaiz() const;
                virtual bool buscar(int);
                virtual bool remover(int);

                ArvoreBinaria(char*);
                virtual ~ArvoreBinaria();
                virtual void imprimir() const;
        protected:
                NoBinario* raiz;
        private:
};

struct NoBinario
{
        friend class PrinterBinario;
        //Construtor
        NoBinario(int x);
        //Destrutor
        ~NoBinario();

        virtual NoBinario* inserir(int) = 0;
        virtual bool buscar(int) = 0;
        virtual NoBinario* remover(int) = 0;
        virtual int altura() const;
        virtual int numeroElementos() const;
        virtual bool eCheio() const;
        virtual int numeroFolhas() const;
        virtual void destruir();
        virtual bool eFolha() const;
        virtual void imprimir() const;

        //Atributos
        int chave;
        NoBinario* esquerda, *direita;
};

#endif // ARVOREBINARIA_H
