#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Nodo {
    public:
        vector<float> PointLU;
        vector<float> PointRB;
        Nodo * Padre;
        vector<Nodo *> Hijos;
        vector<float> DataPoint;
        bool bDataPoint;
        bool bHoja;//si es hoja, tiene un DataPoint, es decir apunt hacia algo un registro o algo, si no es hoja quiere decir que tiene hijos
        float CoverageArea();
        void CalcularCoverage();
        bool Pertenece(vector<float> p);
        void AddHijo(Nodo * hijo);
        void Imprimir(int iden);
        string Identacion(int Tam);
        Nodo(vector<float> p);
        Nodo();
        ~Nodo();
};

