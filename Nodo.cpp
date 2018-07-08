#include "stdafx.h"
#include "Nodo.h"


Nodo::Nodo(vector<double> p) {
    DataPoint = p;
    PointN = p;
    PointP = p;
    bDataPoint = true;
    bHoja = false;
    bSuperNode = false;
    Padre = nullptr;
}

Nodo::Nodo() {
    bDataPoint = false;
    bHoja = false;
    bSuperNode = false;
    Padre = nullptr;
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

double Nodo::OverlapOf(int k) {
    double acum = 0.0;
    for (int i = 0; i < Hijos.size(); i++) {

    }
    return acum;
}

bool Nodo::Pertenece(vector<double> & p) {
    bool acum = true;
    for (int i = 0; acum && i < PointN.size(); i++) {
        acum &= PointN[i] <= p[i] && p[i] <= PointP[i];
    }
    return acum;
}

void Nodo::AddHijo(Nodo * hijo) {
    hijo->Padre = this;
    Hijos.push_back(hijo);
}

void Nodo::Imprimir(int iden) {
    cout << Identacion(iden) << "Region: PN (";
    for (int i = 0; i < PointN.size()-1; i++) {
        cout << PointN[i] << ", ";
    }
    cout << PointN[PointN.size()-1] << ")";
    cout << " - PP (";
    for (int i = 0; i < PointP.size()-1; i++) {
        cout << PointP[i] << ", ";
    }
    cout << PointP[PointP.size()-1] << ")" << endl;
    if (bDataPoint) {
        cout << Identacion(iden) << "Punto: (";
        for (int i = 0; i < DataPoint.size()-1; i++) {
            cout << DataPoint[i] << ", ";
        }
        cout << DataPoint[DataPoint.size()-1] << ")" << endl;
    }
    for (int i = 0; i < Hijos.size(); i++) {
        cout << Identacion(iden+1) << "Hijo " << i << endl;
        Hijos[i]->Imprimir(iden+1);
    }
}

string Nodo::Identacion(int Tam) {
    return string(Tam * 4, ' ');
}

