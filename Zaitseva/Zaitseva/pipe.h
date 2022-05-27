#pragma once

#include <iostream>
#include <string>
#include "input.h"
#include <fstream>
#include <iomanip>

using namespace std;

class pipe {
public:
    static int MaxId;
    string Name;
    double length;
    int diameter;
    bool repair;

    static void DrawHeader();

    void edit();

    friend ostream& operator<<(ostream& out, const pipe& p);

    friend ofstream& operator<<(ofstream& fout, const pipe& p);

    friend istream& operator>>(istream& in, pipe& NewPipe);

    friend ifstream& operator>>(ifstream& fin, pipe& NewPipe);

    pipe();
};


