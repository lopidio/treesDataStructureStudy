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


#include "Printer.h"

int Printer::elementoDestacado = 50;

Printer::Printer(Estrutura* ed)
{
        app = new sf::RenderWindow();
        nome = ed->getNome();
        app->Create(VideoMode(500,400,24), nome, Style::Titlebar );        //cria a janela
        origem.x = 100;
        origem.y = 10;
        espacamentoHorizontal = 0;
        espacamentoVertical = 0;
        zoom = 1;
}

Printer::~Printer()
{
        if (app)
                app->Close();
        app = NULL;
}

/** @brief eventHandler
  *
  * @todo: document this function
  */
void Printer::eventHandler()
{
//	Event Event;
//        while ( app->GetEvent ( Event ) )
//        {
//                if  ( ( Event.Type == sf::Event::Closed ) ||
//                     ((Event.Type == sf::Event::KeyPressed )  && ( Event.Key.Code == sf::Key::Escape )) )
//                {
//                                delete this;
//                                break;
//                }
//        }
}


void Printer::refresh()
{
        //Recalcula os espaçamentos padrão e esse leriado
        childRefresh();

        espacamentoVertical =  app->GetHeight()/(numeroDeOrdensImpressas + 4 );
        espacamentoHorizontal =  app->GetWidth()/(numeroDeNosImpressos + 4 );
        origem.x = app->GetWidth()/2 - float(abs(numeroDeNosImpressos))*espacamentoHorizontal/2;
        origem.y = app->GetHeight()/2 - float(abs(numeroDeOrdensImpressas))*espacamentoVertical/2;
}


void Printer::draw()
{
        eventHandler();
        app->Clear(Color(200,200,200));
        if (app)
        {
                input();
                childDraw();
                app->Display();
        }
        //Calcula os espaçamentos de acordo com a posição do scroll e assim vai
}

/** @brief Input
  *
  * @todo: document this function
  */
void Printer::input()
{
        float modificador = 0.1;
        const Input& key = app->GetInput();
        if (key.IsKeyDown(Key::Space))
                modificador = 0.5;

        if (key.IsKeyDown(Key::W))
                espacamentoVertical -= 1*modificador;
        else if (key.IsKeyDown(Key::S))
                espacamentoVertical +=1*modificador;
        if (key.IsKeyDown(Key::A))
                espacamentoHorizontal -= 1*modificador;
        else if (key.IsKeyDown(Key::D))
                espacamentoHorizontal += 1*modificador;

        if (key.IsKeyDown(Key::Down))
                origem.y += 5*modificador;
        else if (key.IsKeyDown(Key::Up))
                origem.y -= 5*modificador;
        if (key.IsKeyDown(Key::Left))
                origem.x -= 5*modificador;
        else if (key.IsKeyDown(Key::Right))
                origem.x += 5*modificador;

        static int numero = 0;
        if (key.IsKeyDown(Key::F1))
        {
                numero++;
                std::stringstream conversor;
                sf::Image imagem = app->Capture();
                conversor << "ScreenShot "<<nome<<"_" <<numero<<".jpg";
                imagem.SaveToFile(conversor.str());
        }
}

void Printer::SetElementoDestacado(int novoElemento)
{
        elementoDestacado = novoElemento;
}

void Printer::Linha::draw()
{
        Color cor = Color::White;
        if (esquerda)
                cor = Color::Black;
        Shape linha = Shape::Line (ponto1.x * owner->getEspacamentoHorizontal() + owner->origem.x,
                                                  ponto1.y *     owner->getEspacamentoVertical() + owner->origem.y,
                                                        ponto2.x * owner->getEspacamentoHorizontal() + owner->origem.x,
                                                        ponto2.y *     owner->getEspacamentoVertical() + owner->origem.y,
                                                        1.0f, cor);
        owner->app->Draw(linha);
}

/** @brief getElementoDestacado
  *
  * @todo: document this function
  */
int Printer::getElementoDestacado() const
{
        return elementoDestacado;
}

/** @brief getEspacamentoVertical
  *
  * @todo: document this function
  */
float Printer::getEspacamentoVertical() const
{
        return espacamentoVertical;
}

/** @brief getEspacamentoHorizontal
  *
  * @todo: document this function
  */
float Printer::getEspacamentoHorizontal() const
{
        return espacamentoHorizontal;
}


float Printer::getZoom() const
{
        return zoom;
}
