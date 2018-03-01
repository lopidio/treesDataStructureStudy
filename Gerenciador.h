#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Printer.h"
#include <irrlicht.h>
#include <list>

using namespace irr;
using namespace video;
using namespace core;
using namespace gui;
using namespace std;

enum edTipo{ed_Avl, ed_Bst, ed_Splay, ed_B, ed_BMais, ed_Hash, ed_cont};
enum opCode{op_insert, op_search, op_delete};
enum btId {  bt_Insert,
                        bt_Delete,
                        bt_Search,
                        bt_Numero,
                        bt_Aleatorio,
                        bt_Apaga,
                        bt_Abrir,
                        bt_Salvar,
};

struct Log
{
	Log(float tempo_, bool resultado_, int elemento_, opCode operacao_) //Construtor
	{
		tempo = tempo_;
		resultado = resultado_;
		elemento = elemento_;
		operacao = operacao_;
	}
	float tempo;
	bool resultado;
	int elemento;
	opCode operacao;
};

class Gerenciador
{
        public:
                Gerenciador();
                virtual ~Gerenciador();
		void run(); //Método principal
        protected:
        private:
                //Atributos
		static int numeroDeSalvos;
		bool estaAlgumBotaoSendoPressionado;
		bool *estruturaAtiva;
		IGUICheckBox **criado, **ativo, **exibido;
		IGUISpinBox *spin;
		Estrutura** estruturas;
		Printer** printers;
		std::list<Log>* logs;
		IGUIComboBox* comboBox;
		IrrlichtDevice* janela;
		IGUIEnvironment* ambiente;
		IVideoDriver* video;
		IGUIButton *abrirBotao, *salvarBotao;
		IGUIEditBox *nomeArquivoAbrirSalvar;
		IGUIEditBox* campoTexto;
		//Métodos
		void setUpScene(); //Cria todo o cenário
		int getNumero(); //Transforma o campo texto em inteiro, e esvazia o campo texto
		void inserir(int valor); //As outras operações fazem a mesma coisa
		void remover(int ); //Semelhante a inserção
		void buscar(int); //Semelhante a inserção
		void update(); //Verifica comboBox, atualiza check box, atualiza Spinner, cria estruturas e printers
		void verificaBotoes();
		void desenhaEstruturas() const;
		void salvar(); //Salva todos os logs da estruturas criadas
		void abrir(); //Abre um arquivo texto
};

#endif // GERENCIADOR_H
