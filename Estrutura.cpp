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


#include "Estrutura.h"

Estrutura::Estrutura(char* nome_)
{
        nome = nome_;
}

Estrutura::~Estrutura()
{
        //dtor
}

/** @brief getNome
  *
  * @todo: document this function
  */
char* Estrutura::getNome() const
{
        return nome;
}


