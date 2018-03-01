#ifndef HASH_H
#define HASH_H

#include "Estrutura.h"
#include "PrinterHash.h"
#include "Lista.h"
#include <stdio.h>

typedef int (F)(int);


class Hash: public Estrutura
{
        friend class PrinterHash;
	public:
                bool inserir(int x);
                bool remover(int x);
                void imprime();
                bool buscar(int x);
                int getFatorCarga() const;
                Hash(int TH_, F* funcao);
                ~Hash();
                int getTH() const;
	private:
                unsigned int hash(int x);
                int TH;
                int *fatoresCarga;
		F *f; //Ponteiro pra função f(x)
		Lista* vetor;
};



#endif // HASH_H
