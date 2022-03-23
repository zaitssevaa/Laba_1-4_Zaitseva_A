#pragma once

#include <iostream>
#include <string>
#include "input.h"
#include <fstream>
#include <iomanip>

using namespace std;

class KS {
public:
    string Name;
    int Count, CountInWork;
    double Efficiency;

    static void DrawHeader();

    void edit(int NewCountInWork);

    friend ostream &operator<<(ostream& out, const KS& k);

    friend ofstream& operator<<(ofstream& fout, const KS& k);

    friend istream &operator>>(istream &in, KS &NewKS);

    friend istream& operator>>(istream& in, KS& NewKS);

    KS();
};