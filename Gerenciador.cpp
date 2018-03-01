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


#include "Gerenciador.h"
#include "AVL.h"
#include "BST.h"
#include "Splay.h"
#include "PrinterBinario.h"
#include "PrinterHash.h"
#include "BTree.h"
#include "BMaisTree.h"
#include "PrinterB.h"
#include "PrinterBMais.h"
#include <sstream>
#include "Hash.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int funcao(int x) //Função do hash
{
        return x;
}



std::wstring StringToWString(const std::string& s)
{
        std::wstring temp(s.length(),L' ');
        std::copy(s.begin(), s.end(), temp.begin());
        return temp;
}


std::string WStringToString(const std::wstring& s)
{
        std::string temp(s.length(), ' ');
        std::copy(s.begin(), s.end(), temp.begin());
        return temp;
}

int Gerenciador::numeroDeSalvos = 0;

Gerenciador::Gerenciador()
{
        //Cria a janela
        srand(time(NULL));
	janela = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(260, 400), 32, false);
	janela->setWindowCaption(L"Estrutura de Dados");

	video = janela->getVideoDriver();
        ambiente = janela->getGUIEnvironment();
        IGUISkin* novaSkin = ambiente->createSkin(EGST_WINDOWS_METALLIC );
        ambiente->setSkin(novaSkin);
        ambiente->getSkin()->setFont(ambiente->getFont("Century10.xml"));


        estruturas = new Estrutura*[ed_cont];
        printers = new Printer*[ed_cont];
        logs = new std::list<Log>[ed_cont];
        estruturaAtiva = new bool[ed_cont];
        criado = new IGUICheckBox*[ed_cont];
        exibido = new IGUICheckBox*[ed_cont];
        ativo = new IGUICheckBox*[ed_cont];
        for (int i = 0; i < ed_cont; ++i) //Inicializa as variáveis de controle
        {
                estruturaAtiva[i] = false;
                estruturas[i] = NULL;
                printers[i] = NULL;
        }
        setUpScene();
}

Gerenciador::~Gerenciador()
{
        for (int i = 0; i < ed_cont; ++i) //Desaloca internamente
        {
                delete estruturas[i];
                delete printers[i];
                logs[i].clear();
        }
        delete[] ativo;
        delete[] criado;
        delete[] exibido;
        delete[] estruturas;
        delete[] printers;
}

void Gerenciador::run() //Método principal
{
        while (janela->run() && video)
        {
                video->beginScene(true, true, video::SColor(255,192,192,192));
                update();
                desenhaEstruturas();
                ambiente->drawAll();
                video->endScene();
        }
        janela->drop();
}

