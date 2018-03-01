#ifndef PRINTERBMAIS_H
#define PRINTERBMAIS_H
#include "Stdio.h"
#include <vector>
#include "Printer.h"

using namespace std;

class BMaisTree;
struct BMaisNode;


class PrinterBMais: public Printer
{
        friend struct Pagina;
        public:
                PrinterBMais(BMaisTree& b);
                virtual ~PrinterBMais();
        protected:
                struct LinhaBMais: public Linha
                {
                        int xInterno, largura;
                        void draw();
                };
		struct PaginaBMais
		{
		        bool eFolha;
		        int* valores;
		        int tamanho;
		        Vector2f ponto;
		        PrinterBMais* owner;
			void draw();
		};
        private:
                int ordem;
                float menorX, maiorX, y;
		BMaisTree* arvore;
		vector<LinhaBMais> linhas;
		vector<PaginaBMais> paginas;
		int largura;
		virtual void childDraw();
		virtual void childRefresh();
		float representacaoDeNo(BMaisNode* no, int nivel);
};

#endif // PRINTERBMAIS_H
