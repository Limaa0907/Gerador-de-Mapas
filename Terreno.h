#ifndef TERRENO_H
#define TERRENO_H
#include <string>
#include "Paleta.h"
#include "Imagem.h"

class Terreno{
    private:
        int quantidade_de_linhas;
        int quantidade_de_colunas;
        double** matriz_de_altitudes;

    public:
        Terreno(int n);

        int _getQuantidadeLinhas();
        int _getQuantidadeColunas();
        void _gerarAltitude(double roughness);
        double _consultarAltitude(int row, int column);
        bool _salvarArquivo(const std::string &name);
        bool _lerArquivo(const std::string &name);
        void _limitarValor(int row, int column, double value);


        void _funcaoMatrizDeAltitudes(int n, double roughness, int maxvalue);
        void _diamondSquare(int step, double roughness);
        void _diamondStep(int step, double roughness);
        void _squareStep(int step, double roughness);
        double _gerarAleatorio(double maxvalue);
      
        Imagem* _sombreamento(Paleta palette);
        void _suavizarTerreno(int iterator);

        ~Terreno();
};

#endif