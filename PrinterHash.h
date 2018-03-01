#ifndef PRINTERHASH_H
#define PRINTERHASH_H
#include "Printer.h"
#include <vector>
#include <stdio.h>

using namespace sf;
using namespace std;

class Hash;
class Lista;
struct Elemento;

class PrinterHash: public Printer
{
        friend struct Quadrado;
        public:
                PrinterHash(Hash &hash_);
                virtual ~PrinterHash();
        protected:
                struct Quadrado
                {
		        bool cabeca;
		        int valor;
		        Vector2f ponto;
		        Printer* owner;
			void draw();
		};
        private:
                Hash* hash;
		std::vector<Linha> linhas;
		std::vector<Quadrado> quadrados;
		virtual void childDraw();
		virtual void childRefresh();
		void representacaoDeNo(Elemento*, int, int);
};

#endif // PRINTERHASH_H
