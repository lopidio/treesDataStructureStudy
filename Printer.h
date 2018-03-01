#ifndef PRINTER_H
#define PRINTER_H
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <sstream>
#include "Estrutura.h"


using namespace sf;

class Printer
{
        friend struct Linha;
	public:
		Printer(Estrutura*);
		~Printer();
		void refresh();
		void draw();
		static void SetElementoDestacado(int novoElemento);
		float getEspacamentoHorizontal() const;
		float getEspacamentoVertical() const;
		int getElementoDestacado() const;
		Vector2f origem;
		RenderWindow* app;
		float getZoom() const;
	private:
		virtual void childDraw() = 0;
		virtual void childRefresh() = 0;
		static int elementoDestacado;
		void eventHandler();
		void input();
		float espacamentoVertical;
		float espacamentoHorizontal;
		float zoom;
	protected:
                char* nome;
                int numeroDeNosImpressos;
                int numeroDeOrdensImpressas;
		struct Linha
		{
		        bool esquerda;
		        Vector2f ponto1;
		        Vector2f ponto2;
			void draw();
                        Printer* owner;
		};
};



#endif // PRINTER_H
