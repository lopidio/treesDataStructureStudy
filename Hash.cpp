/* *********************************************/
/********************************************  /
//
// @date -
//
// Project -
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


#include "Hash.h"

bool Hash::inserir(int x)
{
        int h = hash(x);
        if (h < 0)
                return false;
        ++fatoresCarga[h];
        return vetor[h].inserir(x);
}

bool Hash::buscar(int x)
{
        int h = hash(x);
        if (h < 0)
                return false;
        return vetor[h].buscar(x);
}
bool Hash::remover(int x)
{
        int h = hash(x);
        if (h < 0)
                return false;
        if (vetor[h].remover(x))
        {
                --fatoresCarga[h];
                return true;
        }
        return false;
}
void Hash::imprime()
{
        for (int i = 0; i < TH; ++i)
        {
                printf(" %d:   ", i);
                vetor[i].imprimir();
                printf("\n");
        }
}
int Hash::getFatorCarga() const
{
        int maior = fatoresCarga[0];
        for (int i = 1;i < TH; ++i)
                if (fatoresCarga[i] > maior)
                        maior = fatoresCarga[i];
        return maior;
}
Hash::Hash(int TH_, F* funcao):Estrutura("Hash")
{
        TH = TH_;
        f = funcao;
        vetor = new Lista[TH];
        fatoresCarga = new int [TH];
        for (int i = 0; i < TH; ++i)
                fatoresCarga[i] = 0;
}
Hash::~Hash()
{
        delete[] vetor;
        delete[] fatoresCarga;
}
int Hash::getTH() const
{
        return TH;
}
unsigned int Hash::hash(int x)
{
        int valorDafuncaoF = (f)(x);
        return valorDafuncaoF%TH;
}
