#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "src/Grafo.h"
using namespace std;

Grafo* G = new Grafo();

void insereAresta(int ini, int fim, bool direcao, std::vector<std::vector<int> >& matAdj, int orientacao){
    ///direcao => grafo direcionado ou não
    ///orientacao => para que "lado" é o vertice
    if(direcao){
        //matAdj[ini][fim] = 1;
    }
    else{       ///Nao direcionado
        switch(orientacao){
            case 0:     ///Direita
                matAdj[ini][0] = fim;
                matAdj[fim][2] = ini;
                break;
            case 1:     ///Baixo
                matAdj[ini][1] = fim;
                matAdj[fim][3] = ini;
                break;
            case 2:     ///Esquerda
                matAdj[ini][2] = fim;
                matAdj[fim][0] = ini;
                break;
            case 3:     ///Cima
                matAdj[ini][3] = fim;
                matAdj[fim][1] = ini;
                break;
        }
    }
}

void printMatrix(std::vector<std::vector<int> >& matAdj){
    cout << "Modelo da Matriz:" <<endl;
    cout << "Linhas: Vertices" <<endl;
    cout << "Colunas: Arestas para uma direcao especifica" <<endl;
    cout << "Conteudo: Vertice de destino na direcao da aresta" <<endl;
    for(int i = 0; i < 14; i++){
        cout << "matAdj[" << i << "]: {";
        for(int j = 0; j < 4; j++){
            cout << matAdj[i][j] << ", ";
        }
        cout << "}" <<endl;
    }
}

void criaMapa01(std::vector<std::vector<int> >& matAdj, bool PARAMETER, std::vector<int>& operations){
    /**
    *   Operações:
    *   0 => Direita
    *   1 => Baixo
    *   2 => Esquerda
    *   3 => Cima
    */

    insereAresta(0, 1, PARAMETER, matAdj, 1);
    insereAresta(1, 2, PARAMETER, matAdj, 0);
    insereAresta(1, 4, PARAMETER, matAdj, 1);
    insereAresta(2, 3, PARAMETER, matAdj, 0);
    insereAresta(2, 5, PARAMETER, matAdj, 1);
    insereAresta(3, 6, PARAMETER, matAdj, 1);
    insereAresta(5, 8, PARAMETER, matAdj, 1);
    insereAresta(6, 9, PARAMETER, matAdj, 1);
    insereAresta(7, 10, PARAMETER, matAdj, 1);
    insereAresta(7, 8, PARAMETER, matAdj, 0);
    insereAresta(8, 9, PARAMETER, matAdj, 0);
    insereAresta(8, 11, PARAMETER, matAdj, 1);
    insereAresta(9, 12, PARAMETER, matAdj, 1);
    insereAresta(12, 13, PARAMETER, matAdj, 1);

    /************************************************************
    *                   MAPA                                    *
    *     Z                    0                                *
    *     |                    |                                *
    *     A--B--C              1--2--3                          *
    *     |  |  |              |  |  |                          *
    *     D  E  F              4  5  6                          *
    *        |  |                 |  |                          *
    *     G--H--I              7--8--9                          *
    *     |  |  |              |  |  |                          *
    *     J  K  L             10 11  12                         *
    *           |                    |                          *
    *           W                    13                         *
    *************************************************************/
    operations.push_back(0);        ///Primeiro da lista de adjacencia e assim vai, uma estratégia possível
    operations.push_back(1);
    operations.push_back(2);
    operations.push_back(3);
}

void metodoIrrevogavel(int ini, int fim, std::vector<std::vector<int> >& matAdj, std::vector<int>& operations){          ///Funcionando
    string arvore = "{";
    stringstream convert;   // stream used for the conversion
    int s = ini;
    int n = s;
    bool fracasso = false;
    bool sucesso = false;
    while((sucesso == false) && (fracasso == false)){
        int cont = 0;
        while(cont < operations.size()){
            if(matAdj[n][cont] != -1){
                convert << "[" << n <<" --(R:" << (cont+1) << ")--> " << matAdj[n][cont] << "], ";      ///Usado para a concatenação do texto e número em uma String única
                arvore = arvore + convert.str();
                convert.str(std::string());             ///"Limpa" a variável
                n = matAdj[n][cont];
                if(n == fim){
                    sucesso = true;
                }
                break;
            }
            cont++;
        }
        if(cont > operations.size()){               ///Não encontrou operação válida
            fracasso = true;
        }
    }
    if(fracasso == true){
        cout << "Fracasso em encontrar a solucao" << endl;
    }
    else{
        if(sucesso == true){
            cout << "--> Sucesso!!! Solucao: " << endl << endl;
            cout << arvore << endl;
        }
    }

}

void backtracking(int ini, int fim, std::vector<std::vector<int> >& matAdj, std::vector<int>& operations)
{

}

int main()
{
    std::vector<std::vector<int> > matVerticePorCaminho;
    bool PARAMETER = false;
    int matrixSize = 14;
    std::vector<std::vector<int> > matAdj;
    std::vector<int> operations;
    for(int i = 0; i < 14; i++){            ///Cria uma matriz vazia
        std::vector<int> aux;
        matAdj.push_back(aux);
        for(int j = 0; j < 4; j++){
            matAdj[i].push_back(-1);
        }
    }
    criaMapa01(matAdj, PARAMETER, operations);
    printMatrix(matAdj);
    metodoIrrevogavel(0, 13, matAdj, operations);

    //cout << PARAMETER << endl;
    //G->insereVertice(1);

    //G->imprime();
    return 0;
}