void Gerenciador::setUpScene()
{
        //Cria botão abrir/salvar
        //Cria campo de texto do nome de arquivo
       int origemX = 20;
        int origemY = 60;

        campoTexto = ambiente->addEditBox(L"",rect<s32>(origemX,origemY - 40, 220 + origemX,origemY - 10),true);
        campoTexto->setTextAlignment(EGUIA_LOWERRIGHT, EGUIA_CENTER);
        campoTexto->setEnabled(false);
        for (int linha = 0; linha < 3; ++linha) // Teclado Numérico
        {
                for (int coluna = 0; coluna < 3; ++coluna)
                {
                        stringstream numero;
                        numero<<(linha*3 + coluna + 1);
                        ambiente->addButton(rect<s32>(coluna*80 + origemX, linha*30 + origemY ,coluna*80 + 60 + origemX , linha*30 + 30 + origemY ), NULL, bt_Numero,
                                                (StringToWString(numero.str())).c_str());
                }
        }

        //Botão Aleatório, Zero, Apaga
        ambiente->addButton(rect<s32>(origemX,100 + origemY, 60 + origemX,130 + origemY), NULL, bt_Aleatorio, L"Random");
        ambiente->addButton(rect<s32>(80 + origemX,100 + origemY, 140 + origemX,130 + origemY), NULL, bt_Numero, L"0");
        ambiente->addButton(rect<s32>(160 + origemX,100 + origemY, 220 + origemX,130 + origemY), NULL, bt_Apaga, L"Apaga");


        //{ Botões de operação
        ambiente->addButton(rect<s32>(origemX,130 + origemY, 60 + origemX,160 + origemY), NULL, bt_Insert, L"Insert");
        ambiente->addButton(rect<s32>(80 + origemX,130 + origemY, 140 + origemX,160 + origemY), NULL, bt_Search, L"Search");
        ambiente->addButton(rect<s32>(160 + origemX,130 + origemY, 220 + origemX,160 + origemY), NULL, bt_Delete, L"Delete");
        //}

        //Botão abrir, salvar e nome do arquivo
        nomeArquivoAbrirSalvar = ambiente->addEditBox(L"nome do arquivo",rect<s32>(origemX,origemY + 190, 220 + origemX,origemY +220),true);
        nomeArquivoAbrirSalvar->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_CENTER);
        ambiente->addButton(rect<s32>(origemX,220 + origemY, 100 + origemX,250 + origemY), NULL, bt_Abrir, L"Abrir");
        ambiente->addButton(rect<s32>(origemX + 120,220 + origemY, 220 + origemX,250 + origemY), NULL, bt_Salvar, L"Salvar");

        //Combo Box
        origemY += 100;
        comboBox = ambiente->addComboBox(rect<s32>(origemX,170 + origemY, 140 + origemX,200 + origemY));
        comboBox->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
        comboBox->addItem(L"AVL");
        comboBox->addItem(L"BST");
        comboBox->addItem(L"Splay");
        comboBox->addItem(L"B");
        comboBox->addItem(L"BMais *");
        comboBox->addItem(L"Hash");

        //Spin
        spin = ambiente->addSpinBox(L"Ordem", rect<s32>(origemX + 140,170 + origemY,220 + origemX,200 + origemY), true);
        spin->setRange(1,10);
        spin->setDecimalPlaces(0);
        origemY -= 10;
        //Check Box
        for (int i = 0; i < ed_cont; ++i)
        {
                criado[i] = ambiente->addCheckBox (false, rect<s32>(origemX,220 + origemY,190+origemX,240 + origemY), 0, -1, L"Criar");
                ativo[i] = ambiente->addCheckBox (false, rect<s32>(origemX + 80,220 + origemY,270+origemX,240 + origemY), 0, -1, L"Ativar");
                exibido[i] = ambiente->addCheckBox (false, rect<s32>(origemX + 160,220 + origemY,350+origemX,240 + origemY), 0, -1, L"Exibir");
        }
}

int Gerenciador::getNumero() //Transforma o campo texto em inteiro, e esvazia o campo texto
{
        if ( WStringToString(campoTexto->getText()).size() > 0)
        {
                int x = atoi(WStringToString(campoTexto->getText()).c_str());
                campoTexto->setText(L"");
                return x;
        }
        throw (-1);
}

void Gerenciador::inserir(int valor) //As outras operações fazem a mesma coisa
{
        for (int i = 0; i < ed_cont; ++i)
        {
                if (estruturaAtiva[i]) //Se está ativa é pq já foi criada
                {
                        Clock clock;
                        bool resultado = estruturas[i]->inserir(valor); //Insere na estrutura
                        float deltaTempo = clock.GetElapsedTime();
                        logs[i].push_back(
                                Log(deltaTempo, resultado, valor, op_insert) //Adiciona ao log
                                                        );
                        Printer::SetElementoDestacado(valor);
                        if (printers[i])
                                printers[i]->refresh();
                }
        }
}

void Gerenciador::remover(int valor ) //Semelhante a inserção
{
        for (int i = 0; i < ed_cont; ++i)
        {
                if (estruturaAtiva[i]) //Se está ativa é pq já foi criada
                {
                        Clock clock;
                        bool resultado = estruturas[i]->remover(valor); //Insere na estrutura
                        float deltaTempo = clock.GetElapsedTime();
                        logs[i].push_back(
                                Log(deltaTempo, resultado, valor, op_delete) //Adiciona ao log
                                                        );
                        Printer::SetElementoDestacado(valor);
                        if (printers[i])
                                printers[i]->refresh();
                }
        }
}

void Gerenciador::buscar(int valor) //Semelhante a inserção
{
        for (int i = 0; i < ed_cont; ++i)
        {
                if (estruturaAtiva[i]) //Se está ativa é pq já foi criada
                {
                        Clock clock;
                        bool resultado = estruturas[i]->buscar(valor); //Insere na estrutura
                        float deltaTempo = clock.GetElapsedTime();
                        logs[i].push_back(
                                Log(deltaTempo, resultado, valor, op_search) //Adiciona ao log
                                                        );
                        Printer::SetElementoDestacado(valor);
                        if (printers[i])
                                printers[i]->refresh();
                }
        }
}

