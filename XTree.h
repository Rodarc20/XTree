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
        void ComponerRegion(vector<double> & R1N, vector<double> & R1P, vector<double> & R2N, vector<double> & R2P, vector<double> & RN, vector<double> & RP);//RN y RP son parametros que son la salida de esta funcion
        double AreaRegion(vector<double> & N, vector<double> & P);//deberia tener usar la clase region
        void Imprimir();
        string Identacion(int Tam);

        XTree(int Dimensiones);
        XTree();
        ~XTree();
};

