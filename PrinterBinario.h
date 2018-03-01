#ifndef PRINTERBINARIO_H
#define PRINTERBINARIO_H
#include <SFML/Graphics.hpp>
#include "Printer.h"
#include "ArvoreBinaria.h"
#include <vector>
#include <stdio.h>

using namespace sf;

class PrinterBinario: public Printer
{
        friend struct Circulo;
        public:
                PrinterBinario(ArvoreBinaria&);
                virtual ~PrinterBinario();
        protected:
		struct Circulo
		{
			void draw();
			int valor;
			Vector2f ponto;
			PrinterBinario* owner;
		};
        private:
                ArvoreBinaria* arvore;
                std::vector<Linha> linhas;
                std::vector<Circulo> circulos;
                virtual void childDraw();
                virtual void childRefresh();
		int representacaoDeNo(NoBinario* no, int ordem); //Retorna a minha posição em relação ao eixo x
};

#endif // PRINTERBINARIO_H
