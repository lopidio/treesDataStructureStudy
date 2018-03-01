#ifndef PRINTERB_H
#define PRINTERB_H
#include "Stdio.h"
#include <vector>
#include "Printer.h"

using namespace std;

class BTree;
struct BNode;


class PrinterB: public Printer
{
        friend struct Pagina;
        public:
                PrinterB(BTree& b);
                virtual ~PrinterB();
        protected:
                struct LinhaB: public Linha
                {
                        int xInterno, largura;
                        void draw();
                };
		struct Pagina
		{
		        int* valores;
		        int tamanho;
		        Vector2f ponto;
		        PrinterB* owner;
			void draw();
		};
        private:
                int ordem;
		BTree* arvore;
		vector<LinhaB> linhas;
		vector<Pagina> paginas;
		int largura;
		virtual void childDraw();
		virtual void childRefresh();
		float representacaoDeNo(BNode* no, int nivel);
};

#endif // PRINTERB_H
