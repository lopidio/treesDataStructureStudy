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


#include "PrinterHash.h"
#include "Hash.h"

PrinterHash::PrinterHash(Hash &hash_):Printer(&hash_)
{
        hash = &hash_;
}

PrinterHash::~PrinterHash()
{

}


void PrinterHash::Quadrado::draw()
{
        sf::Color cor;
        cor = Color::White;
        if (cabeca)
                cor = Color::Black;
        else if (valor == owner->getElementoDestacado())
                cor = Color::Yellow;
        //{ Calculando as quinas
        Vector2f quinaSuperioEsquerda;
        quinaSuperioEsquerda.x = ponto.x * owner->getEspacamentoHorizontal() + owner->origem.x - 8;
        quinaSuperioEsquerda.y = ponto.y * owner->getEspacamentoVertical() + owner->origem.y;
        Vector2f quinaInferiorDireita;
        quinaInferiorDireita.x = quinaSuperioEsquerda.x + 15;
        quinaInferiorDireita.y = quinaSuperioEsquerda.y + 15;
        //}
        Shape quadrado = Shape::Rectangle(quinaSuperioEsquerda, quinaInferiorDireita,
                                                cor, 1.0f, Color::Black);
        owner->app->Draw(quadrado);
        String valorStr;
        if (cabeca)
                valorStr.SetColor(Color::White);
        else
                valorStr.SetColor(Color::Black);
        valorStr.SetSize(12);
        std::stringstream conversor;
        conversor <<valor;
        valorStr.SetText(conversor.str());
        int largura = valorStr.GetRect().Right - valorStr.GetRect().Left;
        int altura = valorStr.GetRect().Bottom - valorStr.GetRect().Top;
        valorStr.SetPosition(quinaInferiorDireita.x - 7.5f - largura/2, quinaInferiorDireita.y - 7.5f - altura/2);
        owner->app->Draw(valorStr);
}

void PrinterHash::childDraw()
{
        //desenha todas as linhas
        for (std::vector<Linha>::iterator it = linhas.begin();
                it != linhas.end();
                 ++it)
        {
                it->draw();
        }
        //desenha todos os quadrados
//        printf("\n\n\n\n\n\n Vai imprimir!!!\n");
        for (std::vector<Quadrado>::iterator it = quadrados.begin();
                it != quadrados.end();
                 ++it)
        {
                it->draw();
//                printf ("cabeca: %d, valor: %d, x: %d, y: %d\n", it->cabeca, it->valor, it->ponto.x, it->ponto.y);
        }
}

void PrinterHash::childRefresh()
{
        //limpa quadrado e linhas
        linhas.clear();
        quadrados.clear();
        numeroDeNosImpressos = hash->getTH();
        numeroDeOrdensImpressas = hash->getFatorCarga();
        int nivel = 0;
        for (int i = 0; i < hash->getTH(); ++i)
        {
                Quadrado quadrado;
                quadrado.cabeca = true;
                quadrado.valor = i;
                quadrado.ponto.x = i;
                quadrado.ponto.y = nivel;
                quadrado.owner = this;
                quadrados.push_back(quadrado);
                representacaoDeNo(hash->vetor[i].cabeca, nivel+1,i);
        }

}


void PrinterHash::representacaoDeNo(Elemento* no, int nivel, int horizontal)
{
        if (no)
        {
                Linha linhaPraCima;
                linhaPraCima.owner = this;
                linhaPraCima.ponto1.y = nivel - 1;
                linhaPraCima.ponto1.x = horizontal;
                linhaPraCima.ponto2.x = horizontal;
                linhaPraCima.ponto2.y = nivel;
                linhaPraCima.esquerda = true; //Só pq quero
                linhas.push_back(linhaPraCima);


                Quadrado quadrado;
                quadrado.cabeca = false;
                quadrado.valor = no->valor;
                quadrado.ponto.x = horizontal;
                quadrado.ponto.y = nivel;
                quadrado.owner = this;
                quadrados.push_back(quadrado);
                representacaoDeNo(no->prox, nivel + 1, horizontal);
        }
}
