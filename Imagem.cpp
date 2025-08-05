#include <fstream>
#include <algorithm>
#include <string>
#include "Paleta.h"
#include "Imagem.h"


Imagem::Imagem(int rows, int columns){  //construtor que cria uma matriz de pixels do tamanho especificado e inicializa todos com a cor preta {0,0,0}.
    quantidade_de_linhas = rows;
    quantidade_de_colunas = columns;

    matriz_de_pixels = new Cor*[rows];

    for (int i = 0; i < rows; i++){
        matriz_de_pixels[i] = new Cor[columns];

        for(int j = 0; j < columns; j++){
            matriz_de_pixels[i][j] = {0,0,0};
        }
    }
}

int Imagem::_getQuantidadeLinhas(){ //adquire o objeto privado quantidade_de_linhas para ser utilizado
    return quantidade_de_linhas;
}

int Imagem::_getQuantidadeColunas(){    //adquire o objeto privado quantidade_de_colunas para ser utilizado
    return quantidade_de_colunas;
}

Cor Imagem::_consultaPixel(int r, int c){   //retorna a cor armazenada do pixel na posição (r, c) ou {0,0,0} (preto) se estiver fora dos limites (saber qual cor esta em um ponto)
    int i = r;
    int j = c;

    if((i >= 0 && i < quantidade_de_linhas) && (j >= 0 && j < quantidade_de_colunas)){
        return matriz_de_pixels[i][j];
    }
    else{
        return {0, 0, 0}; // Cor preta
    }
}

void Imagem::_defineCorPixel(int r, int c, Cor color){  //define a cor armazenada do pixel na posição (r, c) ou (i, j) se estiver dentro dos limites (pinta um ponto)
    int i = r;
    int j = c;

    if(i >= 0 && i < quantidade_de_linhas && j >= 0 && j < quantidade_de_colunas){
        matriz_de_pixels[i][j] = color;
    }
}

bool Imagem::_salvaPPM(const std::string &name){    //salva o arquivo no formato ppm (P3) e le as informações requisitdas
    std::ofstream arquivo(name);

    if(!arquivo.is_open()){
        return false;
    }

    arquivo << "P3" << std::endl;
    arquivo << quantidade_de_colunas << " " << quantidade_de_linhas << std::endl;
    arquivo << "255" << std::endl;

    for(int i = 0; i < quantidade_de_linhas; i++){
        for(int j = 0 ; j < quantidade_de_colunas; j++){
            Cor coloring = matriz_de_pixels[i][j];
            int r = std::clamp(coloring.r, 0, 255);
            int g = std::clamp(coloring.g, 0, 255);
            int b = std::clamp(coloring.b, 0, 255);

            arquivo << r << " " << g << " " << b << " ";
        }
        arquivo << std::endl;
    }
    arquivo.close();
    return true;
}

Imagem::~Imagem(){  //libera a memória alocada para matriz_de_pixels
    for (int i = 0; i < quantidade_de_linhas; i++) {
        delete[] matriz_de_pixels[i];
    }
    delete[] matriz_de_pixels;
}
