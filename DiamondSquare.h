#ifndef DIAMOND_SQUARE_H
#define DIAMOND_SQUARE_H
#include <cstdlib> 
#include <cmath>

void Terreno::_funcaoMatrizDeAltitudes(int n, double roughness, int maxvalue){  //inicializa variaveis que serão usadas na função, além de alocar e re-alocar a matriz, e por fim inicializando aleatoriamente os 4 cantos da matriz
    int size = pow(2, n) + 1;
    int step = size - 1;
    int maxindex = step;

    if (quantidade_de_linhas != size || quantidade_de_colunas != size){
        for (int i = 0; i < quantidade_de_linhas; i++){
            delete[] matriz_de_altitudes[i];
        }
        delete[] matriz_de_altitudes;

        quantidade_de_linhas = quantidade_de_colunas = size;
        matriz_de_altitudes = new double*[quantidade_de_linhas];
        for (int i = 0; i < quantidade_de_linhas; i++) {
            matriz_de_altitudes[i] = new double[quantidade_de_colunas];
            for (int j = 0; j < quantidade_de_colunas; j++) {
                matriz_de_altitudes[i][j] = -1.0; // Reinicializa
            }
        }
    }

    matriz_de_altitudes[0][0] = _gerarAleatorio(roughness * 1.0);
    matriz_de_altitudes[0][maxindex] = _gerarAleatorio(roughness * 1.0);
    matriz_de_altitudes[maxindex][0] = _gerarAleatorio(roughness * 1.0);
    matriz_de_altitudes[maxindex][maxindex] = _gerarAleatorio(roughness * 1.0);

    _diamondSquare(step, roughness);
}

void Terreno::_diamondSquare(int step, double roughness){   //função principal recursiva que subdivide em dois passos
    if (step <= 1){
        return;
    }
    int halfstep = step/2;

    _diamondStep(step, roughness);
    _squareStep(step, roughness);

    _diamondSquare(halfstep, roughness * 0.7);
}

void Terreno::_diamondStep(int step, double roughness){ //função diamond que encontra o valor central dos quadrantes e realiza o processo do Diamond Square de somar a media com o valor aleatório
    int halfstep = step/2;

    for (int i = halfstep; i < quantidade_de_linhas - 1; i += step){
        for (int j = halfstep; j < quantidade_de_colunas - 1; j += step){
            double corner1 = matriz_de_altitudes[i - halfstep][j - halfstep];
            double corner2 = matriz_de_altitudes[i - halfstep][j + halfstep];
            double corner3 = matriz_de_altitudes[i + halfstep][j - halfstep];
            double corner4 = matriz_de_altitudes[i + halfstep][j + halfstep];

            double media = (corner1 + corner2 + corner3 + corner4) / 4.0;
            double randomvalue = _gerarAleatorio(roughness);
            matriz_de_altitudes[i][j] = media + randomvalue;
        }
    }
}

void Terreno::_squareStep(int step, double roughness){  //função square que verifica os valores laterais/arestas dos quadrantes e verifica cada caso para somar a quantidade de quadrados adjacentes definidos e repete o processo do Diamons Square de somar os quadrados laterais com valor aleatorio
    int halfstep = step/2;

    for (int i = 0; i < quantidade_de_linhas; i += halfstep){
        for (int j = ((i / halfstep) % 2 == 0 ) ? (halfstep) : 0; j < quantidade_de_colunas; j += step){
            double sum = 0.0;
            int count = 0;

            if (i - halfstep >= 0){   // Pontos vizinhos para o Square Step
                sum += matriz_de_altitudes[i - halfstep][j];  // Topo
                count++;
            }
            if (i + halfstep < quantidade_de_linhas){
                sum += matriz_de_altitudes[i + halfstep][j];  // Base
                count++;
            }
            if (j - halfstep >= 0){
                sum += matriz_de_altitudes[i][j - halfstep];  // Esquerda
                count++;
            }
            if (j + halfstep < quantidade_de_colunas){
                sum += matriz_de_altitudes[i][j + halfstep];  // Direita
                count++;
            }
            if (count > 0){
                double media = sum / count;
                double randomvalue = _gerarAleatorio(roughness);

                if (matriz_de_altitudes[i][j] == -1.0){
                    matriz_de_altitudes[i][j] = media + randomvalue;
                }
            }
        }
    }
}

double Terreno::_gerarAleatorio(double maxvalue){   //função que gera valor aleatório entre [-max, max]
    static bool iniciado = false;
    if (!iniciado) {
        std::srand(std::time(nullptr)); 
        iniciado = true;
    }
    double random = (double)std::rand() / RAND_MAX;
    return (2.0 * random - 1.0) * maxvalue;
}