void Gerenciador::update() //Verifica comboBox, atualiza check box, atualiza Spinner, cria estruturas e printers
{
        verificaBotoes(); //Verificar os botões
        int id = comboBox->getSelected();
        if (id == -1)
        {
                comboBox->setSelected(0);
                id = 0;
        }

        for (int i = 0; i < ed_cont; ++i) //Selecionando quais checkbox serão exibidos
        {
                ativo[i]->setVisible(i==id);
                criado[i]->setVisible(i==id);
                exibido[i]->setVisible(i==id);
        }

        //Habilitando e desabilitando o spin
        spin->setVisible(id == ed_B || id == ed_Hash || id == ed_BMais);
        spin->setEnabled(!estruturas[id]);

        if (id == ed_Hash)
        {
                spin->setRange(1,100);
                if (estruturas[id])
                {
                        Hash* cast = static_cast<Hash*>(estruturas[id]);
                        spin->setValue(cast->getTH());
                }
        }
        else if (id == ed_B)
        {
                spin->setRange(1,20);
                if (estruturas[id])
                {
                        BTree* cast = static_cast<BTree*>(estruturas[id]);
                        spin->setValue(cast->getOrdem());
                }
        }
        else if (id == ed_BMais)
        {
                spin->setRange(1,20);
                if (estruturas[id])
                {
                        BMaisTree* cast = static_cast<BMaisTree*>(estruturas[id]);
                        spin->setValue(cast->getOrdem());
                }
        }

        int ordem = spin->getValue();
        if (criado[id]->isChecked()) //Controla se a estrutura está criada ou não
        {
                if (!estruturas[id]) //Onde eu crio as estruturas
                {
                        switch (id)
                        {
                                case ed_Avl:
                                                estruturas[id] = new AVL();
                                        break;
                                case ed_Bst:
                                                estruturas[id] = new BST();
                                        break;
                                case ed_Splay:
                                                estruturas[id] = new Splay();
                                        break;
                                case ed_B:
                                                estruturas[id] = new BTree(ordem);
                                        break;
                                case ed_BMais:
                                                estruturas[id] = new BMaisTree(ordem);
                                        break;
                                case ed_Hash:
                                                estruturas[id] = new Hash(ordem, funcao);
                                        break;
                        }
                }

                if (exibido[id]->isChecked()) //Se estiver sendo exibido
                {
                        if (!printers[id]) //Onde eu crio os printers caso não tenha sido criado ainda
                        {
                                switch (id)
                                {
                                        case ed_Avl:
                                        case ed_Bst:
                                        case ed_Splay:
                                                        {
                                                                ArvoreBinaria* ab = static_cast<ArvoreBinaria*>(estruturas[id]);
                                                                printers[id] = new PrinterBinario(*ab);
                                                        }
                                                break;
                                        case ed_B:
                                                        {
                                                                BTree* b = static_cast<BTree*>(estruturas[id]);
                                                                printers[id] = new PrinterB(*b);
                                                        }
                                                break;
                                        case ed_BMais:
                                                        {
                                                                BMaisTree* b = static_cast<BMaisTree*>(estruturas[id]);
                                                                printers[id] = new PrinterBMais(*b);
                                                        }
                                                break;
                                        case ed_Hash:
                                                        {
                                                                Hash* h = static_cast<Hash*>(estruturas[id]);
                                                                printers[id] = new PrinterHash(*h);
                                                        }
                                }
                        }
                }
        }
        if (!criado[id]->isChecked()) //Eu sei que um else soa reduntante
        {
                ativo[id]->setChecked(false);
                exibido[id]->setChecked(false);
                if (estruturas[id]) //Deleta a estrutura, se ela não estiver criada
                {
                        printf("Gerenciador deletou\n");
                        delete estruturas[id];
                        estruturas[id] = NULL;
                }
        }
        if (!exibido[id]->isChecked()) //Deleta a impressora, se ela não estiver criada
        {
                if (printers[id])
                {
                        delete printers[id];
                        printers[id] = NULL;
                }
        }
         estruturaAtiva[id] = ativo[id]->isChecked(); //Atualiza vetor de booleano de controle
}
void Gerenciador::verificaBotoes() //Verifica botões
{
              IGUIButton* botao = dynamic_cast<IGUIButton*> (ambiente->getFocus());
                if (botao)
                {
                        if (!estaAlgumBotaoSendoPressionado && botao->isPressed() )
                        {
                                switch (botao->getID())
                                {
                                        case bt_Numero:
                                                                {
                                                                        std::string nome = WStringToString(campoTexto->getText()).c_str();
                                                                        nome.append(WStringToString(botao->getText()));
                                                                        wstring novo = StringToWString(nome);
                                                                        campoTexto->setText(novo.c_str());
                                                                        estaAlgumBotaoSendoPressionado = true;
                                                                }
                                                break;
                                        case bt_Apaga:
                                                                campoTexto->setText(L"");
                                                                estaAlgumBotaoSendoPressionado = true;
                                                break;

                                        case bt_Aleatorio:
                                                                {
                                                                        int digito = rand()%10;
                                                                        stringstream numero;
                                                                        numero<<digito;
                                                                        std::string nome = WStringToString(campoTexto->getText()).c_str();
                                                                        nome.append(numero.str());
                                                                        wstring novo = StringToWString(nome);
                                                                        campoTexto->setText(novo.c_str());
                                                                        estaAlgumBotaoSendoPressionado = true;
                                                                }
                                                break;
                                        case bt_Insert:
                                                                try //Esse try é pra evitar um botão vazio
                                                                {
                                                                        inserir(getNumero());
                                                                }
                                                                catch(int)
                                                                {

                                                                }
                                                break;
                                        case bt_Search:
                                                                try //Esse try é pra evitar um botão vazio
                                                                {
                                                                        buscar(getNumero());
                                                                }
                                                                catch(int)
                                                                {

                                                                }
                                                break;
                                        case bt_Delete:
                                                                try //Esse try é pra evitar um botão vazio
                                                                {
                                                                        remover(getNumero());
                                                                }
                                                                catch(int)
                                                                {

                                                                }
                                                break;
                                        case bt_Salvar:
                                                                salvar();
                                                                estaAlgumBotaoSendoPressionado = true;
                                                break;
                                        case bt_Abrir:
                                                                abrir();
                                                                estaAlgumBotaoSendoPressionado = true;
                                                break;
                                }
                        }
                        else if (!botao->isPressed())
                                estaAlgumBotaoSendoPressionado = false;
                }
}
void Gerenciador::desenhaEstruturas() const
{
        for (int i = 0; i < ed_cont; ++i)
        {
                if (printers[i]) //Se o printer da estrutura estiver ativo
                {
                        printers[i]->draw();
                }
        }
}
void Gerenciador::salvar() //Salva todos os logs da estruturas criadas
{
        ++numeroDeSalvos;
        const char* fileName = WStringToString(nomeArquivoAbrirSalvar->getText()).c_str();
        for (int i = 0; i < ed_cont; ++i)
        {
                if (estruturaAtiva[i]) //Se tá ativa é pq tá alocada
                {
                        stringstream nomeArquivo;
                        nomeArquivo << fileName<<"_" << estruturas[i]->getNome();
                        if (i == ed_Hash)
                                nomeArquivo << "_t" << static_cast<Hash*>(estruturas[i])->getTH();
                        else if (i == ed_B)
                                nomeArquivo << "_t" << static_cast<BTree*>(estruturas[i])->getOrdem();
                        else if (i == ed_BMais)
                                nomeArquivo << "_t" << static_cast<BTree*>(estruturas[i])->getOrdem();
                        nomeArquivo << "_" << numeroDeSalvos<<".ed2s";
                        FILE* fp = fopen(nomeArquivo.str().c_str(), "wt");
                        fprintf(fp, "Valor\ttempo\topCode\tresult\n");
                        for (std::list<Log>::iterator it = logs[i].begin();
                                                it != logs[i].end(); ++it)
                        {
                                fprintf(fp, "%d\t%.9f\t%d\t%d\n", it->elemento, it->tempo, it->operacao, it->resultado);
                        }
                        fclose(fp);
                }
        }
        nomeArquivoAbrirSalvar->setText(L"Arquivo salvo");
}
void Gerenciador::abrir() //Abre um arquivo texto
{
        printf("Abrir\n");
        const char* fileName = WStringToString(nomeArquivoAbrirSalvar->getText()).c_str();
        FILE* fp = fopen(fileName, "rt");
        if (fp)
        {
                printf("Encontrou o arquivo: %s\n", fileName);
                int i = 0;
                while (!feof(fp)) //Percorre todo o arquivo
                {
                        ++i;
                        int elemento, operacao;
                        fscanf(fp,"%d\t%d\n", &operacao, &elemento);
                        //Já chama a operação, que consequentemente atualiza o log, verifica as estruturas e tudo
                        if (operacao == op_insert)
                                inserir(elemento);
                        else if (operacao == op_search)
                                buscar(elemento);
                        else if (operacao == op_delete)
                                remover(elemento);
                }
                printf("Quantidade: %d\n", i);
                nomeArquivoAbrirSalvar->setText(L"Arquivo lido com sucesso");
                fclose(fp);
        }
        else
                nomeArquivoAbrirSalvar->setText(L"Erro na leitura do arquivo");
}
