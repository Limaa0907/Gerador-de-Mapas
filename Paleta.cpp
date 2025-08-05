#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Paleta.h"

Paleta::Paleta(){   //inicializa quantidade de cores com 0
    quantidade_de_cores = 0;
}

bool Paleta::_carregarArquivo(const std::string& name){ //le a paleta de valores e cores e preenche os arrays de valores e cores
    std::ifstream arquivo(name);

    if (!arquivo) {
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        return false;
    }

    arquivo >> quantidade_de_cores;

    for(int i = 0; i < quantidade_de_cores; i++){
        float value;
        int r, g, b;
        arquivo >> value >> r >> g >> b;

        valores[i] = value;
        cores[i] = {r, g, b};
    }

    arquivo.close();
    return true;
}


void Paleta::_inicializarCor(int quantity, Cor color[], float value[]){ //inicializa a paleta manualmente com quantity cores, a partir de dois arrays: um de cores e outro de valores
    quantidade_de_cores = quantity;

    for(int i = 0; i < quantidade_de_cores; i++){
        cores[i] = color[i];
        valores[i] = value[i];
    }
}

Cor Paleta::_consultaCor(float value){  //retorna a cor correspondente a um valor value, fazendo transição linear entre duas cores vizinhas
    if (value <= valores[0]){
        return cores[0];
    }
    if (value >= valores[quantidade_de_cores - 1]){
        return cores[quantidade_de_cores - 1];
    }

    for(int i = 0 ; i < quantidade_de_cores - 1 ; i++){
        if(value >= valores[i] && value < valores[i+1]){
            float position = (value - valores[i]) / (valores[i+1] - valores[i]); //posição relativa no intervalo i & i+1

            Cor color1 = cores[i];   //obtém as cores do início e fim do intervalo
            Cor color2 = cores[i+1];

            int r_transition = static_cast<int>(color1.r + (color2.r - color1.r) * position);    //suavizar a transição entre cores
            int g_transition = static_cast<int>(color1.g + (color2.g - color1.g) * position);
            int b_transition = static_cast<int>(color1.b + (color2.b - color1.b) * position);

           
            r_transition = std::max(0, std::min(255, r_transition));     //garante que os valores fiquem entre 0 e 255 
            g_transition = std::max(0, std::min(255, g_transition));
            b_transition = std::max(0, std::min(255, b_transition));

            return {r_transition, g_transition, b_transition};
        }
    }
    return cores[quantidade_de_cores - 1];
}

int Paleta::_getQuantidade(){   //adquire o objeto privado quantidade_de_linhas para ser utilizado
    return quantidade_de_cores;
}

Cor Paleta::_getCores(int index){   //adquire o objeto privado cores para ser utilizado
    return cores[index];
}

float Paleta::_getValores(int index){   //adquire o objeto privado valores para ser utilizado
    return valores[index];
}