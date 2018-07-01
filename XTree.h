#pragma once

#include<iostream>
#include<vector>
#include<string>
#include"Nodo.h"

using namespace std;

class XTree {
    public:
        int Dimensions;
        int M;
        int m; // m <= M/2
        Nodo * Root;
        Nodo * ChooseLeaf(Nodo * Data);
        Nodo * SplitNodo(Nodo * nodo);
        void Insert(vector<double> point);//quiza deberi recibir un nodo data point
        void AdjustTree(Nodo * N, Nodo * NN);
        vector<int> PickSeeds(vector<Nodo *> & Entradas);
        int PickNext(vector<Nodo *> & Entradas, Nodo * G1, Nodo * G2);
        void ComponerRegion(vector<double> R1LU, vector<double> R1RB, vector<double> R2LU, vector<double> R2RB, vector<double> & RLU, vector<double> & RRB);
        float AreaRegion(vector<double> LU, vector<double> RB);//deberia tener usar la clase region
        void Imprimir();
        string Identacion(int Tam);

        XTree(int Dimensiones);
        XTree();
        ~XTree();
};

