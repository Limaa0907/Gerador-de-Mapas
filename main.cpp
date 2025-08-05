#include <iostream>
#include <cmath>
#include <string>
#include "Paleta.h"
#include "Imagem.h"
#include "Terreno.h"

int main (){
    std::string palettename;
    std::string ppmname;
    int n;
    double roughness;

    std::cout << "Insira o nome do arquivo a ser lido: " << std:: endl;
    std::cin >> palettename;
    std::cout << "Insira o N (da matriz) e a rugosidade dela: " << std::endl;
    std::cin >> n >> roughness;
    std::cout << "Insira o nome do arquivo PPM a ser salvo: " << std::endl;
    std::cin >> ppmname;

    Terreno terreno(n);
    terreno._funcaoMatrizDeAltitudes(n, roughness, 255);

    Paleta paleta;
    paleta._carregarArquivo(palettename);

    Imagem* imagem; 
    imagem = terreno._sombreamento(paleta);

    imagem->_salvaPPM(ppmname);
    delete imagem;

    return 0;
}

