#ifndef ESTRUTURA_H
#define ESTRUTURA_H


class Estrutura
{
        public:
                Estrutura(char*);
                virtual ~Estrutura();
                virtual bool buscar(int) = 0;
                virtual bool inserir(int) = 0;
                virtual bool remover(int) = 0;
                char* getNome() const;
        protected:
        private:
                char* nome;
};

#endif // ESTRUTURA_H
