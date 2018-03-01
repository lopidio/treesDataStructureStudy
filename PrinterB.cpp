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


#include "PrinterB.h"
#include "BTree.h"

PrinterB::PrinterB(BTree& b):Printer((Estrutura*)(&b))
{
        ordem = b.getOrdem();
        arvore = &b;
        largura = 20; //Largura de cada quadradin
}

PrinterB::~PrinterB()
{
        linhas.clear();
        paginas.clear();
}

void PrinterB::LinhaB::draw()
{
        Color cor = Color::White;
        Shape linha = Shape::Line (ponto1.x * owner->getEspacamentoHorizontal() + owner->origem.x + xInterno*largura - static_cast<PrinterB*>(owner)->ordem*largura,
                                                  ponto1.y *     owner->getEspacamentoVertical() + owner->origem.y + largura,
                                                        ponto2.x * owner->getEspacamentoHorizontal() + owner->origem.x,
                                                        ponto2.y *     owner->getEspacamentoVertical() + owner->origem.y,
                                                        1.0f, cor);
        owner->app->Draw(linha);
}


void PrinterB::Pagina::draw()
{
        for (int i = 0; i < 2*static_cast<PrinterB*>(owner)->ordem; ++i)
        {
                //Calculo a cor
                int largura= owner->largura;
                sf::Color cor = Color::White;
                if ((i < tamanho) && (valores[i] == owner->getElementoDestacado()))
                        cor = Color::Yellow;
                //Calculando as dimensões
                Vector2f quinaSuperiorEsquerda( ponto.x * owner->getEspacamentoHorizontal() + owner->origem.x + i*largura - static_cast<PrinterB*>(owner)->ordem*largura,
                                                                        ponto.y * owner->getEspacamentoVertical() + owner->origem.y);
                Vector2f quinaInferiorDireita(quinaSuperiorEsquerda.x + largura, quinaSuperiorEsquerda.y + largura);
                //Desenha o quadrado
                owner->app->Draw(Shape::Rectangle(quinaSuperiorEsquerda, quinaInferiorDireita,
                                                        cor, 1.0f, Color::Black));

                if (i >= tamanho) //Se for maior que o tamanho só precisa desenhar o quadrado
                        continue;

                //Pegando o valor
                String valorStr;
                valorStr.SetSize(12);
                std::stringstream conversor;
                conversor << valores[i];
                valorStr.SetText(conversor.str());
                valorStr.SetColor(Color::Black);
                //Calculando o local de desenho
                int larguraTxt = valorStr.GetRect().Right - valorStr.GetRect().Left;
                int alturaTxt = valorStr.GetRect().Bottom - valorStr.GetRect().Top;
                valorStr.SetPosition(quinaInferiorDireita.x - 7.5f - larguraTxt/2, quinaInferiorDireita.y - 7.5f - alturaTxt/2 );
                //Desenhando
                owner->app->Draw(valorStr);
        }
}

void PrinterB::childDraw()
{
        for (int i = 0; i < linhas.size(); ++i)//vector<LinhaB>::iterator it = linhas.begin(); it != linhas.end(); it++)
        {
                linhas[i].draw();
        }

        for (int i = 0; i < paginas.size(); ++i)//vector<Pagina>::iterator it = paginas.begin(); it != paginas.end(); it++)
        {
                paginas[i].draw();
        }
}

void PrinterB::childRefresh()
{
        paginas.clear();
        linhas.clear();
        numeroDeNosImpressos = 0; //Número de folhas
        numeroDeOrdensImpressas = 0;
        if (arvore->raiz)
                representacaoDeNo(arvore->raiz, 0);
}

float PrinterB::representacaoDeNo(BNode* no, int nivel)
{
        if (no->eFolha()) // Se eu sou folha, só preciso calcular minha posição
        {
                Pagina pagina;
                pagina.valores = no->chave;
                pagina.tamanho = no->tamanho;
                pagina.owner = this;
                pagina.ponto.x = ++numeroDeNosImpressos; // Conta quantas folhas existem
                pagina.ponto.y = nivel;
                paginas.push_back(pagina);
                return (float)numeroDeNosImpressos;
        }
        else
        {
                float somatorio = 0; //Armazenará minha posição
                int numeroFilhos = no->tamanho + 1;
                float xDosFilhos[2*ordem + 1]; // = no->tamanho + 1
                //Mando desenhar os filhos e calculo a posição deles
                for (int i = 0; i < numeroFilhos; ++i)
                {
                        xDosFilhos[i] = 0;
                        xDosFilhos[i] += representacaoDeNo(no->filho[i], nivel + 1);
                        somatorio += xDosFilhos[i];
                }
                float retorno = somatorio/ (float)numeroFilhos; //Cálculo da minha posição x
                Pagina pagina;
                pagina.tamanho = no->tamanho;
                pagina.valores = no->chave;
                pagina.owner = this;
                pagina.ponto.x = retorno;
                pagina.ponto.y = nivel;
                paginas.push_back(pagina);

                for (int i = 0; i < numeroFilhos; ++i) //Uma linha pra cada filho
                {
                        LinhaB linha;
                        linha.owner = this;
                        linha.ponto1.x = retorno;// + largura*i; //Isso não tá certo
                        linha.ponto1.y = nivel;// + largura;
                        linha.xInterno = i;
                        linha.largura = largura;
                        linha.ponto2.x = xDosFilhos[i];
                        linha.ponto2.y = nivel + 1;
                        linhas.push_back(linha);
                }
                return retorno;
        }
}
