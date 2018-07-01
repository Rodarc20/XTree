#include "stdafx.h"
#include "Nodo.h"


Nodo::Nodo() {
}


Nodo::~Nodo() {
}

double Nodo::CoverageArea() {
    double acum = 1;
    for (int i = 0; i < PointN.size(); i++) {//pintLu tiene el mismo tamaño que potinRB y data point
        //tener cuidado con el sistema de coordenas, de pronto alguno tiene el ordn invertido, es decir Point LU podria estar en los negativos en un eje, pero podria estar en los positivos en otro eje, 
        //lo importante es que LU y RB son vertices opuestos del hypercubo, les cambiare el nombre
        acum *= PointP[i] - PointN[i];
    }
    return acum;
}

void Nodo::CalcularCoverage() {
    if (bDataPoint) {
        PointN = DataPoint;
        PointP = DataPoint;
    }
    else {
        if (Hijos.size()) {
            PointN = Hijos[0]->PointN;
            PointP = Hijos[0]->PointP;
        }
        for (int i = 0; i < Hijos.size(); i++) {
            //actualizar mis PointLU y PoinrRB, con lso minimos y maximos que correspondadn
            for (int j = 0; j < PointN.size(); j++) {//esto es para avanzar en el numero de dimensiones de los vectores, tal vez deberia almacenalo en alguna variable
                if (Hijos[i]->PointN[j] < PointN[j]) {
                    PointN[j] = Hijos[i]->PointN[j];
                }
                if (Hijos[i]->PointP[j] > PointP[j]) {
                    PointP[j] = Hijos[i]->PointP[j];
                }
            }
        }
    }
}

bool Nodo::Pertenece(vector<double> p) {
    return false;
}

void Nodo::AddHijo(Nodo * hijo) {
}

void Nodo::Imprimir(int iden) {
}

string Nodo::Identacion(int Tam) {
    return string();
}

Nodo::Nodo(vector<double> p) {
}
