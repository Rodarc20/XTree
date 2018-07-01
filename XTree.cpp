#include "stdafx.h"
#include "XTree.h"


XTree::XTree(int Dimensiones) {
    Dimensions = Dimensiones;
}

XTree::XTree() {
}


XTree::~XTree() {
}

Nodo * XTree::ChooseLeaf(Nodo * Data) {
    return nullptr;
}

Nodo * XTree::SplitNodo(Nodo * nodo) {
    return nullptr;
}

void XTree::Insert(vector<double> point) {
}

void XTree::AdjustTree(Nodo * N, Nodo * NN) {
}

vector<int> XTree::PickSeeds(vector<Nodo*>& Entradas) {
    return vector<int>();
}

int XTree::PickNext(vector<Nodo*>& Entradas, Nodo * G1, Nodo * G2) {
    return 0;
}

void XTree::ComponerRegion(vector<double> R1LU, vector<double> R1RB, vector<double> R2LU, vector<double> R2RB, vector<double>& RLU, vector<double>& RRB) {
}

float XTree::AreaRegion(vector<double> LU, vector<double> RB) {
    return 0.0f;
}

void XTree::Imprimir() {
}

string XTree::Identacion(int Tam) {
    return string();
}
