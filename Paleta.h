#ifndef PALETA_H
#define PALETA_H
#include <string>

int const MAX = 100;

struct Cor{
    int r;
    int g;
    int b;
};

class Paleta{
    private:
        int quantidade_de_cores;
        Cor cores[MAX];
        float valores[MAX];

    public:
        Paleta ();

        bool _carregarArquivo(const std::string& name);
        void _inicializarCor(int quantity, Cor color[], float value[]);
        Cor _consultaCor(float value);

        int _getQuantidade();
        Cor _getCores(int index);
        float _getValores(int index);
};

#endif
