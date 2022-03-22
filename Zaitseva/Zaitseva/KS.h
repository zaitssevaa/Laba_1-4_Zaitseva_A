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

    void edit(int NewCountInWork);

    void save(ofstream& out) const;

    void load(ifstream&);

    friend std::ostream& operator<<(ostream& out, const KS& k);

    friend std::istream& operator>>(istream& in, KS& NewKS);

    KS();
};