Imagem* Terreno::_sombreamento(Paleta palette){ //gera uma imagem com base nas altitudes e aplica sombreamento
    Imagem* img = new Imagem(quantidade_de_linhas, quantidade_de_colunas);

    double minimumheight = matriz_de_altitudes[0][0];   //encontra a menor altitude e a maior altitude
    double maximumheight = matriz_de_altitudes[0][0];

    for(int i = 0; i < quantidade_de_linhas; i++){
        for(int j = 0; j < quantidade_de_colunas; j++){
            if(matriz_de_altitudes[i][j] < minimumheight){
                minimumheight = matriz_de_altitudes[i][j];
            }
            if(matriz_de_altitudes[i][j] > maximumheight){
                maximumheight = matriz_de_altitudes[i][j];
            }
        }
    }

    double interval = maximumheight - minimumheight;
    if (interval == 0){ //evita divisão por zero se todas as altitudes forem iguais
        interval = 1; 
    }

    for (int i = 0; i < quantidade_de_linhas; i++){
        for (int j = 0; j < quantidade_de_colunas; j++){
            double height = matriz_de_altitudes[i][j];
            double normalvalue = (height - minimumheight) / interval;    //normaliza a altitude para o range [0, 1] para consulta na paleta

            Cor base = palette._consultaCor(normalvalue);   //obtém a cor base correspondente da paleta
            double shadow = 0.5;

            if (i > 0 && j > 0 && i < quantidade_de_linhas-1 && j < quantidade_de_colunas-1){   //calcula sombra somente se o ponto tiver vizinhos
                double dzdx = (matriz_de_altitudes[i][j+1] - matriz_de_altitudes[i][j-1]) / 2.0;    //derivadas parciais de x & y
                double dzdy = (matriz_de_altitudes[i+1][j] - matriz_de_altitudes[i-1][j]) / 2.0;

                double nx = -dzdx;  //vetor normal a superfície
                double ny = -dzdy;
                double nz = 1.0; // Assume que Z aponta para cima

                double lx = -1.0, ly = -1.0, lz = 1.0;  //vetor da luz, vindo do canto superior esquerdo

                double dot = nx*lx + ny*ly + nz*lz; //produto escalar entre o vetor normal e o vetor de luz

                double normaN = sqrt(nx*nx + ny*ny + nz*nz);    //normalização dos vetores
                double normaL = sqrt(lx*lx + ly*ly + lz*lz);

                shadow = std::max(0.4, shadow); //fator de sombreamento
                
                double intensity = 1.4; //intendidade do sombreamento
                shadow = std::pow(std::max(0.0, dot / (normaN * normaL)), intensity);   //realça a sombra com uma curva suave (potencializa pequenas variações)

            }

            Cor color{  //aplica o sombreamento
                static_cast<int>(base.r * shadow),
                static_cast<int>(base.g * shadow),
                static_cast<int>(base.b * shadow)
            };

            color.r = std::max(0, std::min(255, color.r));  //garante que os valores RGB fiquem entre 0 e 255 após o sombreamento
            color.g = std::max(0, std::min(255, color.g));
            color.b = std::max(0, std::min(255, color.b));


            img->_defineCorPixel(i, j, color);  //define o pixel sombreado
        }
    }
    return img;
}

void Terreno::_suavizarTerreno(int iterator){   //suaviza o relevo do terreno em 'iterator' iterações
    for (int k = 0; k < iterator; k++){
        double** copy = new double*[quantidade_de_linhas];  //cria uma cópia da matriz_de_altitudes

        for (int i = 0; i < quantidade_de_linhas; i++){
            copy[i] = new double[quantidade_de_colunas];

            for (int j = 0; j < quantidade_de_colunas; j++){
                copy[i][j] = matriz_de_altitudes[i][j];
            }
        }
        for (int i = 1; i < quantidade_de_linhas - 1; i++){ //aplica suavização nos pontos internos (3x3)
            for (int j = 1; j < quantidade_de_colunas - 1; j++){
                double sum = 0.0;
                for (int di = -1; di <= 1; di++){
                    for (int dj = -1; dj <= 1; dj++){
                        sum += copy[i + di][j + dj];
                    }
                }
                matriz_de_altitudes[i][j] = sum / 9.0;
            }
        }
        for (int i = 0; i < quantidade_de_linhas; i++){ //libera a memória alocada da matriz
            delete[] copy[i];
        }
        delete[] copy;
    }
}

#endif