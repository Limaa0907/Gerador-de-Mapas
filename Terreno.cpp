#include <iostream>
#include <fstream>
#include <algorithm> 
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Terreno.h"
#include "DiamondSquare.h"

Terreno::Terreno(int n){    //construtor que inicializa matriz_de_altitudes quadrada de (2^n + 1) com todas de valores -1.0
    quantidade_de_linhas = quantidade_de_colunas = pow(2, n) + 1;

    std::cout << "Linhas = " << quantidade_de_linhas << ", Colunas = " << quantidade_de_colunas << std::endl;

    if (quantidade_de_linhas <= 0 || quantidade_de_colunas <= 0){
        std::cerr << "Erro: tamanho inválido para a matriz" << std::endl;
        exit(1);
    }

    matriz_de_altitudes = new double*[quantidade_de_linhas];

    for (int i = 0; i < quantidade_de_linhas; i++){
        matriz_de_altitudes[i] = new double[quantidade_de_colunas];
        for (int j = 0; j < quantidade_de_linhas; j++){
            matriz_de_altitudes[i][j] = -1.0; // valor default
        }
    }
}

int Terreno::_getQuantidadeLinhas(){    //adquire o objeto privado quantidade_de_linhas para ser utilizado
    return quantidade_de_linhas;
}

int Terreno::_getQuantidadeColunas(){   //adquire o objeto privado quantidade_de_colunas para ser utilizado
    return quantidade_de_colunas;
}

double Terreno::_consultarAltitude(int row, int column){    //retorna a altitude da posição (row, column) ou -1.0 se estiver fora dos limites.
    if (row >= 0 && row < this->quantidade_de_linhas && column >= 0 && column < this->quantidade_de_colunas){
        return this->matriz_de_altitudes[row][column];
    }
    return -1.0; // valor inválido
}

bool Terreno::_salvarArquivo(const std::string &name){  //salva matriz_de_altitudes em um arquivo de texto
    std::ofstream arquivo(name);

    if (!arquivo.is_open()){
        return false;
    }

    arquivo << quantidade_de_linhas << " " << quantidade_de_colunas << std::endl;

    for (int i = 0; i < quantidade_de_linhas; i++){
        for (int j = 0; j < quantidade_de_colunas; j++){
            arquivo << matriz_de_altitudes[i][j];
            if (j < quantidade_de_colunas - 1){
                arquivo << " ";
            } 
        }
        arquivo << std::endl;
    }
    arquivo.close();
    return true;
}

bool Terreno::_lerArquivo(const std::string &name){ //lê uma nova matriz_de_altitudes de um arquivo, deleta a memória antiga, cria uma nova memória e atualiza o terreno
    std::ifstream arquivo(name);

    if (!arquivo.is_open()){
        return false;
    }

    int newrows;
    int newcolumns;
    arquivo >> newrows >> newcolumns;

    for (int i = 0; i < quantidade_de_linhas; i++){   //libera a memória que tava ocupada
        delete[] matriz_de_altitudes[i];
    }
    delete[] matriz_de_altitudes;

    quantidade_de_linhas = newrows;
    quantidade_de_colunas = newcolumns;

    matriz_de_altitudes = new double*[quantidade_de_linhas];
    for (int i = 0; i < quantidade_de_linhas; i++){
        matriz_de_altitudes[i] = new double[quantidade_de_colunas];
    }

    for (int i = 0; i < quantidade_de_linhas; i++){
        for (int j = 0; j < quantidade_de_colunas; j++){
            arquivo >> matriz_de_altitudes[i][j];
        }
    }
    arquivo.close();
    return true;
}

void Terreno::_limitarValor(int row, int column, double value){ //evitar acesso de valores fora dos limites da matriz
    if (row >= 0 && row < quantidade_de_linhas && column >= 0 && column < quantidade_de_colunas){
        matriz_de_altitudes[row][column] = value;
    }
}

Terreno::~Terreno() {
    for (int i = 0; i < quantidade_de_linhas; i++){ //libera a memória alocada para matriz_de_altitudes
        delete[] matriz_de_altitudes[i];
    }
    delete[] matriz_de_altitudes;
}