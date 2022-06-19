#pragma once

#include <iostream>
#include <string>
#include "input.h"
#include <iomanip>

using namespace std;

class KS {
public:
    static int MaxId;
    string Name;
    int Count, CountInWork;
    double Efficiency;

    static void DrawHeader();

    void edit(int NewCountInWork);

    friend ostream& operator<<(ostream& out, const KS& k);

    friend istream& operator>>(istream& in, KS& NewKS);

    KS();
};