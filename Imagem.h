#ifndef IMAGEM_H
#define IMAGEM_H
#include <string>
#include "Paleta.h"

class Imagem{
    private:
        int quantidade_de_linhas;
        int quantidade_de_colunas;    
        Cor** matriz_de_pixels;

    public:

    Imagem(int rows, int columns);  // rows = linhas, columns = colunas

    int _getQuantidadeLinhas();
    int _getQuantidadeColunas();
    
    Cor _consultaPixel(int r, int c);   //r para indice de rows, c para indice de columns
    void _defineCorPixel(int r, int c, Cor color);

    bool _salvaPPM(const std::string& name);

    ~Imagem();

};

#endif