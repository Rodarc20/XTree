#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Nodo {
    public:
        vector<double> PointN;//PointLU
        vector<double> PointP;//PointRB
        Nodo * Padre;
        vector<Nodo *> Hijos;
        vector<double> DataPoint;
        bool bDataPoint;
        bool bHoja;//si es hoja, tiene un DataPoint, es decir apunt hacia algo un registro o algo, si no es hoja quiere decir que tiene hijos
        double CoverageArea();
        void CalcularCoverage();
        bool Pertenece(vector<double> p);
        void AddHijo(Nodo * hijo);
        void Imprimir(int iden);
        string Identacion(int Tam);
        Nodo(vector<double> p);
        Nodo();
        ~Nodo();
};

