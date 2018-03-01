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


#include "PrinterBinario.h"

/** @brief PrinterBinario
  *
  * @todo: document this function
  */
 PrinterBinario::PrinterBinario(ArvoreBinaria& arvore_):Printer(&arvore_)
{
        arvore = &arvore_;
        refresh();
}

PrinterBinario::~PrinterBinario()
{
        linhas.clear();
        circulos.clear();
}

/** @brief draw
  *
  * @todo: document this function
  */
void PrinterBinario::Circulo::draw()
{
        sf::Color cor;
        cor = Color::White;
        if (valor == owner->getElementoDestacado())
                cor = Color::Yellow;
        Shape circulo = Shape::Circle(ponto.x * owner->getEspacamentoHorizontal() + owner->origem.x,
                                                         ponto.y *     owner->getEspacamentoVertical() + owner->origem.y,
                                                        12, cor, 1.f, Color::Black);
        owner->app->Draw(circulo);
        String valorStr;
        valorStr.SetColor(Color::Black);
        valorStr.SetSize(12);
        std::stringstream conversor;

        conversor << valor;
        valorStr.SetText(conversor.str());
        int largura = valorStr.GetRect().Right - valorStr.GetRect().Left;
        int altura = valorStr.GetRect().Bottom - valorStr.GetRect().Top;
        valorStr.SetPosition(ponto.x * owner->getEspacamentoHorizontal() + owner->origem.x - largura/2,
                                        ponto.y *     owner->getEspacamentoVertical() + owner->origem.y- altura/2);
        owner->app->Draw(valorStr);
}

/** @brief representacaoDeNo
  *
  * @todo: document this function
  */
int PrinterBinario::representacaoDeNo(NoBinario* no, int nivel) //Retorna a posição X do nó
{
        Circulo circulo;
        circulo.valor = no->chave;
        circulo.ponto.y = nivel;
        if (nivel > numeroDeOrdensImpressas)
                numeroDeOrdensImpressas = nivel;
        circulo.owner = this;
        if (no->esquerda)
        {
                int ordemEsquerda = representacaoDeNo(no->esquerda, nivel+1);
                Linha linha;
                linha.esquerda = true;
                linha.owner = this;
                linha.ponto1.x = numeroDeNosImpressos+1; //Ponto 1 = mim
                linha.ponto1.y = nivel;
                linha.ponto2.x = ordemEsquerda;
                linha.ponto2.y = nivel + 1;
                linhas.push_back(linha);
        }
        int retorno;
        circulo.ponto.x = ++numeroDeNosImpressos; //Eu mesmo
        retorno = circulo.ponto.x;
        circulos.push_back(circulo);
        if (no->direita)
        {
                int ordemDireita = representacaoDeNo(no->direita, nivel+1);
                Linha linha;
                linha.owner = this;
                linha.esquerda = false;
                linha.ponto1.x = retorno;
                linha.ponto1.y = nivel;
                linha.ponto2.x = ordemDireita;
                linha.ponto2.y = nivel + 1;
                linhas.push_back(linha);
        }
        return retorno;
}

/** @brief childRefresh
  *
  * @todo: document this function
  */
void PrinterBinario::childRefresh()
{
        //limpa círculos e linhas
        numeroDeNosImpressos = 0;
        numeroDeOrdensImpressas = 0;
        linhas.clear();
        circulos.clear();
        if (arvore->raiz)
                representacaoDeNo(static_cast<NoBinario*>(arvore->raiz), 0);
}

/** @brief childDraw
  *
  * @todo: document this function
  */
void PrinterBinario::childDraw()
{
        //desenha todas as linhas
        for (std::vector<Linha>::iterator it = linhas.begin(); it != linhas.end(); ++it)
        {
                it->draw();
        }
        //desenha todos os círculos
        for (std::vector<Circulo>::iterator it = circulos.begin(); it != circulos.end(); ++it)
        {
                it->draw();
        }
}


